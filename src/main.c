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
#include <cub3d.h>

static int
	cleanup(t_app *app, enum e_init_error status)
{
	static const char	*msgs[] = {
	[INIT_ERR_PARSE] = "Parsing failed\n",
	[INIT_ERR_MLX] = "Failed to initialize MLX\n",
	[INIT_ERR_WINDOW] = "Failed to initialize Window\n",
	[INIT_ERR_LOAD] = "Failed to load assets\n",
	[INIT_ERR_UI] = "Failed to setup UI\n",
	};

	if (status >= INIT_ERR_UI)
		ui_cleanup(app);
	if (status >= INIT_ERR_MLX)
		map_free(&app->map);
	if (status >= INIT_ERR_WINDOW)
		mlx_destroy_window(app->mlx_ptr, app->mlx_window);
	if (status >= INIT_ERR_LOAD)
	{
		atlas_mat_free(&app->material_atlas);
		atlas_tex_free(app->mlx_ptr, &app->texture_atlas);
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

	if (ac != 2)
		return (printf("USAGE: %s MAP.cub\n", av[0]), 1);
	ft_memset(&app, 0, sizeof(app));
	app.sizes = (t_pos){1024, 512};
	if (!parse_map(av[1], &app))
		return (cleanup(&app, INIT_ERR_PARSE));
	app.mlx_ptr = mlx_init();
	if (!app.mlx_ptr)
		return (cleanup(&app, INIT_ERR_MLX));
	app.mlx_window = mlx_new_window(app.mlx_ptr,
			app.sizes.x, app.sizes.y, "Cub3D");
	if (!app.mlx_window)
		return (cleanup(&app, INIT_ERR_WINDOW));
	if (!assets_load(&app))
		return (cleanup(&app, INIT_ERR_LOAD));
	if (!ui_setup(&app))
		return (cleanup(&app, INIT_ERR_UI));
	mlx_loop(app.mlx_ptr);
	return (cleanup(&app, INIT_OK));
}
