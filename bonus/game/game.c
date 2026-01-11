/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <cub3d_bonus.h>

bool
	game_setup(t_app *app)
{
	if (!game_minimap_setup(app))
		return (false);
	player_setup(app);
	app->game.show_minimap = true;
	return (true);
}

void
	game_cleanup(t_app *app)
{
	(void)app;
}
