/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@hive.fi>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:33:10 by nzharkev          #+#    #+#             */
/*   Updated: 2025/02/25 12:13:35 by amaula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

/**
 * the_image - Initializes the MLX loop and sets up image rendering.
 *
 * @data: Pointer to the main data structure containing scene information.
 *
 * This function sets up the event hooks for handling key presses and mouse
 * interactions, displays the rendered image on the window, and enters the MLX
 * event loop. It also enables image stretching and terminates the MLX instance
 * upon exit.
 */
static int	the_image(t_data *data)
{
	mlx_key_hook(data->mlx, &keypress, data);
	if (mlx_image_to_window(data->mlx, data->image, 0, 0) == -1)
		return (FAILURE);
	mlx_set_setting(MLX_STRETCH_IMAGE, 1);
	mlx_loop_hook(data->mlx, &rt_mouse, data);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
	return (SUCCESS);
}

/**
 * format_validation - Checks if the input file has a valid .rt format.
 *
 * @str: The filename string to validate.
 *
 * This function ensures that the input file has a `.rt` extension. If the file
 * does not have the correct format, it returns a failure message.
 *
 * Returns:
 * - SUCCESS (0) if the file format is valid.
 * - FAILURE (1) if the file format is incorrect.
 */
static int	format_validation(char *str)
{
	int		len;
	int		fd;
	char	file[1];

	len = ft_strlen(str);
	if (ft_strncmp(&str[len - 3], ".rt", 3) != 0)
		return (failure("Wrong file type"));
	fd = open(str, O_RDONLY);
	if (read(fd, file, 1) == -1)
	{
		close(fd);
		return (failure("Could not read"));
	}
	close(fd);
	return (SUCCESS);
}

/**
 * main - Entry point of the ray tracer.
 *
 * @argc: Number of command-line arguments.
 * @argv: Array of command-line arguments.
 *
 * This function validates input arguments, ensures the file format is correct,
 * initializes the data structure, performs ray tracing, and starts the rendering
 * loop. If any initialization step fails, it prints an error message and exits
 * gracefully.
 *
 * Returns:
 * - SUCCESS (0) if the program runs successfully.
 * - FAILURE (1) if an error occurs during initialization or execution.
 */
int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc != 2)
		return (failure("Wrong amount of arguments!"));
	if (format_validation(argv[1]) == FAILURE)
		return (FAILURE);
	data = init_data(argv[1]);
	if (data == NULL)
		return (FAILURE);
	raycast(data);
	if (the_image(data))
	{
		free_data(data);
		return (FAILURE);
	}
	free_data(data);
	return (SUCCESS);
}
