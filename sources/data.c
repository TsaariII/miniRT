/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzharkev <nzharkev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 13:41:03 by nzharkev          #+#    #+#             */
/*   Updated: 2025/02/20 15:12:39 by nzharkev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

/**
 * mlx_and_image - Initializes the MLX library and creates an image.
 *
 * @data: Pointer to the main program data structure.
 *
 * This function initializes the MLX window and creates an image buffer
 * for rendering. If either initialization fails, an error message is
 * displayed and the function returns FAILURE.
 *
 * Return: SUCCESS (0) on success, FAILURE (1) on error.
 */
static int	mlx_and_image(t_data *data)
{
	data->mlx = mlx_init(X, Y, "miniRT", true);
	if (data->mlx == NULL)
	{
		error_msg(data);
		return (failure("MLX initialization failed"));
	}
	data->image = mlx_new_image(data->mlx, X, Y);
	if (data->image == NULL)
	{
		error_msg(data);
		return (failure("image initialization failed"));
	}
	return (SUCCESS);
}

/**
 * data_mallocs - Allocates and initializes memory for the t_data structure.
 *
 * @data: Pointer to the t_data structure.
 * @file: File path containing scene description.
 *
 * This function allocates memory for the main data structure, the ambient
 * light, the light source, and the camera. The first three objects in
 * `data->camera` are reserved for:
 *   - Camera (`data->camera`)
 *   - Light (`data->light->obj`)
 *   - Ambient light (`data->ambient->obj`)
 *
 * If any allocation fails, the function returns FAILURE.
 *
 * Return: SUCCESS (0) on success, FAILURE (1) on error.
 */
static int	data_mallocs(t_data *data, char *file)
{
	if (data == NULL)
		return (failure("malloc failed"));
	ft_bzero(&data->info, sizeof(t_image_plane));
	ft_bzero(data, sizeof(t_data));
	ft_bzero(&(data->mouse), sizeof(t_mouse));
	data->file = file;
	data->ambient = malloc(sizeof(t_ambient));
	data->light = malloc(sizeof(t_light));
	if (data->ambient == NULL || data->light == NULL)
		return (failure("malloc failed"));
	data->camera = malloc(sizeof(t_object) * 3);
	if (data->camera == NULL)
		return (failure("malloc failed"));
	data->light->obj = data->camera + 1;
	data->ambient->obj = data->camera + 2;
	data->camera->type = NONE;
	data->light->obj->type = NONE;
	data->ambient->obj->type = NONE;
	return (SUCCESS);
}

/**
 * init_data - Initializes the scene data and reads objects from file.
 *
 * @file: Path to the scene description file.
 *
 * This function allocates memory for the `t_data` structure and initializes
 * the necessary components, including reading scene objects and setting
 * up the MLX window and image. If any step fails, allocated memory is freed.
 *
 * Return: Pointer to the initialized t_data structure, or NULL on failure.
 */
t_data	*init_data(char *file)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (data_mallocs(data, file) == FAILURE
		|| read_objects(data) == FAILURE
		|| mlx_and_image(data) == FAILURE)
	{
		free_data(data);
		return (NULL);
	}
	print_objects(data);
	select_object(data->camera, data);
	return (data);
}

/**
 * free_data - Frees all allocated memory in the t_data structure.
 *
 * @data: Pointer to the t_data structure to be freed.
 *
 * This function ensures that all dynamically allocated objects, including
 * scene objects, lights, ambient lighting, and camera, are properly freed.
 * If `data` is NULL, the function does nothing.
 */
void	free_data(t_data *data)
{
	if (data == NULL)
		return ;
	free_objarr(data->objects);
	free(data->light);
	free(data->ambient);
	free(data->camera);
	free(data);
}
