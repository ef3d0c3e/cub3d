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
}	t_texture_atlas;

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
	/** @brief Material type */
	enum e_mat_type		type;
	/** @brief Material textures */
	int					tdx_ids[4];
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
}	t_material_atlas;

/** @} */

/** @} */

#endif // ASSETS_H
