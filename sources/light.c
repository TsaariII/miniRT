/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@hive.fi>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:32:29 by nzharkev          #+#    #+#             */
/*   Updated: 2025/02/25 12:12:39 by amaula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

/**
 * ambient_checks - Sets up validation checks for ambient light properties.
 *
 * @checks: Array of function pointers for validation.
 *
 * The function assigns:
 * - `is_double` to check ambient brightness.
 * - `is_color` to check ambient color.
 * - NULL to indicate the end of the checks.
 */
void	ambient_checks(int (**checks)(char *))
{
	checks[0] = &is_double;
	checks[1] = &is_color;
	checks[2] = NULL;
}

/**
 * lights_checks - Sets up validation checks for light source properties.
 *
 * @checks: Array of function pointers for validation.
 *
 * The function assigns:
 * - `is_vector` to check light position.
 * - `is_double` to check light brightness.
 * - NULL to indicate the end of the checks.
 */
void	lights_checks(int (**checks)(char *))
{
	checks[0] = &is_vector;
	checks[1] = &is_double;
	checks[2] = &is_color;
	checks[3] = NULL;
}

/**
 * create_light - Initializes lighting calculations.
 *
 * @light: Pointer to the light object.
 * @ray: Pointer to the ray being processed.
 * @coll: The collision point where the light is interacting.
 *
 * Computes the light direction and view direction based on the collision point
 * and stores them in the `t_light` structure. Resets diffuse and specular
 * components to zero.
 */
static void	create_light(t_light *light, t_ray *ray, t_vector coll)
{
	light->diff = 0.0;
	light->spec = 0.0;
	light->shine = SHINE;
	light->light_dir = normalize_vector(v_sub(light->obj->location, coll));
	light->view_dir = v_mul(-1, ray->direction);
}

/**
 * set_lights - Computes the final color based on
 *              ambient, diffuse, and specular lighting.
 *
 * @data: Pointer to the scene data.
 * @ray: Pointer to the ray being processed.
 * @collision: The collision point where light calculations occur.
 *
 * The function initializes lighting, applies ambient lighting, calculates
 * shadows, and applies diffuse and specular lighting if the point is lit.
 * The final RGB values are clamped to the 0-255 range.
 *
 * Returns:
 * - The computed color as a 32-bit RGBA value.
 */
uint32_t	set_lights(t_data *data, t_ray *ray, t_vector collision)
{
	t_vector	final_col;
	double		shadow_f;

	shadow_f = 1.0;
	create_light(data->light, ray, collision);
	data->ambient->color.x = ((data->ambient->obj->color >> 24) & 0xff);
	data->ambient->color.y = ((data->ambient->obj->color >> 16) & 0xff);
	data->ambient->color.z = ((data->ambient->obj->color >> 8) & 0xff);
	final_col = v_sum(data->ambient->color, decompose_color(ray->color));
	final_col = v_mul(0.5, final_col);
	final_col = v_mul(data->ambient->obj->brightness, final_col);
	shadow_f = in_the_shadow(ray, data->light->obj, data);
	if (shadow_f == 0)
		return (recompose_color(final_col));
	light_col(data, ray, &final_col, shadow_f);
	data->light->r = min(255, (int)(final_col.x));
	data->light->g = min(255, (int)(final_col.y));
	data->light->b = min(255, (int)(final_col.z));
	data->light->color = (data->light->r << 24 | data->light->g << 16
			| data->light->b << 8 | 255);
	return (data->light->color);
}
