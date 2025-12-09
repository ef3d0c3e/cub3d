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
# include <assets/defs/defs.h>
# include <map/map.h>
# include <hud/hud.h>
# include <hud/panel/panel.h>
# include <ui/ui.h>
# include <player/player.h>
# include <entity/entity.h>
# include <game/game.h>
# include <render/render.h>

/** @brief Initialization status */
enum e_init_error
{
	/** @brief Error while parsing */
	INIT_ERR_PARSE,
	/** @brief Error during MLX setup */
	INIT_ERR_MLX,
	/** @brief Error during MLX window creation */
	INIT_ERR_WINDOW,
	/** @brief Error while loading assets */
	INIT_ERR_LOAD,
	/** @brief Error during UI setup */
	INIT_ERR_UI,
	/** @brief Error during game init */
	INIT_ERR_INIT,
	/** @brief No error happened */
	INIT_OK,
};

typedef struct s_app
{
	/* --- Render data --- */
	/** @brief Window sizes */
	t_pos				sizes;
	/** @brief MLX instance pointer */
	void				*mlx_ptr;
	/** @brief MLX window pointer */
	void				*mlx_window;
	/** @brief Texture atlas */
	t_texture_atlas		texture_atlas;
	/** @brief Material atlas */
	t_material_atlas	material_atlas;
	/** @brief Last rame duration in seconds */
	float				frame_delta;
	/** @brief Current frame number */
	unsigned long long	frame;

	/* --- UI Data --- */
	/** @brief Event data */
	struct s_event		event;
	/** @brief The application's framer buffer */
	t_img				*framebuffer;
	/** @brief Application assets */
	t_assets			assets;
	/** @brief HUD */
	t_hud				hud;

	/* --- Game Data --- */
	/** @brief The map */
	t_map				map;
	/** @brief Spawned entities */
	t_rbtree			entities;
	/** @brief Game data */
	t_game				game;
}	t_app;

/**
 * @brief Setup the application
 *
 * @param app Setup the last required variables for the application
 */
bool
app_setup(t_app *app);
/**
 * @brief Cleanup the application
 *
 * @param app Setup the last required variables for the application
 */
void
app_cleanup(t_app *app);

#endif // CUB3D_H
