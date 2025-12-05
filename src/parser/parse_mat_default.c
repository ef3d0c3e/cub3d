/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_mat_default.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <parser/parser.h>

static inline int
	cube_parser(struct s_parser *parser)
{
	static const char	*texs[] = {
		"NO", "North",
		"EA", "East",
		"SO", "South",
		"WE", "West",
		NULL,
	};
	int					status;
	t_material			mat;

	ft_memset(&mat, 0, sizeof(mat));
	mat.orientation = ORI_NONE;
	mat.type = MAT_CUBE;
	status = parse_material(parser, "CUBE", texs, &mat);
	if (status == 1)
		atlas_mat_add(&parser->s_data.mat_atlas, mat);
	return (status);
}

static inline int
	floor_parser(struct s_parser *parser)
{
	static const char	*texs[] = {
		"TO", "Top",
		"BO", "Bottom",
		NULL,
	};
	int					status;
	t_material			mat;

	ft_memset(&mat, 0, sizeof(mat));
	mat.orientation = ORI_NONE;
	mat.type = MAT_FLOOR;
	status = parse_material(parser, "FLOOR", texs, &mat);
	if (status == 1)
		atlas_mat_add(&parser->s_data.mat_atlas, mat);
	return (status);
}

int
	parse_mat_default(struct s_parser *parser)
{
	int	status;

	status = cube_parser(parser);
	if (status == 0)
		status = floor_parser(parser);
	return (status);
}
