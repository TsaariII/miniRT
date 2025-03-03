/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@hive.fi>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:53:48 by amaula            #+#    #+#             */
/*   Updated: 2025/02/27 15:42:45 by amaula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

/**
 * select_object - Selects an object and updates the current selection.
 *
 * @object: The object to be selected.
 * @data: The main data structure containing the scene.
 *
 * This function updates the `selected` pointer in the `data` structure
 * to point to the specified object. It then prints the details of
 * the selected object using its `print_object` function.
 */
void	select_object(t_object *object, t_data *data)
{
	data->selected = object;
	printf("Object selected: \n");
	object->print_object(object);
}

/**
 * min - Returns the minimum of two integers.
 *
 * @a: The first integer.
 * @b: The second integer.
 *
 * Return: The smaller of the two integers.
 */
int	min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

/**
 * max - Returns the maximum of two integers.
 *
 * @a: The first integer.
 * @b: The second integer.
 *
 * Return: The larger of the two integers.
 */
int	max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

/**
 * trim_newline - Removes the newline character at the end of a string.
 *
 * @str: The string to be processed.
 *
 * Note: The function allocates memory for a new string if a newline is found
 *       and frees the original string.
 *
 * Return: A new string without the trailing newline.
 *         If no newline is present, returns the original string.
 *         Returns NULL if the input string is NULL.
 */
char	*trim_newline(char *str)
{
	char	*trimmed;
	size_t	len;

	if (str == NULL)
		return (NULL);
	len = ft_strlen(str);
	if (str[len - 1] == '\n')
		trimmed = ft_substr(str, 0, len - 1);
	else
		return (str);
	free(str);
	return (trimmed);
}

void	light_helper(t_vector *f_col, t_data *data, t_ray *ray)
{
	if (HAS_COLOR == 1)
	{
		f_col->x += data->light->diff * (((ray->color >> 24) & 0xff)
				+ ((data->light->obj->color >> 24) & 0xff));
		f_col->y += data->light->diff * (((ray->color >> 16) & 0xff)
				+ ((data->light->obj->color >> 16) & 0xff));
		f_col->z += data->light->diff * (((ray->color >> 8) & 0xff)
				+ ((data->light->obj->color >> 8) & 0xff));
	}
	else
	{
		f_col->x += data->light->diff * ((ray->color >> 24) & 0xff);
		f_col->y += data->light->diff * ((ray->color >> 16) & 0xff);
		f_col->z += data->light->diff * ((ray->color >> 8) & 0xff);
	}
}
