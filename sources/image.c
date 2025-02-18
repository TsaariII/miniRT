/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzharkev <nzharkev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:28:16 by nzharkev          #+#    #+#             */
/*   Updated: 2025/02/18 15:08:42 by nzharkev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

/**
 * redraw - Recalculates and redraws the scene.
 *
 * @data: Pointer to the main program data structure.
 *
 * This function updates any necessary precalculations, performs
 * raycasting to render the scene, and then displays the updated image
 * using the MLX graphics library.
 */
void	redraw(t_data *data)
{
	set_precalculations(data);
	raycast(data);
	mlx_image_to_window(data->mlx, data->image, 0, 0);
}

/**
 * reset_scene - Clears and reloads the scene from the file.
 *
 * @data: Pointer to the main program data structure.
 *
 * This function frees the current object array and resets the scene by
 * marking the camera, light, and ambient light as uninitialized (`NONE`).
 * It then reloads the objects from the scene file, selects the camera as
 * the default object, and triggers a redraw of the scene.
 *
 * After execution, the scene is fully reset and re-rendered.
 */
void	reset_scene(t_data *data)
{
	free_objarr(data->objects);
	data->camera->type = NONE;
	data->light->obj->type = NONE;
	data->ambient->obj->type = NONE;
	read_objects(data);
	data->selected = data->camera;
	printf("Scene resetted\n");
	redraw(data);
}
