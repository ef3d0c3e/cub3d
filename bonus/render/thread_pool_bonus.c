/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_pool_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <cub3d_bonus.h>

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
