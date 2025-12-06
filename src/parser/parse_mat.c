/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_mat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <parser/parser.h>

/** @brief Initialize the atlases with the header's textures and default
 * materials */
static void
	init_atlas(struct s_parser *parser)
{
	t_atlas_id	texs[4];
	t_texture	tex;

	ft_memset(&tex, 0, sizeof(tex));
	tex.path = parser->s_data.textures[0];
	texs[0] = atlas_tex_add(&parser->s_data.tex_atlas, tex);
	parser->s_data.textures[0] = NULL;
	tex.path = parser->s_data.textures[1];
	texs[1] = atlas_tex_add(&parser->s_data.tex_atlas, tex);
	parser->s_data.textures[1] = NULL;
	tex.path = parser->s_data.textures[2];
	texs[2] = atlas_tex_add(&parser->s_data.tex_atlas, tex);
	parser->s_data.textures[2] = NULL;
	tex.path = parser->s_data.textures[3];
	texs[3] = atlas_tex_add(&parser->s_data.tex_atlas, tex);
	parser->s_data.textures[3] = NULL;
	atlas_mat_add(&parser->s_data.mat_atlas, (t_material){.id = ' ', .tex_ids
		= {0, 0, 0, 0}, .orientation = ORI_NONE, .type = MAT_OPEN,});
	atlas_mat_add(&parser->s_data.mat_atlas, (t_material){.id = '0', .tex_ids
		= {0, 0, 0, 0}, .orientation = ORI_NONE, .type = MAT_FLOOR,});
	atlas_mat_add(&parser->s_data.mat_atlas, (t_material){.id = '1', .tex_ids
		= {texs[0], texs[1], texs[2], texs[3]}, .orientation = ORI_NONE, .type
		= MAT_CUBE});
}

bool
	parser_mat(struct s_parser *parser)
{
	int	status;

	if (parser->s_data.mat_atlas.size == 0)
		init_atlas(parser);
	if (!*parser_trim_start(parser->line, " \t\n"))
		return (true);
	status = parse_mat_default(parser);
	if (status == -1)
		return (false);
	else if (status == 0)
		parser->state = PARSE_PROPS;
	return (true);
}
