/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@hive.fi>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:53:05 by amaula            #+#    #+#             */
/*   Updated: 2025/02/26 14:13:04 by amaula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

/**
 * camera_checks - Initializes an array of function pointers
 *                 for validating camera parameters.
 *
 * @checks: Pointer to an array of function pointers.
 *
 * The function assigns appropriate validation functions to check
 * camera attributes:
 * - Position: Validated as a vector.
 * - Orientation: Validated as a vector.
 * - Field of View (FOV): Validated as an integer.
 * The last element is set to NULL to mark the end of the array.
 */
void	camera_checks(int (**checks)(char *))
{
	checks[0] = &is_vector;
	checks[1] = &is_vector;
	checks[2] = &is_int;
	checks[3] = NULL;
}

/**
 * assign_camera - Parses and assigns values to a camera object.
 *
 * @camera: Pointer to the camera object to be initialized.
 * @info: Array of strings containing the camera's attributes.
 *
 * This function:
 * - Parses position and orientation vectors.
 * - Parses and validates the FOV (must be between 0 and 180).
 * - Assigns a print function for debugging.
 *
 * Returns:
 * - SUCCESS (0) if the camera is correctly assigned.
 * - FAILURE (1) if FOV is out of range.
 */
int	assign_camera(t_object *camera, char **info)
{
	camera->location = parse_vector(info[1]);
	camera->orientation = parse_vector(info[2]);
	camera->fov = ft_atoi(info[3]);
	if (!is_normalized_vector(camera->orientation))
		return (failure("Camera orientation not normalized"));
	if (camera->fov < 0 || camera->fov > 180)
		return (failure("FOV not valid"));
	camera->print_object = &print_camera;
	return (SUCCESS);
}

/**
 * print_camera - Prints the details of a camera object.
 *
 * @c: Pointer to the camera object to be printed.
 *
 * This function prints the camera's location and orientation in a
 * formatted manner. A camera emoji is used for a visual indication.
 */
void	print_camera(t_object *c)
{
	printf("Camera:   📷\n");
	printf("Location: ");
	print_vector(c->location);
	printf("Orientation: ");
	print_vector(c->orientation);
}
