/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_mat_props_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <cub3d_bonus.h>

/**
 * @brief Parse integer value
 *
 * @param parser Parser
 * @param val Value range
 * @param name Value name
 * @param bounds Bounds [min, max] for the parsed value
 * @return The parsed value, `-1` on errors
 */
static int
	parse_int(
	struct s_parser *parser,
	const char *val[2],
	const char *name,
	const int bounds[2])
{
	int		x;

	x = 0;
	while (val[0] != val[1])
	{
		if (!ft_isdigit(*val[0]))
			return (parser_error_loc(parser, err_rst(err_style(err(0, "Unexpect"
								"ed token when parsing "), name, (t_text_style){
							COL_GREEN, 0, STYLE_BOLD}), "")), -1);
		x = x * 10 + *val[0] - '0';
		if (x > bounds[1])
			return (parser_error_loc(parser, err_rst(err_style(err(0, "Value fo"
								"r "), name, (t_text_style){COL_GREEN, 0,
							STYLE_BOLD}), " is too high")), -1);
		++val[0];
	}
	if (x < bounds[0])
		return (parser_error_loc(parser, err_rst(err_style(err(0, "Value for "),
						name, (t_text_style){COL_GREEN, 0, STYLE_BOLD}),
				" is too low")), -1);
	return (x);
}

/**
 * @brief Parse color value
 *
 * @param parser Parser
 * @param val Value range
 * @param name Value name
 * @return The parsed value, @ref COLOR_UNINIT on errors
 */
static t_color
	parse_color(
	struct s_parser *parser,
	const char *val[2],
	const char *name)
{
	static const char	*set = "0123456789abcdef";
	char				*s;
	t_color				x;

	x = 0;
	if (val[1] - val[0] != 6)
		return (parser_error_loc(parser, err_rst(err_style(err(0, "Color fo"
							"r "), name, (t_text_style){COL_GREEN, 0,
						STYLE_BOLD}), " is invalid")), (t_color)COLOR_UNINIT);
	while (val[0] != val[1])
	{
		s = ft_strchr(set, ft_tolower(*val[0]));
		if (!s)
			return (parser_error_loc(parser, err_rst(err_style(err(0, "Unexpect"
								"ed token when parsing "), name, (t_text_style){
							COL_GREEN, 0, STYLE_BOLD}), "")),
					(t_color)COLOR_UNINIT);
		x = x * 16 + (t_color)(s - set);
		++val[0];
	}
	return (x);
}

static bool
	parse_prop_values_2(
	struct s_parser *parser,
	const char *prop[2],
	t_material_prop *mp,
	const char *sep)
{
	t_color		parsed_c;

	if (!ft_strncmp("reflect_color", prop[0], (size_t)(sep - prop[0])))
	{
		parsed_c = parse_color(parser, (const char *[2]){sep + 1, prop[1]},
				"reflect_color");
		mp->reflect_color = parsed_c;
		return (parsed_c != (t_color)COLOR_UNINIT);
	}
	if (!ft_strncmp("fade_color", prop[0], (size_t)(sep - prop[0])))
	{
		parsed_c = parse_color(parser, (const char *[2]){sep + 1, prop[1]},
				"fade_color");
		mp->fade_color = parsed_c;
		return (parsed_c != (t_color)COLOR_UNINIT);
	}
	return (parser_error_loc(parser, err_rst(err_style_n(err(0, "Unknown proper"
						"ty name '"), prop[0], (size_t)(sep - prop[0]),
				(t_text_style){COL_GREEN, 0, STYLE_BOLD}), "'")), false);
}

/** @brief Parse the value of a property */
static bool
	parse_prop_values_1(
	struct s_parser *parser,
	const char *prop[2],
	t_material_prop *mp)
{
	const char	*sep = ft_strmchr(prop[0], prop[1], '=');
	int			parsed_i;

	if (!sep)
		return (parser_error_loc(parser, err(0, "Missing property")), false);
	if (!ft_strncmp("emission", prop[0], (size_t)(sep - prop[0])))
	{
		parsed_i = parse_int(parser, (const char *[2]){sep + 1, prop[1]},
				"emission", (const int [2]){0, 255});
		return (mp->emission = (uint8_t)parsed_i, parsed_i != -1);
	}
	if (!ft_strncmp("reflectivity", prop[0], (size_t)(sep - prop[0])))
	{
		parsed_i = parse_int(parser, (const char *[2]){sep + 1, prop[1]},
				"reflectivity", (const int [2]){0, 255});
		mp->reflectivity = (uint8_t)parsed_i;
		return (parsed_i != -1);
	}
	return (parse_prop_values_2(parser, prop, mp, sep));
}

bool
	parse_mat_props(
	struct s_parser *parser,
	const char *tex[2],
	t_material_prop *props)
{
	const char	*sep = ft_strmchr(tex[0], tex[1], ':');
	const char	*p = sep + 1;
	const char	*next;

	if (!sep)
		return (1);
	while (p != tex[1])
	{
		next = ft_strmchr(p, tex[1], ':');
		if (next)
		{
			if (!parse_prop_values_1(parser, (const char *[2]){p, next}, props))
				return (false);
			p = next + 1;
		}
		else
		{
			if (!parse_prop_values_1(parser, (const char *[2]){p, tex[1]},
				props))
				return (false);
			p = tex[1];
		}
	}
	tex[1] = sep;
	return (true);
}
