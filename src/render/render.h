/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef RENDER_H
# define RENDER_H

# include <map/map.h>

struct	s_app;

////////////////////////////////////////////////////////////////////////////////
// Render                                                                     //
////////////////////////////////////////////////////////////////////////////////

/**
 * @defgroup Render Render
 * @{
 */

/**
 * @brief Render the current scene to screen
 *
 * @param app Application pointer
 */
void
render_frame(struct s_app *app);

/** @} */

#endif // RENDER_H
