/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defs.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef DEFS_H
# define DEFS_H

# include <assets/assets.h>

struct			s_assets;
struct			s_app;

/**
 * @defgroup PredefinedAssets Predefined Assets
 * @ingroup Assets
 * @{
 */

/**
 * @brief Asset loader function
 *
 * @param app Application pointer
 * @param assets The global asset registry
 */
typedef bool	(*t_asset_loader)(
	struct s_app *app,
	struct s_assets *assets);

////////////////////////////////////////////////////////////////////////////////
// Weapons                                                                    //
////////////////////////////////////////////////////////////////////////////////

/**
 * @defgroup WeaponAssets Weapon Assets
 * @ingroup PredefinedAssets
 * @{
 */

/** @brief Player weapon */
typedef struct s_weapon
{
	/** @brief Weapon view model */
	t_sprite_sheet	view_model;
	/** @brief Weapon item model (on ground) */
	t_sprite		item_model;
	/** @brief Number of ammunitions */
	int				ammo;
	/** @brief Time taken by the shoto animation */
	float			anim_shoot_time;
}	t_weapon;

/** @brief All available weapons */
enum e_weapon_id
{
	/** @brief No weapon selected */
	WEAPON_NONE = -1,
	/** @brief The shotgun weapon */
	WEAPON_SHOTGUN = 0,
	/** @brief Number of weapons */
	WEAPON_NUM_,
};

/** @} */

////////////////////////////////////////////////////////////////////////////////
// Registry                                                                   //
////////////////////////////////////////////////////////////////////////////////

/**
 * @defgroup RegistryAssets Assets Registry
 * @ingroup PredefinedAssets
 * @{
 */

/** @brief A struct holding all assets */
typedef struct s_assets
{
	/** @brief Texture for pickups */
	const t_texture	*items;
	/** @brief Sprites for all weapons */
	t_weapon		weapons[WEAPON_NUM_];
}	t_assets;

/**
 * @brief Load all assets
 *
 * @param app Application pointer
 * @return `true` on success, `false` on errors
 */
bool
assets_load(struct s_app *app);
/**
 * @brief Asset loader for the map
 *
 * @param app Application
 * @param assets Assets
 * @return `true` on success, `false` on errors
 */
bool
asset_loader_map(struct s_app *app, t_assets *assets);
/**
 * @brief Asset loader for the font
 *
 * @param app Application
 * @param assets Assets
 * @return `true` on success, `false` on errors
 */
bool
asset_loader_font(struct s_app *app, t_assets *assets);
/**
 * @brief Asset loader for items
 *
 * @param app Application
 * @param assets Assets
 * @return `true` on success, `false` on errors
 */
bool
asset_loader_items(struct s_app *app, t_assets *assets);
/**
 * @brief Asset loader for weapons
 *
 * @param app Application
 * @param assets Assets
 * @return `true` on success, `false` on errors
 */
bool
asset_loader_weapons(struct s_app *app, t_assets *assets);

////////////////////////////////////////////////////////////////////////////////
// Internal                                                                   //
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Display an error message for asset loading
 *
 * @param path Path to the loaded asset
 * @param errstr Error message
 */
void
assets_error(const char *path, t_err_str errstr);
/**
 * @brief Check the size of a loaded texture
 *
 * @param tex Loaded texture
 * @param width Expected width
 * @param height Expected height
 * @return `true` if sizes match, `false` otherwise and print
 * an error message
 */
bool
asset_size_check(const t_texture *tex, int width, int height);

/** @} */

/** @} */

#endif // DEFS_H
