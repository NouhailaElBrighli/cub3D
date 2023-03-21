#include "../parsing/parsing.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	//protection
	dst = data->ptr->addr + (y * data->ptr->line_length + x * (data->ptr->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	render_2D(t_data *data)
{
	int row;

	mlx_clear_window(data->ptr->mlx, data->ptr->win);
	data->ptr->img = mlx_new_image(data->ptr->mlx, data->ptr->tile_size * data->long_line, data->ptr->tile_size * data->size);
	data->ptr->addr = mlx_get_data_addr(data->ptr->img , &(data->ptr->bits_per_pixel), &(data->ptr->line_length), &(data->ptr->endian));
	row = data->index;
	while (data->map[row])
	{
		Draw_walls(data, data->map[row], row - data->index);
		row++;
	}
	DrawCircle(data, data->player->x, data->player->y, 5);
	DrawLine(data, data->player->angle * M_PI / 180 ,data->player->x, data->player->y);
	DrawRays(data);
	mlx_put_image_to_window(data->ptr->mlx, data->ptr->win, data->ptr->img, 0, 0);
}

void	draw_2Dmap(t_data *data)
{
	int row;
	
	row = data->index;
	while (data->map[row])
	{
		Draw_walls(data, data->map[row], row - data->index);
		row++;
	}
	row = data->index;
	while (data->map[row])
	{
		DrawPlayer(data, data->map[row], row - data->index);
		row++;
	}
	mlx_put_image_to_window(data->ptr->mlx, data->ptr->win, data->ptr->img, 0, 0);
}

void	execution(t_data *data)
{
	data->ptr = malloc(sizeof(t_cub3d));
	data->ptr->mlx = mlx_init();
	if (!data->ptr->mlx)
		return ;
	init(data);
	data->ptr->win = mlx_new_window(data->ptr->mlx, data->ptr->tile_size * data->long_line, data->ptr->tile_size * data->size, "cub3D");
	data->ptr->img = mlx_new_image(data->ptr->mlx, data->ptr->tile_size * data->long_line, data->ptr->tile_size * data->size);
	data->ptr->addr = mlx_get_data_addr(data->ptr->img , &(data->ptr->bits_per_pixel), &(data->ptr->line_length), &(data->ptr->endian));
	draw_2Dmap(data);
	mlx_hook(data->ptr->win, ON_DESTROY, 1L << 0, ft_close, data);
	mlx_hook(data->ptr->win, KEY_PRESS, 0, key_press, data);
	mlx_hook(data->ptr->win, KEY_RELEASE, 0, key_release, data);
	mlx_loop_hook(data->ptr->mlx, render_next_frame, data);
	mlx_loop(data->ptr->mlx);
}
