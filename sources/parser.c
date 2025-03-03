/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@hive.fi>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:54:10 by amaula            #+#    #+#             */
/*   Updated: 2025/02/26 14:13:46 by amaula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

/**
 * fract_len - Calculates the length of the fractional part of a number.
 *
 * @ptr: Pointer to the start of the fractional part in a string.
 *
 * This function iterates through the fractional digits and counts them.
 *
 * Return: The number of digits in the fractional part.
 */
static size_t	fract_len(char *ptr)
{
	size_t	len;

	len = 0;
	while (ft_isdigit(ptr[len]))
		len++;
	return (len);
}

/**
 * parse_double - Parses a string into a double.
 *
 * @str: The string representation of a floating-point number.
 *
 * This function handles both integer and fractional parts, including
 * negative numbers. If no decimal point is found, it returns the integer part.
 *
 * Return: The parsed double value.
 */
double	parse_double(char *str)
{
	int		int_part;
	int		fract_part;
	int		sign;
	char	*dot;
	char	*comma;

	sign = 1;
	if (*str == '-')
	{
		str++;
		sign = -1;
	}
	int_part = 0;
	dot = ft_strchr(str, '.');
	comma = ft_strchr(str, ',');
	if (*str != '.')
		int_part = ft_atoi(str);
	if (dot == NULL || (comma != NULL && comma < dot))
		return (sign * (double)int_part);
	fract_part = ft_atoi(dot + 1);
	return ((sign * int_part)
		+ (sign * fract_part / pow(10, fract_len(dot + 1))));
}

/**
 * parse_vector - Parses a string into a 3D vector.
 *
 * @str: The string containing three comma-separated values.
 *
 * This function extracts the x, y, and z components of a vector from
 * a formatted string and returns a t_vector struct.
 *
 * Return: A t_vector structure with parsed values.
 */
t_vector	parse_vector(char *str)
{
	t_vector	v;

	v.x = parse_double(str);
	str = ft_strchr(str, ',') + 1;
	v.y = parse_double(str);
	str = ft_strrchr(str, ',') + 1;
	v.z = parse_double(str);
	return (v);
}

/**
 * parse_color - Parses a string into a 32-bit RGBA color.
 *
 * @str: The string containing three comma-separated integer values (R, G, B).
 *
 * This function extracts the red, green, and blue components and
 * combines them into a 32-bit unsigned integer with full opacity (alpha=255).
 *
 * Return: A uint32_t representing the color in ARGB format.
 */
uint32_t	parse_color(char *str)
{
	int	r;
	int	g;
	int	b;

	r = ft_atoi(str);
	g = ft_atoi(ft_strchr(str, ',') + 1);
	b = ft_atoi(ft_strrchr(str, ',') + 1);
	return (r << 24 | g << 16 | b << 8 | 255);
}
