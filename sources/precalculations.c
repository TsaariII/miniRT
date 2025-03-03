/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precalculations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzharkev <nzharkev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:30:15 by amaula            #+#    #+#             */
/*   Updated: 2025/02/26 15:58:33 by nzharkev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

/**
 * calc_view_distance - Calculates the view distance for the camera.
 *
 * @fov: The field of view in degrees.
 *
 * This function converts the field of view (FOV) from degrees to radians
 * and calculates the distance from the camera to the image plane.
 * The formula used is:
 *   distance = (X / 2) / tan(FOV / 2)
 *
 * Return: The computed view distance.
 */
static double	calc_view_distance(int fov)
{
	double	fov_rad;

	fov_rad = fov * M_PI / 180;
	return ((X / 2) / tan(fov_rad / 2));
}

/**
 * image_plane - Computes the image plane parameters based on the camera.
 *
 * @camera: Pointer to the camera object.
 *
 * This function calculates the camera's image plane orientation.
 * It determines the right (u) and up (v) vectors for the camera,
 * ensuring that the up vector remains stable for edge cases (like
 * when the camera is pointing straight up or down).
 *
 * - u: The right vector, computed as the cross product of the up vector
 *      and the camera direction.
 * - v: The up vector, computed as the cross product of the camera
 *      direction and u.
 *
 * If the camera is looking straight up or down, a different up vector
 * is chosen to avoid instability.
 *
 * Return: A structure containing the computed image plane properties.
 */
t_image_plane	image_plane(t_object *camera)
{
	t_image_plane	info;
	t_vector		up;

	info.view_distance = calc_view_distance(camera->fov);
	up = vector(0, -1, 0);
	if (fabs(camera->orientation.y) > 0.99)
		up = vector(1, 0, 0);
	info.u = normalize_vector(cross_product(up, camera->orientation));
	info.v = normalize_vector(cross_product(camera->orientation, info.u));
	if (dot(info.v, up) < 0)
		info.v = v_mul(-1, info.v);
	info.ray.start = camera->location;
	info.ray.end = camera->location;
	info.ray.direction = v_mul(info.view_distance, camera->orientation);
	info.ray.direction = v_sum(camera->location, info.ray.direction);
	info.ray.color = BACKGROUND_COLOR;
	info.ray.distance = DBL_MAX;
	info.ray.object = NULL;
	return (info);
}

/**
 * set_precalculations - Updates image plane parameters in the scene data.
 *
 * @data: Pointer to the scene data structure.
 *
 * This function recalculates the camera's image plane and updates
 * the relevant fields in the `t_data` structure.
 */
void	set_precalculations(t_data *data)
{
	data->info = image_plane(data->camera);
}
