/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzharkev <nzharkev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:49:53 by amaula            #+#    #+#             */
/*   Updated: 2025/02/20 15:11:02 by nzharkev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

/**
 * cylinder_checks - Initializes an array of validation functions for a cylinder.
 *
 * @checks: Array of function pointers to validation functions.
 *
 * This function sets up an array of functions that check if each component
 * of a cylinder's description is valid. The expected input format is:
 *   - checks[0]: Vector (location)
 *   - checks[1]: Vector (orientation)
 *   - checks[2]: Double (diameter)
 *   - checks[3]: Double (height)
 *   - checks[4]: Color (RGB)
 *   - checks[5]: NULL (end of list)
 */
void	cylinder_checks(int (**checks)(char *))
{
	checks[0] = &is_vector;
	checks[1] = &is_vector;
	checks[2] = &is_double;
	checks[3] = &is_double;
	checks[4] = &is_color;
	checks[5] = NULL;
}

/**
 * assign_cylinder - Parses and assigns cylinder properties from input data.
 *
 * @cylinder: Pointer to the cylinder object to initialize.
 * @info: Array of strings containing cylinder parameters.
 *
 * This function extracts cylinder properties from the `info` array:
 *   - Location (vector)
 *   - Orientation (vector, must be normalized)
 *   - Diameter (positive double)
 *   - Height (positive double)
 *   - Color (RGB integer)
 *
 * If the cylinder orientation is not a unit vector, an error is returned.
 * The function assigns collision detection and printing functions to the object.
 *
 * Return: SUCCESS (0) on success, FAILURE (1) if an error occurs.
 */
int	assign_cylinder(t_object *cylinder, char **info)
{
	cylinder->location = parse_vector(info[1]);
	cylinder->orientation = parse_vector(info[2]);
	if (info[3][0] == '-')
		return (failure("Diameter cannot be negative value"));
	cylinder->diameter = parse_double(info[3]);
	cylinder->height = parse_double(info[4]);
	cylinder->color = parse_color(info[5]);
	if (!is_normalized_vector(cylinder->orientation))
		return (failure("Cylinder orientation not normalized"));
	cylinder->collisionf = &cylinder_collision;
	cylinder->print_object = &print_cylinder;
	return (SUCCESS);
}

/**
 * print_cylinder - Prints cylinder properties in a readable format.
 *
 * @c: Pointer to the cylinder object.
 *
 * This function prints the following properties:
 *   - Location (vector)
 *   - Orientation (vector)
 *   - Diameter (double)
 *   - Height (double)
 *   - Color (RGB)
 */
void	print_cylinder(t_object *c)
{
	printf("Cylinder: 🛢️\n");
	printf("Location: ");
	print_vector(c->location);
	printf("Orientation: ");
	print_vector(c->orientation);
	printf("Diameter: %f\n", c->diameter);
	printf("Height: %f\n", c->height);
	printf("Color: ");
	print_color(c->color);
}
