/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ents.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <parser/parser.h>

static const t_entity_type
	*get_type(struct s_parser *parser, const char *line)
{
	const t_entity_type	*type;
	size_t				name_len;
	enum e_ent_id		id;

	name_len = 0;
	while (!ft_strchr(" \t\n", line[name_len]))
		++name_len;
	id = 0;
	while (id < ENT_NUM_)
	{
		type = ent_get_type(id);
		if (!ft_strncmp(line, type->name, name_len))
			return (type);
		++id;
	}
	parser_error_loc(parser, err_style(err_style_n(err(0, "Failed to find entit"
					"y type '"), line, name_len, (t_text_style){COL_GREEN, 0,
				STYLE_BOLD}), "'", (t_text_style){0, 0, 0}));
	return (NULL);
}

static bool
	parse_vec2(struct s_parser *parser, const char **line, t_vec2 *vec)
{
	*vec = (t_vec2){0, 0};
	if (!parser_expect(parser, line, "("))
		return (false);
	if (!parse_float(parser, line, "vector x component", &vec->x))
		return (false);
	if (!parser_expect(parser, line, ","))
		return (false);
	*line = parser_trim_start(*line, " \t");
	if (!parse_float(parser, line, "vector y component", &vec->y))
		return (false);
	return (parser_expect(parser, line, ")"));
}

static void
	add_entity(struct s_parser *parser, struct s_parser_ent ent)
{
	if (parser->s_data.ents_size == parser->s_data.ents_capacity)
	{
		parser->s_data.ents_capacity = parser->s_data.ents_capacity * 2
			+ !parser->s_data.ents_capacity * 16;
		parser->s_data.ents = xrealloc(parser->s_data.ents,
				sizeof(ent) * parser->s_data.ents_size,
				sizeof(ent) * parser->s_data.ents_capacity);
	}
	parser->s_data.ents[parser->s_data.ents_size++] = ent;
}

static int
	parse_entity(struct s_parser *parser)
{
	const char			*line;
	size_t				name_len;
	struct s_parser_ent	ent;

	ft_memset(&ent, 0, sizeof(ent));
	line = parser_trim_start(parser->line, " \t");
	if (ft_strncmp(line, "ENT", 3))
		return (0);
	if (!parser_expect_space(parser, &line, "ENT"))
		return (-1);
	name_len = 0;
	while (!ft_strchr(" \t\n", line[name_len]))
		++name_len;
	ent.type = get_type(parser, line);
	if (!ent.type)
		return (-1);
	if (!parser_expect_space(parser, &line, ent.type->name))
		return (-1);
	if (!parse_vec2(parser, &line, &ent.pos))
		return (-1);
	if (*line && *line != '\n')
		return (parser_error_loc(parser, err(0, "Unexpected token")), -1);
	add_entity(parser, ent);
	return (1);
}

bool
	parser_entities(struct s_parser *parser)
{
	int	status;

	if (!*parser_trim_start(parser->line, " \t\n"))
		return (true);
	status = parse_entity(parser);
	if (status == -1)
		return (false);
	if (status == 0)
		parser->state = PARSE_MAP;
	return (true);
}
