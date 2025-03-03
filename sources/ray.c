/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzharkev <nzharkev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:52:26 by amaula            #+#    #+#             */
/*   Updated: 2025/02/24 15:51:12 by nzharkev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

/**
 * get_reflection - Computes the reflected ray direction.
 *
 * @ray: The incident ray that hits a reflective surface.
 *
 * This function calculates the reflection of a ray off a surface using
 * the reflection formula:
 *     R = D - 2 * (D . N) * N
 * where D is the incident ray direction and N is the surface normal.
 *
 * The new ray starts slightly offset from the collision point to prevent
 * self-intersections.
 *
 * Returns: A new reflected ray.
 */
static t_ray	get_reflection(t_ray *ray)
{
	t_ray	r;
	double	dot_p;

	ft_memset(&r, 0, sizeof(t_ray));
	dot_p = dot(ray->direction, ray->coll_norm);
	r.direction = v_sub(ray->direction, v_mul(2 * dot_p, ray->coll_norm));
	r.direction = normalize_vector(r.direction);
	r.start = v_sum(ray->end, v_mul(EPSILON, r.direction));
	r.distance = DBL_MAX;
	r.color = BACKGROUND_COLOR;
	r.object = NULL;
	return (r);
}

/**
 * get_ray - Computes the primary ray for a pixel.
 *
 * @info: The image plane and camera data.
 * @x: The x-coordinate of the pixel.
 * @y: The y-coordinate of the pixel.
 *
 * This function generates a primary ray originating from the camera
 * and passing through the given pixel. The direction is computed
 * based on the camera's basis vectors.
 *
 * Returns: The computed ray.
 */
t_ray	get_ray(t_image_plane info, int x, int y)
{
	t_ray		ray;

	ray = info.ray;
	ray.direction = v_sum(ray.direction, v_mul((-X / 2 + x + 0.5), info.u));
	ray.direction = v_sum(ray.direction, v_mul((-Y / 2 + y + 0.5), info.v));
	ray.direction = normalize_vector(ray.direction);
	return (ray);
}

/**
 * cast_ray - Traces a ray through the scene, checking for intersections.
 *
 * @ray: The ray to be cast.
 * @data: The scene data.
 * @reflections: The number of allowed reflections.
 *
 * This function iterates through all objects to determine the closest
 * intersection. If reflections are enabled, the function calculates
 * the reflected ray and blends colors accordingly.
 *
 * Returns: 1 if a collision occurs, 0 otherwise.
 */
int	cast_ray(t_ray *ray, t_data *data, int reflections)
{
	size_t		i;
	int			is_collision;
	t_object	*arr;
	t_ray		r;

	is_collision = 0;
	i = 0;
	arr = data->objects->arr;
	while (i < data->objects->objects)
	{
		if ((*(arr[i].collisionf))(ray, &arr[i]) == HIT)
			is_collision = 1;
		i++;
	}
	if (reflections > 0 && is_collision && REFLECTIVITY > 0)
	{
		r = get_reflection(ray);
		if (cast_ray(&r, data, reflections - 1) == HIT)
			r.color = set_lights(data, &r, r.end);
		ray->color = mix_colors(ray->color, r.color, REFLECTIVITY);
	}
	return (is_collision);
}

/**
 * raycast - Performs ray tracing for the entire image.
 *
 * @data: The scene data containing objects, lights, and camera.
 *
 * This function iterates over every pixel in the image, casting a ray
 * and determining the pixel color. The final image is then stored in
 * the `data->image` buffer.
 */
void	raycast(t_data *data)
{
	int		x;
	int		y;
	t_ray	ray;

	y = 0;
	while (y < Y)
	{
		x = 0;
		while (x < X)
		{
			ray = get_ray(data->info, x, y);
			if (cast_ray(&ray, data, REFLECTIONS) == HIT)
				ray.color = set_lights(data, &ray, ray.end);
			color_pixel(data->image, ray.color, x, y);
			x++;
		}
		printf("%d%%    \r", y * 100 / Y);
		y++;
	}
	printf("Ready\n");
}
