/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzharkev <nzharkev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:52:32 by amaula            #+#    #+#             */
/*   Updated: 2025/02/20 15:06:41 by nzharkev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

/**
 * sphere_checks - Sets validation functions for sphere properties.
 *
 * @checks: An array of function pointers used to validate input values.
 *
 * This function assigns the appropriate validation functions for:
 * - Position (vector)
 * - Diameter (double)
 * - Color (RGB format)
 * The last element is set to NULL to indicate the end of the array.
 */
void	sphere_checks(int (**checks)(char *))
{
	checks[0] = &is_vector;
	checks[1] = &is_double;
	checks[2] = &is_color;
	checks[3] = NULL;
}

/**
 * assign_sphere - Parses and assigns properties to a sphere object.
 *
 * @sphere: The sphere object to be initialized.
 * @info: The array of string values representing sphere properties.
 *
 * This function extracts and assigns:
 * - Location (parsed from `info[1]`)
 * - Diameter (parsed from `info[2]`)
 * - Color (parsed from `info[3]`)
 *
 * If the diameter is negative, the function returns a failure.
 *
 * Returns: SUCCESS if assignment is valid, FAILURE otherwise.
 */
int	assign_sphere(t_object *sphere, char **info)
{
	sphere->location = parse_vector(info[1]);
	if (info[2][0] == '-')
		return (failure("Diameter cannot be negative value"));
	sphere->diameter = parse_double(info[2]);
	sphere->color = parse_color(info[3]);
	sphere->collisionf = &sphere_collision;
	sphere->print_object = &print_sphere;
	return (SUCCESS);
}

/**
 * print_sphere - Displays information about a sphere object.
 *
 * @s: The sphere object to be printed.
 *
 * Prints:
 * - The sphere's emoji representation (⚪)
 * - Location (x, y, z)
 * - Diameter
 * - Color (printed in RGB format)
 */
void	print_sphere(t_object *s)
{
	printf("Sphere:   ⚪\n");
	printf("Location: ");
	print_vector(s->location);
	printf("Diameter: %f\n", s->diameter);
	printf("Color: ");
	print_color(s->color);
}
