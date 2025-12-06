/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_props.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <parser/parser.h>

/** @brief Setup default property values */
static void
	init_properties(struct s_parser *parser)
{
	parser->s_data.parsing_properties = true;
	parser->s_data.properties.accelerate = 1.f;
	parser->s_data.properties.friction = 0.95f;
	parser->s_data.properties.frame_time = 1.f / 60.f;
	parser->s_data.properties.player_spawn = '0';
}

bool
	parser_props(struct s_parser *parser)
{
	int	status;

	if (!parser->s_data.parsing_properties)
		init_properties(parser);
	if (!*parser_trim_start(parser->line, " \t\n"))
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
		status = parse_property_mat(parser, "player_spawn",
				&parser->s_data.properties.player_spawn);
	if (status == -2)
		return (parser_error_loc(parser, err(0, "Unknown property name")),
			false);
	if (status == -1)
		return (false);
	else if (status == 0)
		parser->state = PARSE_MAP; // TODO: PARSE_ENT
	return (true);
}
