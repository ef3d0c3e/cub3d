/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_props_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <cub3d_bonus.h>

/** @brief Setup default property values */
static void
	init_properties(struct s_parser *parser)
{
	parser->s_data.parsing_properties = true;
	parser->s_data.properties.accelerate = 15.f;
	parser->s_data.properties.friction = 0.92f;
	parser->s_data.properties.frame_time = 1.f / 60.f;
	parser->s_data.properties.player_spawn = '0';
	parser->s_data.properties.pitch_enabled = 1;
}

static int
	parse_property_bool(struct s_parser *parser, const char *name, int *val)
{
	const char	*line;

	line = parser_trim_start(parser->line, " ");
	if (ft_strncmp(line, "PROP", 4))
		return (0);
	if (!parser_expect_space(parser, &line, "PROP"))
		return (-1);
	if (ft_strncmp(line, name, ft_strlen(name)))
		return (-2);
	if (!parser_expect_space(parser, &line, name))
		return (-1);
	if (*line == '0')
		*val = 0;
	else if (*line == '1')
		*val = 1;
	else
		return (parser_error_loc(parser, err(0, "Expected 0 or 1")), -1);
	line = parser_trim_start(line + 1, " ");
	if (*line && *line != '\n')
		return (parser_error_loc(parser, err(0, "Unexpected token")), -1);
	return (1);
}

int
	parser_props2(struct s_parser *parser)
{
	int	status;

	status = parse_property_mat(parser, "player_spawn",
			&parser->s_data.properties.player_spawn);
	if (status == 0 || status == -2)
		status = parse_property_bool(parser, "pitch_enabled",
				&parser->s_data.properties.pitch_enabled);
	return (status);
}

bool
	parser_props(struct s_parser *parser)
{
	int	status;

	if (!parser->s_data.parsing_properties)
		init_properties(parser);
	if (!*parser_trim_start(parser->line, " \n"))
		return (true);
	status = parse_property_float(parser, "accelerate",
			&parser->s_data.properties.accelerate);
	if (status == 0 || status == -2)
		status = parse_property_float(parser, "friction",
				&parser->s_data.properties.friction);
	if (status == 0 || status == -2)
		status = parse_property_float(parser, "frame_time",
				&parser->s_data.properties.frame_time);
	if (status == 0 || status == -2)
		status = parser_props2(parser);
	if (status == -2)
		return (parser_error_loc(parser, err(0, "Unknown property name")),
			false);
	if (status == -1)
		return (false);
	else if (status == 0)
		parser->state = PARSE_ENT;
	return (true);
}
