/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzharkev <nzharkev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:50:59 by amaula            #+#    #+#             */
/*   Updated: 2025/02/18 16:03:58 by nzharkev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

/**
 * is_cs_double - Checks if a string represents a valid coordinate system double.
 *
 * @ptr: The string to check.
 *
 * Return: 1 if valid, 0 otherwise.
 *
 * Description:
 * A coordinate system double is a floating-point number that:
 * - May start with a minus sign '-'.
 * - Contains at most one period '.'.
 * - Contains at least one digit.
 * - Ends at a space, null terminator, or comma.
 */
static int	is_cs_double(char *ptr)
{
	int	periods;
	int	digits;

	periods = 0;
	digits = 0;
	if (*ptr == '-')
		ptr++;
	while (!ft_isspace(*ptr) && *ptr != '\0' && *ptr != ',')
	{
		if (ft_isdigit(*ptr))
			digits++;
		else if (*ptr == '.')
			periods++;
		else
			return (0);
		ptr++;
	}
	if (*ptr != ' ' && *ptr != '\0' && *ptr != ',')
		return (0);
	return (periods <= 1 && digits >= 1);
}

/**
 * is_double - Checks if a string represents a valid floating-point number.
 *
 * @ptr: The string to check.
 *
 * Return: 1 if valid, 0 otherwise.
 *
 * Description:
 * A valid floating-point number:
 * - May start with a minus sign '-'.
 * - Contains at most one period '.'.
 * - Contains at least one digit.
 * - Ends at a space or null terminator.
 */
int	is_double(char *ptr)
{
	int	periods;
	int	digits;

	periods = 0;
	digits = 0;
	if (*ptr == '-')
		ptr++;
	while (!ft_isspace(*ptr) && *ptr != '\0')
	{
		if (ft_isdigit(*ptr))
			digits++;
		else if (*ptr == '.')
			periods++;
		else
			return (0);
		ptr++;
	}
	if (*ptr != ' ' && *ptr != '\0')
		return (0);
	return (periods <= 1 && digits >= 1);
}

/**
 * is_color - Checks if a string represents a valid RGB color.
 *
 * @ptr: The string to check.
 *
 * Return: 1 if valid, 0 otherwise.
 *
 * Description:
 * A valid RGB color is formatted as "R,G,B":
 * - Contains exactly three integer values (0-255).
 * - Contains exactly two commas separating the values.
 * - Ends at a space or null terminator.
 */
int	is_color(char *ptr)
{
	int	commas;
	int	values;

	commas = 0;
	values = 0;
	while (!ft_isspace(*ptr) && *ptr != '\0')
	{
		if (ft_isdigit(*ptr) && ft_atoi(ptr) / 256 == 0)
			values++;
		while (ft_isdigit(*ptr))
			ptr++;
		if (*ptr != ',')
			break ;
		commas++;
		ptr++;
	}
	if (*ptr != ' ' && *ptr != '\0')
		return (0);
	return (values == 3 && commas == 2);
}

/**
 * is_vector - Checks if a string represents a valid 3D vector.
 *
 * @ptr: The string to check.
 *
 * Description:
 * A valid 3D vector is formatted as "x,y,z":
 * - Contains exactly three floating-point values.
 * - Contains exactly two commas separating the values.
 * - Ends at a space or null terminator.
 *
 * Return: 1 if valid, 0 otherwise.
 */
int	is_vector(char *ptr)
{
	int	commas;
	int	doubles;

	commas = 0;
	doubles = 0;
	while (!ft_isspace(*ptr) && *ptr != '.')
	{
		if (is_cs_double(ptr))
			doubles++;
		while (ft_isdigit(*ptr) || *ptr == '.' || *ptr == '-')
			ptr++;
		if (*ptr != ',')
			break ;
		commas++;
		ptr++;
	}
	if (*ptr != ' ' && *ptr != '\0')
		return (0);
	return (doubles == 3 && commas == 2);
}

/**
 * is_int - Checks if a string represents a valid integer.
 *
 * @ptr: The string to check.
 *
 * Description:
 * A valid integer:
 * - Consists only of digits (0-9).
 * - Ends at a space or null terminator.
 *
 * Return: 1 if valid, 0 otherwise.
 */
int	is_int(char *ptr)
{
	while (!ft_isspace(*ptr) && *ptr != '\0')
	{
		if (!ft_isdigit(*ptr))
			return (0);
		ptr++;
	}
	return (1);
}
