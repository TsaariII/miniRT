/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzharkev <nzharkev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:51:09 by amaula            #+#    #+#             */
/*   Updated: 2025/02/20 15:14:19 by nzharkev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

/**
 * plane_checks - Initializes validation functions for a plane.
 *
 * @checks: Array of function pointers for checking input values.
 *
 * This function sets up validation checks for:
 * - Position vector
 * - Orientation vector
 * - Color
 * The last element in the array is set to NULL to indicate the end.
 */
void	plane_checks(int (**checks)(char *))
{
	checks[0] = &is_vector;
	checks[1] = &is_vector;
	checks[2] = &is_color;
	checks[3] = NULL;
}

/**
 * assign_plane - Assigns values to a plane object.
 *
 * @plane: Pointer to the plane object to be initialized.
 * @info: Array of strings containing object data.
 *
 * This function extracts and validates:
 * - Position (Vector)
 * - Orientation (Vector within range [-1.0, 1.0])
 * - Color (RGB)
 * The orientation vector is normalized and stored in the object.
 * If the orientation is invalid or not normalized, it returns an error.
 *
 * Return: SUCCESS (0) on success, FAILURE (1) on error.
 */
int	assign_plane(t_object *plane, char **info)
{
	plane->location = parse_vector(info[1]);
	plane->orientation = parse_vector(info[2]);
	if ((plane->orientation.x > 1.0 || plane->orientation.x < -1.0)
		|| (plane->orientation.y > 1.0 || plane->orientation.y < -1.0)
		|| (plane->orientation.z > 1.0 || plane->orientation.z < -1.0))
		return (failure("Orientation should be [1.0, -1.0]"));
	plane->color = parse_color(info[3]);
	if (!is_normalized_vector(plane->orientation))
		return (failure("Plane orientation not normalized"));
	plane->collisionf = &plane_collision;
	plane->print_object = &print_plane;
	return (SUCCESS);
}

/**
 * print_plane - Prints information about a plane object.
 *
 * @p: Pointer to the plane object to be printed.
 *
 * This function prints:
 * - The object's type (Plane)
 * - Position vector
 * - Orientation vector
 * - Color (in RGB format)
 */
void	print_plane(t_object *p)
{
	printf("Plane:    ✈️\n");
	printf("Location: ");
	print_vector(p->location);
	printf("Orientation: ");
	print_vector(p->orientation);
	printf("Color: ");
	print_color(p->color);
}
