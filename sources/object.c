/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzharkev <nzharkev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:03:22 by nzharkev          #+#    #+#             */
/*   Updated: 2025/02/20 11:38:04 by nzharkev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

/**
 * assign_ambient - Assigns values to an ambient light object.
 *
 * @ambient: Pointer to the ambient light object.
 * @info: Array of strings containing brightness and color values.
 *
 * This function parses and assigns the brightness and color of the ambient
 * light. The brightness must be within the range [0.0, 1.0]. If the brightness
 * is invalid, an error message is displayed, and the function returns FAILURE.
 *
 * Return: SUCCESS if assignment is successful, otherwise FAILURE.
 */
static int	assign_ambient(t_object *ambient, char **info)
{
	ambient->brightness = parse_double(info[1]);
	ambient->color = parse_color(info[2]);
	if (ambient->brightness < 0.0 || ambient->brightness > 1.0)
		return (failure("Brightness should be [0.0, 1.0]"));
	ambient->print_object = &print_ambient;
	return (SUCCESS);
}

/**
 * assign_light - Assigns values to a light source object.
 *
 * @light: Pointer to the light object.
 * @info: Array of strings containing position and brightness values.
 *
 * This function parses and assigns the position and brightness of the light
 * source. The brightness must be within the range [0.0, 1.0]. If invalid, an
 * error message is displayed, and the function returns FAILURE.
 *
 * Return: SUCCESS if assignment is successful, otherwise FAILURE.
 */
static int	assign_light(t_object *light, char **info)
{
	light->location = parse_vector(info[1]);
	light->brightness = parse_double(info[2]);
	if (HAS_COLOR == 1)
		light->color = parse_color(info[3]);
	else
		light->color = parse_color("255,255,255");
	if (light->brightness > 1.0 || light->brightness < 0.0)
		return (failure("Brightness should be [0.0, 1.0]"));
	light->print_object = &print_light;
	return (SUCCESS);
}

/**
 * assign_values - Assigns values to an object based on its type.
 *
 * @object: Pointer to the object to be assigned values.
 * @info: Array of strings containing object-specific properties.
 *
 * This function determines the type of object and assigns its properties
 * accordingly by calling the appropriate assignment function.
 *
 * Return: SUCCESS if assignment is successful, otherwise FAILURE.
 */
static int	assign_values(t_object *object, char **info)
{
	if (object == NULL || info == NULL)
		return (FAILURE);
	if (object->type == AMBIENT)
		return (assign_ambient(object, info));
	else if (object->type == CAMERA)
		return (assign_camera(object, info));
	else if (object->type == LIGHT)
		return (assign_light(object, info));
	else if (object->type == SPHERE)
		return (assign_sphere(object, info));
	else if (object->type == PLANE)
		return (assign_plane(object, info));
	else if (object->type == CYLINDER)
		return (assign_cylinder(object, info));
	return (FAILURE);
}

/**
 * get_type - Determines the type of an object from a line of input.
 *
 * @line: The input string representing the object.
 *
 * This function checks if the input string matches a known object type
 * (e.g., Camera, Light, Sphere, etc.) and returns the corresponding type.
 *
 * Return: The type of the object, or NONE if no match is found.
 */
t_type	get_type(char *line)
{
	char	*shapes[7];
	int		i;

	shapes[CAMERA] = "C ";
	shapes[LIGHT] = "L ";
	shapes[AMBIENT] = "A ";
	shapes[SPHERE] = "sp ";
	shapes[PLANE] = "pl ";
	shapes[CYLINDER] = "cy ";
	shapes[NONE] = NULL;
	i = 0;
	while (shapes[i] != NULL)
	{
		if (ft_strncmp(shapes[i], line, ft_strlen(shapes[i])) == 0)
		{
			return (i);
		}
		i++;
	}
	return (NONE);
}

/**
 * parse_object - Parses an object from a line of input.
 *
 * @object: Pointer to the object to be parsed.
 * @line: The input string containing object data.
 *
 * This function determines the object type, splits the line into
 * properties, and assigns them to the object. If the assignment fails,
 * an error message is displayed.
 *
 * Return: SUCCESS if parsing is successful, otherwise FAILURE.
 */
int	parse_object(t_object *object, char *line)
{
	char		**info;

	object->type = get_type(line);
	info = ft_split(line, ' ');
	if (assign_values(object, info) == FAILURE)
	{
		ft_free_array(info);
		return (failure("assign_values FAILURE"));
	}
	ft_free_array(info);
	return (SUCCESS);
}
