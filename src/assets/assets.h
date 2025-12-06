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

enum
{
	/** @brief Invalid atlas ID */
	ATLAS_INVALID = ~0,
};

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
/**
 * @brief Get a texture from it's atlas id
 *
 * @param atlas The atlas to get the texture from
 * @param tex_id The texture ID in the atlas
 * @return The texture, or `NULL` if not found
 */
const t_texture
*atlas_tex_get(const t_texture_atlas *atlas, t_atlas_id tex_id);
/**
 * @brief Load a texture and store it in the atlas
 *
 * @param mlx_ptr MLX instance pointer
 * @param atlas The texture atlas
 * @param path Path to the image
 * @param out Output the texture's pointer
 * @return The texture id on success, `ATLAS_INVALID` otherwise
 */
t_atlas_id
atlas_tex_load(
	void *mlx_ptr,
	t_texture_atlas *atlas,
	const char *path,
	const t_texture **out);

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
	/** @brief Outside area */
	MAT_OPEN,
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
const t_material
*atlas_mat_get(const t_material_atlas *atlas, char ch);
/**
 * @brief Get that atlas id of a material
 *
 * @param atlas The material atlas
 * @param ch The id of the material
 * @return The ID of the material or `0` if not found
 */
t_atlas_id
atlas_mat_get_id(const t_material_atlas *atlas, char ch);

/** @} */

////////////////////////////////////////////////////////////////////////////////
// Sprites                                                                    //
////////////////////////////////////////////////////////////////////////////////

/**
 * @defgroup Sprites Sprites
 * @ingroup Assets
 * @{
 */

/** @brief A sprite */
typedef struct s_sprite
{
	/** @brief Texture of the sprite */
	const t_texture	*texture;
	/** @brief Background color of the sprite (for transparency) */
	t_color			background;
	/** @brief Sprite rectangle `x` coordinate */
	int				left;
	/** @brief Sprite rectangle `y` coordinate */
	int				top;
	/** @brief Sprite rectangle width */
	int				width;
	/** @brief Sprite rectangle height */
	int				height;
	/** @brief Number of pixels in a line on the sprite's sheet texture */
	int				line_size;
}	t_sprite;

/**
 * @brief Sample a pixel from a sprite
 *
 * @param spr Sprite to sample from
 * @param u X-axis factor, in range `[0.f, 1.f]`
 * @param v Y-axis factor, in range `[0.f, 1.f]`
 * @return The sampled color (or `COLOR_UNINIT` if sampling background)
 */
t_color
sprite_sample(const t_sprite *spr, float u, float v);

/**
 * @brief A sprite-sheet
 *
 * A 2D grid containing multiple sprites.
 * The left dimension represent separate animation states.
 * The down dimension represent animation frames.
 */
typedef struct s_sprite_sheet
{
	/** @brief Texture of the sheet */
	const t_texture	*texture;
	/** @brief Background color of the sheet (for transparency) */
	t_color			background;

	/** @brief Left-offset of the sheet */
	int				off_left;
	/** @brief Top-offset of the sheet */
	int				off_top;
	/** @brief Left separator width */
	int				sep_left;
	/** @brief Top separator height */
	int				sep_top;
	/** @brief Width of a single sprite in the sheet */
	int				width;
	/** @brief Height of a single sprite in the sheet */
	int				height;
}	t_sprite_sheet;

/**
 * @brief Get a sprite from a sheet
 *
 * @param sheet The sprite sheet to get a sprite from
 * @param x Sprite `x` id (state)
 * @param y Sprite `y` id (animation)
 * @return The sprite at index `(x, y)`
 */
t_sprite
sprite_sheet_get(const t_sprite_sheet *sheet, int x, int y);
/**
 * @brief Sample directly from a sprite sheet
 *
 * @param sheet The sheet to sample from
 * @param id The sprite's id in the sheet
 * @param uv The sprite's uv in the sheet
 * @return The sampled pixel, or `COLOR_UNINIT` for background
 */
t_color
sprite_sheet_sample(const t_sprite_sheet *sheet, t_pos id, t_vec2 uv);

/** @} */

/** @} */

#endif // ASSETS_H
