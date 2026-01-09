/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project_entity.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <cub3d.h>

static bool
	cast_entity_2(
	const t_app *app,
	const t_entity *ent,
	t_proj_ent *e,
	int scale)
{
	const t_player	*p = &app->game.player;
	int				i;
	float			min;

	e->dist = e->trans.y;
	e->start_x = clamp(e->real_start_x, 0, app->sizes.x);
	e->vmove_y = (int)((float)ent->type->offset.y / e->trans.y);
	e->end_x = clamp(e->end_x, 0, app->sizes.x);
	e->w = (int)((float)scale * ent->type->scale.x);
	e->h = (int)((float)scale * ent->type->scale.y);
	e->start_y = (-e->h + app->sizes.y) / 2 + p->pitch + e->vmove_y;
	e->end_y = (e->h + app->sizes.y) / 2 + p->pitch + e->vmove_y;
	if (e->end_y < 0 || e->start_y >= app->sizes.y)
		return (false);
	e->start_y = clamp(e->start_y, 0, app->sizes.y);
	e->end_y = clamp(e->end_y, 0, app->sizes.y);
	e->flip = ent->data.flip;
	e->sprite = sprite_sheet_get(&ent->type->model,
			ent->data.anim_state.x, ent->data.anim_state.y);
	i = e->start_x;
	min = 1e10f;
	while (i < e->end_x)
		min = fmaxf(min, app->z_buffer[i++]);
	return (e->dist < min);
}

/** @brief Cast for a single entity */
static void
	cast_entity(
	const t_app *app,
	struct s_render_ent_data *render,
	t_entity *ent)
{
	const t_player	*p = &app->game.player;
	t_proj_ent		e;
	int				scale;

	e.ent = ent;
	e.space.x = ent->data.position.x - p->position.x;
	e.space.y = ent->data.position.y - p->position.y;
	e.inv_det = 0.f;
	e.inv_det = p->plane.x * p->dir.y - p->plane.y * p->dir.x;
	if (fabsf(e.inv_det) < 1e-10)
		return ;
	e.inv_det = 1.f / e.inv_det;
	e.trans.x = e.inv_det * (e.space.x * p->dir.y - e.space.y * p->dir.x);
	e.trans.y = -e.inv_det * (e.space.x * p->plane.y - e.space.y * p->plane.x);
	if (e.trans.y < 1e-2)
		return ;
	scale = absi((int)((float)app->sizes.y / e.trans.y));
	e.screen_x = ((float)app->sizes.x / 2.f) * (1.f + e.trans.x / e.trans.y)
		+ ent->type->offset.x * (float)scale;
	e.real_start_x = (int)(e.screen_x - (float)scale / 2.f);
	e.end_x = (int)ceilf(e.screen_x + (float)scale / 2.f);
	if (e.end_x < 0 || e.real_start_x >= app->sizes.x
		|| !cast_entity_2(app, ent, &e, scale))
		return ;
	render->ents[render->num++] = e;
}

/** @brief Iteration function for entities */
static void
	entity_traverse(size_t depth, t_rbnode *node, void *cookie)
{
	struct s_ent_tr_data *const	data = cookie;
	const char					*name = ((t_entity *)node->key)->type->name;

	(void)depth;
	if (!data->exclude
		|| ft_strncmp(data->exclude, name, ft_strlen(data->exclude)))
		cast_entity(data->app, data->render, node->key);
}

/** @brief Compare function to sort entities back to front */
static int
	ent_cmp(const void *lhs, const void *rhs)
{
	const t_proj_ent	*a = lhs;
	const t_proj_ent	*b = rhs;

	if (a->dist > b->dist)
		return (-1);
	else if (a->dist < b->dist)
		return (1);
	return (0);
}

void
	project_entities(
	t_app *app,
	struct s_render_ent_data *render,
	const char *exclude)
{
	struct s_ent_tr_data	data;
	t_proj_ent				tmp[MAX_ENTITIES];

	render->num = 0;
	data.app = app;
	data.render = render;
	data.exclude = exclude;
	rb_apply(&app->entities, entity_traverse, &data);
	ft_qsort_base(render->ents, render->num, (struct s_qsort_param){
		.s = sizeof(t_proj_ent),
		.cmp = ent_cmp,
		.t = (char *)tmp,
	});
}
