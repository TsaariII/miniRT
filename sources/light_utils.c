/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzharkev <nzharkev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:32:42 by nzharkev          #+#    #+#             */
/*   Updated: 2025/02/24 18:50:51 by nzharkev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

/**
 * in_the_shadow - Determines the shadow factor at a collision point.
 *
 * @collision: The point where the light interaction is being checked.
 * @light: Pointer to the light object.
 * @data: Pointer to the scene data.
 *
 * This function traces a shadow ray from the collision point toward the light
 * source. If an object is found along the way, the function returns a factor
 * based on the distance of obstruction to soften the shadow rather than
 * making it completely dark.
 *
 * Returns:
 * - A shadow factor between 0.2 and 1.0, where 1.0 means fully lit and
 *   values closer to 0.2 mean the point is more occluded.
 */
double	in_the_shadow(t_ray *ray, t_object *light, t_data *data)
{
	t_ray	shadow;

	shadow.direction = normalize_vector(v_sub(light->location, ray->end));
	shadow.start = v_sum(ray->end, v_mul(EPSILON, shadow.direction));
	shadow.distance = DBL_MAX;
	if (cast_ray(&shadow, data, 0))
	{
		if (shadow.distance + EPSILON < v_dist(light->location, ray->end))
			return (0);
	}
	return (1);
}

/**
 * set_specular - Computes the specular lighting component.
 *
 * @norm: Normal at the collision point.
 * @light: Pointer to the light object.
 *
 * This function calculates the specular reflection using the Blinn-Phong
 * model. It considers the halfway vector between the light direction and
 * the view direction to determine how much light is reflected toward the
 * observer.
 *
 * Returns:
 * - The computed specular intensity, influenced by light brightness and
 *   the material's shininess.
 */
double	set_specular(t_vector norm, t_light *light)
{
	t_vector	halfway;
	double		dot_p;

	halfway = normalize_vector(v_sum(light->light_dir, light->view_dir));
	dot_p = dot(norm, halfway);
	if (dot_p < 0)
		return (0);
	return (light->obj->brightness * pow(fmax(dot_p, 0.0),
			light->shine) * REFLECTIVITY);
}

/**
 * set_diffuse - Computes the diffuse lighting component.
 *
 * @normal: The surface normal at the collision point.
 * @light: Pointer to the light object.
 *
 * This function calculates the diffuse lighting using the Lambertian model,
 * which depends on the angle between the light source and the surface normal.
 * A larger dot product means the light is striking the surface more directly,
 * resulting in a brighter diffuse component.
 *
 * Returns:
 * - The computed diffuse intensity, scaled by light brightness.
 */
double	set_diffuse(t_vector normal, t_light *light)
{
	double	dot_p;

	dot_p = dot(normal, light->light_dir);
	if (dot_p < 0)
		return (0);
	return (light->obj->brightness * dot_p);
}

/**
 * print_light - Prints information about a light object.
 *
 * @l: Pointer to the light object.
 *
 * This function prints the light's location and brightness in a structured
 * format, including an emoji for clarity in terminal output.
 */
void	print_light(t_object *l)
{
	printf("Light:    💡\n");
	printf("Location: ");
	print_vector(l->location);
	printf("Brightness: %f\n", l->brightness);
}

/**
 * print_ambient - Prints information about the ambient lighting.
 *
 * @a: Pointer to the ambient light object.
 *
 * This function prints the ambient light's brightness and color in a
 * structured format, including an emoji for clarity in terminal output.
 */
void	print_ambient(t_object *a)
{
	printf("Ambient:  🌓\n");
	printf("Brightness: %f\n", a->brightness);
	printf("Color: ");
	print_color(a->color);
}
