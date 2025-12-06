/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef CUB3D_H
# define CUB3D_H

# include <util/util.h>
# include <map/map.h>
# include <ui/ui.h>
# include <assets/defs/defs.h>

/** @brief Initialization status */
enum e_init_error
{
	/** @brief Error while parsing */
	INIT_ERR_PARSE,
	/** @brief Error during MLX setup */
	INIT_ERR_MLX,
	/** @brief Error during MLX window creation */
	INIT_ERR_WINDOW,
	/** @brief Error while loading map assets */
	INIT_ERR_LOAD,
	/** @brief Error during UI setup */
	INIT_ERR_UI,
	/** @brief No error happened */
	INIT_OK,
};

typedef struct s_app
{
	/** @brief Window sizes */
	t_pos			sizes;
	/** @brief MLX instance pointer */
	void			*mlx_ptr;
	/** @brief MLX window pointer */
	void			*mlx_window;
	/** @brief The map */
	t_map			map;

	/* --- UI Data --- */
	/** @brief Event data */
	struct s_event	event;
	/** @brief The application's framer buffer */
	t_img			*framebuffer;
	/** @brief Application assets */
	t_assets		assets;

}	t_app;

#endif // CUB3D_H
