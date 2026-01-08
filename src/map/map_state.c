/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_state.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <cub3d.h>

int
	map_state_cmp(const void *lhs, const void *rhs)
{
	const uintptr_t	*a = lhs;
	const uintptr_t	*b = rhs;

	if (a > b)
		return (1);
	if (a < b)
		return (-1);
	return (0);
}

void
	*map_state_get(struct s_app *app, int x, int y)
{
	uintptr_t	key;

	key = ((uintptr_t)(int32_t)x) | (((uintptr_t)(int32_t)y) << 32);
	return (rb_find(&app->map.map_state, (void*)key));
}

void
	map_state_set(struct s_app *app, int x, int y, void *state)
{
	uintptr_t	key;

	key = (uintptr_t)(int32_t)x | (((uintptr_t)(int32_t)y) << 32);
	rb_insert(&app->map.map_state, (void*)key, state);
}
