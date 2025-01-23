#include "../includes/minirt.h"

int main(void)
{
	t_data	*data = init_data(1000, 750, "test.rt");
	if (data == NULL)
	{
		printf("data initialization failed\n");
		free_data(data);
		return (1);
	}
	get_camera(data)->view_distance = 1000;
	raycast(data);
	mlx_key_hook(data->win, handle_key, data);
	mlx_hook(data->win, 17, 0, handle_close, data);
	mlx_put_image_to_window(data->mlx, data->win, data->image->img, 0, 0);
	mlx_loop(data->mlx);
	return (0);
}
