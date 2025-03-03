/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@hive.fi>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:50:26 by amaula            #+#    #+#             */
/*   Updated: 2025/02/26 14:17:25 by amaula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

/**
 * assign_checks - Assigns the appropriate validation functions
 *                 for each object type.
 *
 * @type: The type of the object to validate.
 * @checks: An array of function pointers to validation functions.
 *
 * Description:
 * This function maps each object type to its corresponding validation
 * function. It ensures that the correct checks are applied to the object.
 */
static void	assign_checks(t_type type, int (**checks)(char *))
{
	if (type == AMBIENT)
		ambient_checks(checks);
	else if (type == CAMERA)
		camera_checks(checks);
	else if (type == LIGHT)
		lights_checks(checks);
	else if (type == SPHERE)
		sphere_checks(checks);
	else if (type == PLANE)
		plane_checks(checks);
	else if (type == CYLINDER)
		cylinder_checks(checks);
}

/**
 * next_value - Finds the next non-space value in a string.
 *
 * @ptr: A pointer to the current position in the string.
 *
 * Description:
 * This function finds the next value by searching for a space (' ') character,
 * then skipping over any whitespace that follows it.
 *
 * Return: A pointer to the next value in the string.
 *         Returns NULL if no further values are found.
 */
static char	*next_value(char *ptr)
{
	ptr = ft_strchr(ptr, ' ');
	if (ptr == NULL)
		return (NULL);
	while (ft_isspace(*ptr))
		ptr++;
	return (ptr);
}

/**
 * validate - Validates the format of a given line.
 *
 * @line: The line to be validated.
 *
 * Description:
 * This function ensures that a line follows the correct format for a
 * specific object type. It assigns the necessary validation functions
 * and checks each value in the line accordingly. If any validation fails
 * or if there are extra values in the line, the function returns FAILURE.
 *
 * Return: SUCCESS if the line is valid, FAILURE otherwise.
 */
int	validate(char *line)
{
	int		(*checks[6])(char *);
	int		i;
	t_type	type;

	type = get_type(line);
	if (line == NULL || ft_isspace(*line) || *line == '\0' || type == NONE)
		return (FAILURE);
	assign_checks(type, checks);
	i = 0;
	while (checks[i] != NULL)
	{
		line = next_value(line);
		if (line == NULL || (checks[i])(line) == 0)
			return (failure("Value validation failed"));
		i++;
	}
	line = next_value(line);
	if (line != NULL && *line != '\0')
		return (failure("Extra parameters"));
	return (SUCCESS);
}
