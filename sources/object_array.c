/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzharkev <nzharkev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:03:37 by nzharkev          #+#    #+#             */
/*   Updated: 2025/02/18 14:03:39 by nzharkev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_objarr	*init_objarr(size_t capacity)
{
	t_objarr	*objarr;
	t_object	*arr;

	objarr = malloc(sizeof(t_objarr));
	arr = malloc(capacity * sizeof(t_object));
	if (objarr == NULL || arr == NULL)
	{
		free(objarr);
		return (NULL);
	}
	ft_memset(arr, 0, capacity * sizeof(t_object));
	objarr->arr = arr;
	objarr->capacity = capacity;
	objarr->objects = 0;
	return (objarr);
}

static int	reallocate(t_objarr *objarr)
{
	t_object	*new_arr;
	size_t		i;

	objarr->capacity *= 2;
	new_arr = malloc(objarr->capacity * sizeof(t_object));
	if (new_arr == NULL)
		return (FAILURE);
	ft_memset(new_arr, 0, objarr->capacity * sizeof(t_object));
	i = 0;
	while (i < objarr->objects)
	{
		new_arr[i] = objarr->arr[i];
		i++;
	}
	free(objarr->arr);
	objarr->arr = new_arr;
	return (SUCCESS);
}

/*	Adds an object to the array
	parse_object parses that object from line
	if array is full, doubles the arrays allocated memory
	CLA are instead put in data */
int	add_object(t_data *data, char *line)
{
	t_object	*object;

	if (validate(line) == FAILURE)
		return (failure("Validation failed"));
	if (line[0] == 'C')
		return (parse_object(data->camera, line));
	if (line[0] == 'L')
		return (parse_object(data->light->obj, line));
	if (line[0] == 'A')
		return (parse_object(data->ambient->obj, line));
	if (data->objects->capacity == data->objects->objects)
		if (reallocate(data->objects) == FAILURE)
			return (FAILURE);
	object = data->objects->arr + data->objects->objects;
	if (parse_object(object, line) == FAILURE)
		return (FAILURE);
	data->objects->objects++;
	return (SUCCESS);
}

void	free_objarr(t_objarr *objarr)
{
	if (objarr == NULL)
		return ;
	free(objarr->arr);
	free(objarr);
}
