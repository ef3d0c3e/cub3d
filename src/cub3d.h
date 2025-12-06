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

/** @brief Initialization status */
enum e_init_error
{
	INIT_ERR_PARSE,
	INIT_ERR_MLX,
	INIT_ERR_WINDOW,
	INIT_ERR_LOAD,
	INIT_OK,
};

typedef struct s_app
{
	void	*mlx_ptr;
	void	*mlx_window;
	t_map	map;
}	t_app;

#endif // CUB3D_H
