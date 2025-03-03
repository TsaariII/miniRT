/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzharkev <nzharkev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:52:49 by amaula            #+#    #+#             */
/*   Updated: 2025/02/20 15:10:56 by nzharkev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

/**
 * compute_normal_curved - Computes the normal vector at a point on
 *                         a curved surface of a cylinder.
 *
 * @collision_point: The point of collision on the cylinder's surface.
 * @cy: Pointer to the cylinder object.
 *
 * This function calculates the surface normal for a cylinder by:
 * - Finding the vector from the cylinder's base to the collision point.
 * - Projecting this vector onto the cylinder's axis.
 * - Subtracting the projection to get the normal.
 * - Normalizing the result.
 *
 * Returns:
 * - The normalized surface normal vector.
 */
t_vector	compute_normal_curved(t_vector collision_point, t_object *cy)
{
	t_vector	to_point;
	t_vector	projection;
	t_vector	normal;

	to_point = v_sub(collision_point, cy->location);
	projection = v_mul(dot(to_point, cy->orientation), cy->orientation);
	normal = v_sub(to_point, projection);
	return (normalize_vector(normal));
}

/**
 * update_ray - Updates ray properties after a collision is detected.
 *
 * @ray: Pointer to the ray to be updated.
 * @object: Pointer to the object the ray collided with.
 * @t: Distance from the ray's origin to the collision point.
 *
 * This function:
 * - Updates the ray's color based on the object's color.
 * - Computes the collision point.
 * - Determines the surface normal based on the object type:
 *   - Sphere: Normal is from center to collision point.
 *   - Plane: Normal is constant (given by the plane's orientation).
 *   - Cylinder: Uses compute_normal_curved() for curved surfaces.
 * - Ensures the normal is oriented outward.
 */
void	update_ray(t_ray *ray, t_object *object, double t)
{
	ray->color = object->color;
	ray->distance = t;
	ray->end = v_sum(ray->start, v_mul(ray->distance, ray->direction));
	if (object->type == SPHERE)
		ray->coll_norm = normalize_vector(v_sub(ray->end, object->location));
	if (object->type == PLANE)
		ray->coll_norm = object->orientation;
	if (object->type == CYLINDER)
		ray->coll_norm = compute_normal_curved(ray->end, object);
	if (dot(ray->coll_norm, ray->direction) <= 0)
		ray->coll_norm = v_mul(-1, ray->coll_norm);
	ray->object = object;
}

/**
 * calc_t - Solves for the parameter 't' in a quadratic equation
 *          for ray-object intersection.
 *
 * @t: Pointer to store the valid intersection distance.
 * @v1: Direction component of the quadratic equation.
 * @v2: Origin component of the quadratic equation.
 * @r: Radius of the object (e.g., sphere or cylinder).
 *
 * This function calculates the roots of the quadratic equation:
 *   ax² + bx + c = 0, where:
 *   - a = dot(v1, v1)
 *   - b = 2 * dot(v1, v2)
 *   - c = dot(v2, v2) - r²
 * If no real roots exist (discriminant < 0), it returns FAILURE.
 * If there are valid intersections, the closest positive root is selected.
 *
 * Returns:
 * - SUCCESS (0) if a valid intersection is found.
 * - FAILURE (1) if there is no valid intersection.
 */
double	calc_t(double *t, t_vector v1, t_vector v2, double r)
{
	double	t1;
	double	t2;
	t_disc	disc;

	disc.a = dot(v1, v1);
	disc.b = 2 * dot(v1, v2);
	disc.c = dot(v2, v2) - r * r;
	disc.discriminant = disc.b * disc.b - 4 * disc.a * disc.c;
	if (disc.discriminant < 0)
		return (FAILURE);
	t1 = (-disc.b - sqrt(disc.discriminant)) / (2 * disc.a);
	t2 = (-disc.b + sqrt(disc.discriminant)) / (2 * disc.a);
	if (t1 < 0 && t2 < 0)
		return (FAILURE);
	if (t1 > 0)
		*t = t1;
	else
		*t = t2;
	return (SUCCESS);
}
