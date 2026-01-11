/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef RENDER_BONUS_H
# define RENDER_BONUS_H

# include <stdbool.h>
# include <pthread.h>

struct	s_app;
struct	s_render_ent_data;

/** @brief Number of scanline per work request */
#define WORK_CHUNK 8

typedef struct s_render_job
{
	struct s_app				*app;
	int							next_x;
	struct s_render_ent_data	*ents;
}	t_render_job;

typedef struct s_thread_pool
{
	/** @brief Render threads */
	pthread_t		*threads;
	/** @brief Number of render threads */
	size_t			thread_count;

	/** @brief Mutex for the condition variables, `active_workers` and `stop` */
	pthread_mutex_t	mutex;
	/** @brief Condvar to start rendering */
	pthread_cond_t	cond_start;
	/** @brief Condvar to stop rendering */
	pthread_cond_t	cond_done;

	/** @brief Number of active workers */
	size_t			active_workers;
	/** @brief Whether to stop working */
	bool			stop;
	/** @brief Whether work is available */
	bool			work_available;
	/** @brief Current job ID */
	size_t			job_id;

	/** @brief Render job */
	t_render_job	job;
}	t_thread_pool;

/** @brief Render a frame using the thread pool */
void
render_frame_bonus(struct s_app *app);
/** @brief Initialize thread pool */
bool
thread_pool_init(t_thread_pool *pool, size_t thread_count);
/** @brief Destroy thread pool */
void
thread_pool_destroy(t_thread_pool *pool);
/** @brief Worker thread routine */
void
*render_worker(void *arg);

#endif // RENDER_BONUS_H
