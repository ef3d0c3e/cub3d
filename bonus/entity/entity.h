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
struct	s_assets;

/**
 * @defgroup Entities Entities
 * @{
 */

////////////////////////////////////////////////////////////////////////////////
// Entity data                                                                //
////////////////////////////////////////////////////////////////////////////////

/** @brief Types of Player -> Entity interactions */
enum e_ent_interaction_kind
{
	/** @brief Player attacks entity */
	ENTI_ATTACK,
	/** @brief Player activates entity */
	ENTI_ACTIVATE,
};

/** @brief Player -> Entity interaction data */
typedef struct s_ent_interaction
{
	enum e_ent_interaction_kind	kind;
	union
	{
		struct
		{
			/** @brief Entity attack damage */
			int		damage;
			float	knockback;
		}	s_attack;
	}	u_data;
}	t_ent_interaction;

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
	/** @brief Render mirrored sprite */
	bool	flip;
	/** @brief Entity tint color */
	t_color	color;
	/** @brief Flag to delete entity at the end of the current frame */
	bool	delete;
}	t_entity_data;

/** @brief Static data for each entity type */
typedef struct s_entity_type
{
	/** @brief Entity type name */
	const char		*name;
	/** @brief Entity model data */
	t_sprite_sheet	model;
	/** @brief Entity hitbox size */
	t_vec2			hitbox_size;

	/** @brief Entity (X, Y) offset */
	t_vec2			offset;
	/** @brief Entity (X, Y) scale */
	t_vec2			scale;

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
	/**
	 * @brief Function to interact with an entity instance
	 * - `app`: Application pointer
	 * - `entity`: Entity instance
	 * - `interaction`: Interaction
	 */
	void			(*interact_fn)(
			struct s_app *app,
			void *entity,
			struct s_ent_interaction interaction);
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
	ENT_ITEM_HEAL,
	ENT_ITEM_AMMO_SHOTGUN,
	ENT_PART_SHOTGUN,
	ENT_ITEM_SHOTGUN,
	ENT_ITEM_AMMO_CHAINGUN,
	ENT_ITEM_CHAINGUN,
	ENT_PART_CHAINGUN,
	ENT_GHOUL,
	ENT_NUM_,
};

/**
 * @brief Get the entity type for the associated @ref e_ent_id
 *
 * @param id The entity to get the type for
 * @return Entity type for @p id
 */
const t_entity_type
*ent_get_type(enum e_ent_id id);

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
 * @brief Get the tntity type for @ref ENT_ITEM_HEAL
 *
 * @return The entity type for @ref ENT_ITEM_HEAL
 */
t_entity_type
*ent_type_item_heal(void);
/**
 * @brief Get the tntity type for @ref ENT_ITEM_AMMO_SHOTGUN
 *
 * @return The entity type for @ref ENT_ITEM_AMMO_SHOTGUN
 */
t_entity_type
*ent_type_item_ammo_shotgun(void);
/**
 * @brief Get the tntity type for @ref ENT_ITEM_SHOTGUN
 *
 * @return The entity type for @ref ENT_ITEM_SHOTGUN
 */
t_entity_type
*ent_type_item_shotgun(void);
/**
 * @brief Get the tntity type for @ref ENT_ITEM_AMMO_CHAINGUN
 *
 * @return The entity type for @ref ENT_ITEM_AMMO_CHAINGUN
 */
t_entity_type
*ent_type_item_ammo_chaingun(void);
/**
 * @brief Get the tntity type for @ref ENT_ITEM_CHAINGUN
 *
 * @return The entity type for @ref ENT_ITEM_CHAINGUN
 */
t_entity_type
*ent_type_item_chaingun(void);

struct s_ent_particle
{
	/** @brief Base entity data */
	t_entity			base;
	/** @brief Alive time of the particle */
	float				lifetime;
};
/**
 * @brief Get the entity type for @ref ENT_PART_SHOTGUN
 *
 * @return The entity type for @ref ENT_PART_SHOTGUN
 */
t_entity_type
*ent_type_part_shotgun(void);
/**
 * @brief Get the entity type for @ref ENT_PART_CHAINGUN
 *
 * @return The entity type for @ref ENT_PART_CHAINGUN
 */
t_entity_type
*ent_type_part_chaingun(void);

struct s_ent_ghoul
{
	/** @brief Base entity data */
	t_entity			base;
	/** @brief Ghoul health */
	int					health;
	/** @brief Ghoul damage time */
	float				hurt_time;
	/** @brief Ghoul forced aggression time */
	float				aggro_time;
};
/**
 * @brief Get the entity type for @ref ENT_GHOUL
 *
 * @return The entity type for @ref ENT_GHOUL
 */
t_entity_type
*ent_type_ghoul(void);

/** @} */

////////////////////////////////////////////////////////////////////////////////
// Entity system                                                              //
////////////////////////////////////////////////////////////////////////////////

/**
 * @defgroup SystemEntities Entity System
 * @ingroup Entities
 * @{
 */

/**
 * @brief Setup the entity system
 *
 * @param app Application pointer
 */
void
ent_setup(struct s_app *app);
/**
 * @brief Spawn a new entity
 *
 * @param app Application pointer
 * @param id Entity id
 * @param data Entity data
 * @return The spawned entity
 */
void
*ent_spawn(struct s_app *app, enum e_ent_id id, t_entity_data data);
/**
 * @brief Tick all entities
 *
 * @param app Application pointer
 */
void
ent_update(struct s_app *app);

/** @} */

/** @} */

#endif // ENTITY_H
