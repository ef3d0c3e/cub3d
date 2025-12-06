/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <parser/parser.h>
#include <stdio.h>
#include <util/util.h>
#include <parser/parser.h>
#include <cub3d.h>

static int
	cleanup(t_app *app, enum e_init_error status)
{
	static const char	*msgs[] = {
	[INIT_ERR_PARSE] = "Parsing failed\n",
	[INIT_ERR_MLX] = "Failed to initialize MLX\n",
	[INIT_ERR_WINDOW] = "Failed to initialize Window\n",
	[INIT_ERR_LOAD] = "Failed to load assets\n",
	};
	void				*mlx;

	mlx = NULL;
	if (status >= INIT_ERR_WINDOW)
		mlx = app->mlx_ptr;
	if (status >= INIT_ERR_MLX)
		map_free(mlx, &app->map);
	if (status >= INIT_ERR_WINDOW)
		mlx_destroy_window(app->mlx_ptr, app->mlx_window);
	if (status >= INIT_ERR_LOAD)
	{
		mlx_destroy_display(app->mlx_ptr);
		free(app->mlx_ptr);
	}
	if (status != INIT_OK)
		write(STDOUT_FILENO, msgs[status], ft_strlen(msgs[status]));
	return (status != INIT_OK);
}

int
	main(int ac, char **av)
{
	t_app	app;

	ft_memset(&app, 0, sizeof(app));
	if (!parse_map(av[1], &app.map))
		return (cleanup(&app, INIT_ERR_PARSE));
	app.mlx_ptr = mlx_init();
	if (!app.mlx_ptr)
		return (cleanup(&app, INIT_ERR_MLX));
	app.mlx_window = mlx_new_window(app.mlx_ptr, 512, 512, "Cub3D");
	if (!app.mlx_window)
		return (cleanup(&app, INIT_ERR_WINDOW));
	if (!map_asset_load(app.mlx_ptr, &app.map))
		return (cleanup(&app, INIT_ERR_LOAD));
	return (cleanup(&app, INIT_OK));
}
