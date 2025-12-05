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

/**
 * @defgroup Assets Assets
 * @{
 */

/** @brief ID of an object in an atlas */
typedef unsigned int	t_atlas_id;

////////////////////////////////////////////////////////////////////////////////
// Textures                                                                   //
////////////////////////////////////////////////////////////////////////////////

/**
 * @defgroup Textures Textures
 * @ingroup Assets
 * @{
 */

/** @brief A texture */
typedef struct s_texture
{
	/** @brief Texture width in pixels */
	int		width;
	/** @brief Texture height in pixels */
	int		height;
	/** @brief Texture path */
	char	*path;
	/** @brief mlx image handle */
	t_img	*img;
}	t_texture;

/** @brief The atlas holding all textures */
typedef struct s_texture_atlas
{
	/** @brief All textures */
	t_texture	*textures;
	/** @brief The number of textures */
	size_t		size;
	/** @brief Capacity of the atlas */
	size_t		capacity;
}	t_texture_atlas;

/**
 * @brief Add a texture in the texture atlas
 *
 * @param atlas The atlas
 * @param texture The texture to add
 * @return The ID of the inserted texture, or the ID of a previous texture if a
 * texture with the same path already exists. In that case @p texture is freed.
 */
t_atlas_id
atlas_tex_add(t_texture_atlas *atlas, t_texture texture);
/**
 * @brief Free the texture atlas
 *
 * @param mlx_ptr The mlx instance, if `NULL` no images will be freed
 * @param atlas The atlas to free
 */
void
atlas_tex_free(void *mlx_ptr, t_texture_atlas *atlas);

/** @} */

////////////////////////////////////////////////////////////////////////////////
// Materials                                                                  //
////////////////////////////////////////////////////////////////////////////////

/**
 * @defgroup Materials Materials
 * @ingroup Assets
 * @{
 */

/** @brief Represent the type of a material */
enum e_mat_type
{
	/** @brief Empty space with a floor and ceiling texture */
	MAT_FLOOR,
	/** @brief Cube wall with four sides */
	MAT_CUBE,
	/** @brief A door with 2 sides and an orientation */
	MAT_DOOR,
	/** @brief A cylinder with a single texture */
	MAT_CYLINDER,
};

/** @brief A material */
typedef struct s_material
{
	/** @brief Material character id */
	char				id;
	/** @brief Material type */
	enum e_mat_type		type;
	/** @brief Material textures */
	t_atlas_id			tex_ids[4];
	/** @brief Material orientation */
	enum e_orientation	orientation;
}	t_material;

/** @brief The atlas holding all materials */
typedef struct s_material_atlas
{
	/** @brief All materials */
	t_material	*materials;
	/** @brief Number of materials */
	size_t		size;
	/** @brief Capacity of the atlas */
	size_t		capacity;
}	t_material_atlas;

/**
 * @brief Add a material in the material atlas
 *
 * @param atlas The atlas
 * @param material The material to add
 * @return The ID of the inserted material
 */
t_atlas_id
atlas_mat_add(t_material_atlas *atlas, t_material material);
/**
 * @brief Free the material atlas
 *
 * @param atlas The atlas to free
 */
void
atlas_mat_free(t_material_atlas *atlas);
/**
 * @brief Get a material by it's character id
 *
 * @param atlas The atlas to get the material from
 * @param ch The material character id
 * @return The material, or `NULL` if not found
 */	
t_material
*atlas_mat_get(t_material_atlas *atlas, char ch);

/** @} */

/** @} */

#endif // ASSETS_H
