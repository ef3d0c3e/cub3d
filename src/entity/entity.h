/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef ENTITY_H
# define ENTITY_H

# include <assets/assets.h>

struct	s_app;

/**
 * @defgroup Entities Entities
 * @{
 */

////////////////////////////////////////////////////////////////////////////////
// Entity data                                                                //
////////////////////////////////////////////////////////////////////////////////

/** @brief Contains data common to all entities */
typedef struct s_entity_data
{
	/** @brief Entity animation sprite (X, Y) id */
	t_pos	anim_state;
	/** @brief Entity position (m) */
	t_vec2	position;
	/** @brief Entity velocity (m/s) */
	t_vec2	velocity;
	/** @brief Entity acceleration (m/s²) */
	t_vec2	acceleration;
	/** @brief Entity angles (yaw, pitch) */
	t_vec2	angles;
}	t_entity_data;

/** @brief Static data for each entity type */
typedef struct s_entity_type
{
	/** @brief Entity model data */
	t_sprite_sheet	model;
	/** @brief Entity hitbox size */
	t_vec2			hitbox_size;

	/**
	 * @brief Function to create an instance of the entity:
	 * - `app`: Application pointer
	 * - `data`: Entity data to instantiate with
	 * - `cookie`: Optional user-provided data
	 */
	void			*(*create_fn)(
			struct s_app *app,
			t_entity_data data,
			void *cookie);
	/**
	 * @brief Function to load assets for an entity type
	 * - `app`: Application pointer
	 * - return `true` on success, `false` on errors
	 */
	bool			(*load_fn)(
		struct s_app * app);
	/**
	 * @brief Function to tick an entity instance
	 * - `app`: Application pointer
	 * - `entity`: Entity instance
	 */
	void			(*tick_fn)(
			struct s_app *app,
			void *entity);
}	t_entity_type;

/** @brief Base data for all entities */
typedef struct s_entity
{
	/** @brief Entity types, contains methods and constant fields */
	const t_entity_type	*type;
	/** @brief Common entity data */
	t_entity_data		data;
}	t_entity;

/** @brief Entity types */
enum e_ent_id
{
	ENT_ITEM,
	ENT_GHOUL,
	ENT_NUM_,
};

/**
 * @brief Get the entity type for the associated @ref e_ent_id
 *
 * @param id The entity to get the type for
 * @return Entity type for @p id
 */
t_entity_type
*ent_type(enum e_ent_id id);

/**
 * @brief Asset loader function for entities
 *
 * @param app Application pointer
 * @param assets Assets registry
 * @return `true` on success, `false` on errors.
 */
bool
ent_load_assets(struct s_app *app, struct s_assets *assets);

////////////////////////////////////////////////////////////////////////////////
// Individual entities                                                        //
////////////////////////////////////////////////////////////////////////////////

/**
 * @defgroup IndividualEntities Individual Entities
 * @ingroup Entities
 * @{
 */

/** @brief On ground item entity */
struct s_ent_item
{
	/** @brief Base entity data */
	t_entity			base;
};

/**
 * @brief Get the entity type for @ref ENT_ITEM
 *
 * @return The entity type for @ref ENT_ITEM
 */
t_entity_type
*ent_type_item(void);

struct s_ent_ghoul
{
	/** @brief Base entity data */
	t_entity			base;
};

/**
 * @brief Get the entity type for @ref ENT_GHOUL
 *
 * @return The entity type for @ref ENT_GHOUL
 */
t_entity_type
*ent_type_ghoul(void);

/** @} */

/** @} */

#endif // ENTITY_H
