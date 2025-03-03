/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzharkev <nzharkev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:49:29 by amaula            #+#    #+#             */
/*   Updated: 2025/02/20 15:42:19 by nzharkev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

/**
 * dot - Computes the dot product of two 3D vectors.
 *
 * @v1: The first vector.
 * @v2: The second vector.
 *
 * Description:
 * The dot product is calculated as:
 *     dot(v1, v2) = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z
 * It measures the similarity between two vectors:
 * - If the result is > 0, the vectors point in a similar direction.
 * - If the result is < 0, the vectors point in opposite directions.
 * - If the result is 0, the vectors are perpendicular.
 *
 * Return: The dot product of v1 and v2.
 */
double	dot(t_vector v1, t_vector v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

/**
 * cross_product - Computes the cross product of two 3D vectors.
 *
 * @v1: The first vector.
 * @v2: The second vector.
 *
 * Description:
 * The cross product is calculated as:
 *     product.x = v1.y * v2.z - v1.z * v2.y
 *     product.y = v1.z * v2.x - v1.x * v2.z
 *     product.z = v1.x * v2.y - v1.y * v2.x
 * The resulting vector is perpendicular to both input vectors.
 * This is useful for computing normal vectors in 3D geometry.
 *
 * Return: A vector perpendicular to both v1 and v2.
 */
t_vector	cross_product(t_vector v1, t_vector v2)
{
	t_vector	product;

	product.x = v1.y * v2.z - v1.z * v2.y;
	product.y = v1.z * v2.x - v1.x * v2.z;
	product.z = v1.x * v2.y - v1.y * v2.x;
	return (product);
}

/**
 * vector - Creates a 3D vector with the given components.
 *
 * @x: The x-coordinate.
 * @y: The y-coordinate.
 * @z: The z-coordinate.
 *
 * Description:
 * This function initializes and returns a vector with
 * the provided x, y, and z values.
 *
 * Return: A t_vector structure with the specified coordinates.
 */
t_vector	vector(double x, double y, double z)
{
	t_vector	v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

/**
 * reflect_vector - Computes the reflection of a light vector off a surface.
 *
 * @light_dir: The incident light direction.
 * @normal: The surface normal.
 *
 * Description:
 * The reflection is calculated using the formula:
 *     R = 2 * (N • L) * N - L
 * Where:
 * - R is the reflected vector.
 * - N is the normal vector.
 * - L is the incident light direction.
 * This is useful for implementing specular lighting in ray tracing.
 *
 * Return: The reflected light direction.
 */
t_vector	reflect_vector(t_vector light_dir, t_vector normal)
{
	return (v_sub(v_mul(2 * dot(normal, light_dir), normal),
			light_dir));
}

/**
 * is_normalized_vector - Checks if a vector is normalized.
 *
 * @v: The vector to check.
 *
 * Description:
 * A normalized vector has a length of 1. This function checks whether
 * the length of the given vector is within the range [1 - EPSILON, 1 + EPSILON].
 * This is useful for ensuring that direction vectors remain unit-length.
 *
 * Return: 1 if the vector length is approximately 1, otherwise 0.
 */
int	is_normalized_vector(t_vector v)
{
	return (v_len(v) < 1 + EPSILON && v_len(v) > 1 - EPSILON);
}
