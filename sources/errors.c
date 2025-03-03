/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzharkev <nzharkev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 13:38:45 by nzharkev          #+#    #+#             */
/*   Updated: 2025/02/20 15:14:03 by nzharkev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

/**
 * failure - Prints an error message and returns a failure code.
 *
 * @message: The error message to be displayed.
 *
 * This function prints an error message to the console and returns
 * FAILURE (1), which can be used to signal an error in function calls.
 *
 * Return: FAILURE (1).
 */
int	failure(char *message)
{
	ft_putstr_fd("Error\n\t", 2);
	ft_putendl_fd(message, 2);
	return (FAILURE);
}

/**
 * error_msg - Checks the state of the t_data structure and reports errors.
 *
 * @data: Pointer to the main program data structure.
 *
 * This function verifies whether critical components of the t_data structure
 * (such as objects, MLX, and the image buffer) have been initialized properly.
 * If any of these components are NULL, an error message is displayed.
 *
 * If `data` itself is NULL, the function reports that the data structure
 * failed to initialize and exits early.
 */
void	error_msg(t_data *data)
{
	if (!data)
	{
		failure("Data structure failed");
		return ;
	}
	if (!data->objects)
	{
		failure("Failed create data objects");
		return ;
	}
	if (!data->mlx)
		failure("MLX failed to initialize");
	if (!data->image)
		failure("No image");
	return ;
}
