/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_mat_textures.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <parser/parser.h>

/**
 * @brief Parse a single texture property for a material
 *
 * @param parser The parser
 * @param line Current position in line
 * @param tex Texture attribute `{IDENT, NAME}`
 * @param out Output for the parsed property
 * @return `0` if not the correct property to parse, `-1` on errors,
 * `1` on success
 */
static int
	parse_tex_prop(
	struct s_parser *parser,
	const char **line,
	const char **tex,
	const char **out)
{
	size_t	i;

	if (ft_strncmp(*line, tex[0], ft_strlen(tex[0])))
		return (0);
	if (out[1])
		return (parser_error_loc(parser, err_style(err_style(err(0, "Duplicate "
							"texture '"), tex[1], (t_text_style){COL_YELLOW, 0,
						STYLE_BOLD}), "'", (t_text_style){0, 0, 0})), -1);
	*line += ft_strlen(tex[0]);
	if (**line != '=')
		return (parser_error_loc(parser, err_style(err_style(err(0, "Expected '"
							"=' after '"), tex[0], (t_text_style){COL_YELLOW, 0,
						STYLE_BOLD}), "'", (t_text_style){0, 0, 0})), -1);
	++*line;
	out[0] = *line;
	i = 0;
	while (!ft_strchr(" \t\n", (*line)[i]))
		++i;
	if (!i)
		return (parser_error_loc(parser, err_style(err_style(err(0, "Empty '"),
						tex[1], (t_text_style){COL_YELLOW, 0, STYLE_BOLD}),
				"' texture", (t_text_style){0, 0, 0})), -1);
	*line += i;
	out[1] = *line;
	return (1);
}

/**
 * @brief Check textures extensions and insert them into the atlas
 *
 * @param parser The parser
 * @param attrs_parsed An array containing `{TEXTURE ATTRIBUTES,
 * PARSED PROPERTIES}`
 * @param counts An array containing `{NUMBER OF PARSED PROPERTIES, NUMBER OF
 * EXPECTED PROPERTIES}`
 * @param mat The material
 * @return `true` on success, `false` on errors
 */
static bool
	insert_textures(
	struct s_parser *parser,
	const char ***attrs_parsed,
	const size_t *counts,
	t_material *mat)
{
	size_t		i;
	size_t		len;
	t_texture	tex;

	i = 0;
	while (i < counts[0])
	{
		len = (size_t)(attrs_parsed[1][2 * i + 1] - attrs_parsed[1][2 * i]);
		if (len < 4 || ft_strncmp(attrs_parsed[1][2 * i] + len - 4, ".xpm", 4))
			return (parser_error_loc(parser, err(0, "Invalid extension for "
						"texture")), false);
		++i;
	}
	i = 0;
	ft_memset(&tex, 0, sizeof(tex));
	while (i < counts[0])
	{
		len = (size_t)(attrs_parsed[1][2 * i + 1] - attrs_parsed[1][2 * i]);
		tex.path = ft_strndup(attrs_parsed[1][2 * i], len);
		mat->tex_ids[i++] = atlas_tex_add(&parser->s_data.tex_atlas, tex);
	}
	return (true);
}

/**
 * @brief Check for missing textures and calls `insert_textures`
 *
 * @param parser The parser
 * @param attrs_parsed An array containing `{TEXTURE ATTRIBUTES,
 * PARSED PROPERTIES}`
 * @param counts An array containing `{NUMBER OF PARSED PROPERTIES, NUMBER OF
 * EXPECTED PROPERTIES}`
 * @param mat The material
 * @return `true` on success, `false` on errors
 */
static bool
	validate_textures(
	struct s_parser *parser,
	const char ***attrs_parsed,
	const size_t *counts,
	t_material *mat)
{
	t_err_str	msg;
	size_t		i;

	i = 0;
	if (counts[0] != counts[1])
	{
		msg = err(0, "Missing textures");
		while (i++ < counts[1])
		{
			if (!attrs_parsed[1][2 * i - 1])
				msg = err_style(err_style(msg, " ", (t_text_style){0, 0, 0}),
						attrs_parsed[0][2 * i - 1], (t_text_style){COL_YELLOW,
						0, STYLE_BOLD});
		}
		return (parser_error_loc(parser, msg), false);
	}
	return (insert_textures(parser, attrs_parsed, counts, mat));
}

bool
	parse_mat_textures(
	struct s_parser *parser,
	const char **line,
	const char **tex_attrs,
	t_material *mat)
{
	const char		*texs[8];
	size_t			i;
	int				s;
	size_t			counts[2];

	ft_memset(texs, 0, sizeof(texs));
	ft_memset(counts, 0, sizeof(counts));
	while (tex_attrs[2 * counts[1]])
		++counts[1];
	while (**line && **line != '\n')
	{
		i = 0;
		while (**line && **line != '\n' && tex_attrs[i * 2])
		{
			s = parse_tex_prop(parser, line, &tex_attrs[2 * i], &texs[2 * i]);
			if (++i && s == 0)
				continue ;
			if (s == -1)
				return (false);
			++counts[0];
			*line = parser_trim_start(*line, " \t");
		}
	}
	return (validate_textures(parser, (const char **[2]){tex_attrs, texs},
		counts, mat));
}
