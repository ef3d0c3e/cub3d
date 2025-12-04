/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef ASSETS_H
# define ASSETS_H

# include <util/util.h>

////////////////////////////////////////////////////////////////////////////////
// Textures                                                                   //
////////////////////////////////////////////////////////////////////////////////

typedef struct s_texture
{
	int		width;
	int		height;
	char	*path;
	t_img	*img;
}	t_texture;

typedef struct s_texture_atlas
{
	t_texture	*textures;
	size_t		size;
}	t_texture_atlas;

////////////////////////////////////////////////////////////////////////////////
// Materials                                                                  //
////////////////////////////////////////////////////////////////////////////////

enum e_mat_type
{
	MAT_FLOOR,
	MAT_CUBE,
	MAT_DOOR,
	MAT_CYLINDER,
};

typedef struct s_material
{
	enum e_mat_type	type;
	int				tdx_ids[4];
	int				orientation;
}	t_material;

typedef struct s_material_atlas
{
	t_material	*materials;
	size_t		size;
}	t_material_atlas;

#endif // ASSETS_H
