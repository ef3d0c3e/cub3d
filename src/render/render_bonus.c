/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
# include <render/render_bonus.h>
# include <cub3d.h>

static __attribute__((always_inline)) inline  void
	worker_scanline(t_app *app, int x, const struct s_render_ent_data *ents)
{
	t_ray				r;
	size_t				i;
	int					y;
	const t_proj_ent	*ent;

	ray_init(&app->game.player, 2.f * ((float)x / (float)app->sizes.x) - 1.f,
			&r);
	ray_cast(app, &r);
	app->z_buffer[x] = r.perp_dist;
	render_scanline(app, x, &r);
	i = 0;
	while (i < ents->num)
	{
		ent = &ents->ents[i++];
		if (ent->start_x > x || ent->end_x < x || ent->dist > r.perp_dist)
			continue ;
		y = ent->start_y;
		while (y < ent->end_y)
			render_entity_pix(app, ent, x, y++);
	}
}

/** @brief Worker thread based on work-stealing */
static void
	*render_worker(void *arg)
{
	t_thread_pool *const	pool = arg;
	t_app					*app;
	int						x;
	size_t					job;

	job = 0;
	while (1)
	{
		pthread_mutex_lock(&pool->mutex);
		while (!pool->stop && pool->job_id == job)
			pthread_cond_wait(&pool->cond_start, &pool->mutex);
		if (pool->stop)
		{
			pthread_mutex_unlock(&pool->mutex);
			break ;
		}
		job = pool->job_id;
		app = pool->job.app;
		pthread_mutex_unlock(&pool->mutex);
		while (1)
		{
			x = __atomic_fetch_add(&pool->job.next_x, 1, __ATOMIC_RELAXED);
			if (x >= app->sizes.x)
				break ;
			worker_scanline(app, x, pool->job.ents);
		}
		pthread_mutex_lock(&pool->mutex);
		if (--pool->active_workers == 0)
			pthread_cond_broadcast(&pool->cond_done);
		pthread_mutex_unlock(&pool->mutex);
	}
	return (NULL);
}

void
	render_frame_bonus(t_app *app)
{
	struct s_render_ent_data	ents;

	project_entities(app, &ents, NULL);
	pthread_mutex_lock(&app->pool.mutex);
    app->pool.job.app = app;
    app->pool.job.next_x = 0;
    app->pool.work_available = true;
	app->pool.job_id++;
	app->pool.job.ents = &ents;
    app->pool.active_workers = app->pool.thread_count;
    pthread_cond_broadcast(&app->pool.cond_start);
    while (app->pool.active_workers > 0)
		pthread_cond_wait(&app->pool.cond_done, &app->pool.mutex);
    pthread_mutex_unlock(&app->pool.mutex);
    //render_entities(app);
}

bool
	thread_pool_init(t_thread_pool *pool, size_t thread_count)
{
	size_t	i;

	ft_memset(pool, 0, sizeof(*pool));
	pool->thread_count = thread_count;
	if (pthread_cond_init(&pool->cond_start, NULL))
		return (false);
	if (pthread_cond_init(&pool->cond_done, NULL))
		return (pthread_cond_destroy(&pool->cond_start), false);
	pthread_mutex_init(&pool->mutex, NULL);
	pool->threads = xmalloc(sizeof(pthread_t) * thread_count);
	ft_memset(pool->threads, 0, sizeof(pthread_t) * thread_count);
	i = 0;
	while (i < thread_count)
	{
		if (!pthread_create(&pool->threads[i++], NULL, render_worker, pool))
			continue ;
		while (--i)
			pthread_join(pool->threads[i], NULL);
		free(pool->threads);
		pthread_mutex_destroy(&pool->mutex);
		pthread_cond_destroy(&pool->cond_done);
		pthread_cond_destroy(&pool->cond_start);
		return (false);
	}
	return (true);
}

void
	thread_pool_destroy(t_thread_pool *pool)
{
	size_t	i;

    pthread_mutex_lock(&pool->mutex);
    pool->stop = 1;
    pthread_cond_broadcast(&pool->cond_start);
    pthread_mutex_unlock(&pool->mutex);
	i = 0;
	while (i < pool->thread_count)
		pthread_join(pool->threads[i++], NULL);
    pthread_mutex_destroy(&pool->mutex);
    pthread_cond_destroy(&pool->cond_done);
    pthread_cond_destroy(&pool->cond_start);
    free(pool->threads);
}
