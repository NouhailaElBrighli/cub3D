#include "../parsing/parsing.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->ptr->addr + (y * data->ptr->line_length + x * (data->ptr->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void DrawCircle(t_data *data, int x, int y, float r)
{
    int i, angle, x1, y1;

	while (r != 0)
	{    	
		for(i = 0; i < 360; i += 1)
    	{
			angle = i;
			x1 = r * cos(angle * M_PI / 180);
			y1 = r * sin(angle * M_PI / 180);
			my_mlx_pixel_put(data, x + x1, y + y1, 0xE24666);
    	}
		r -= 0.5;
	}
}

void DrawLine(t_data *data, int x_start, int y_start)
{
	float angle = data->player->angle * M_PI / 180;
	int x_end = x_start + roundf((cos(angle) * 100.0f));// modify
	int y_end = y_start + roundf((sin(angle) * 100.0f));// modify

	
    int dy = y_end - y_start;
	int dx = x_end - x_start;

    int step;

    if (abs(dx) > abs(dy))
        step = abs(dx);
    else
        step = abs(dy);
 
    float x_incr = (float)dx / step;
    float y_incr = (float)dy / step;

    float x = (float)x_start;
    float y = (float)y_start;

    for (int i = 0; i < step; i++) {
		my_mlx_pixel_put(data, roundf(x), roundf(y), 0xE24666);
        x += x_incr;
        y += y_incr;
    }
}

void	Draw_walls(t_data *data, char *row, int nbr_row)
{
	int i;

	i = 0;
	while (row[i] != '\0')
	{
		if (row[i] == '1')
		{
			for (int x = 0; x < data->ptr->img_dim; x++)
			{
				for (int y = 0; y < data->ptr->img_dim; y++)
					my_mlx_pixel_put(data, x + (i * data->ptr->img_dim), y + (nbr_row * data->ptr->img_dim), 0xFFFFFF);
			}
		}
		i++;
	}
}

int get_height(t_data *data)
{
	int count = data->index;

	while (data->map[count])
		count++;
	count -= data->index;
	return(count);
}

void	render_2D(t_data *data)
{
	int row;

	mlx_clear_window(data->ptr->mlx, data->ptr->win);
	data->ptr->img = mlx_new_image(data->ptr->mlx, data->ptr->img_dim * data->long_line, data->ptr->img_dim * data->size);
	data->ptr->addr = mlx_get_data_addr(data->ptr->img , &(data->ptr->bits_per_pixel), &(data->ptr->line_length), &(data->ptr->endian));
	row = data->index;
	while (data->map[row])
	{
		Draw_walls(data, data->map[row], row - data->index);
		row++;
	}
	DrawCircle(data, data->player->x, data->player->y, 5.0f);
	DrawLine(data, data->player->x, data->player->y);
	mlx_put_image_to_window(data->ptr->mlx, data->ptr->win, data->ptr->img, 0, 0);
}

int	key_press(int keycode, t_data *data)
{
	if (keycode == 53)
	{
		mlx_destroy_window(data->ptr->mlx, data->ptr->win);
		exit(0);
	}
	else if (keycode == 13)
		data->move_up = 1;
	else if (keycode == 1)
		data->move_down = 1;
	else if (keycode == 0)
		data->move_right = 1;
	else if (keycode == 2)
		data->move_left = 1;
	else if (keycode == 124)
		data->rot_left = 1;
	else if (keycode == 123)
		data->rot_right = 1;
	return (0);
}

int key_release(int keycode, t_data *data)
{
	if (keycode == 13)
		data->move_up = 0;
	else if (keycode == 1)
		data->move_down = 0;
	else if (keycode == 0)
		data->move_right = 0;
	else if (keycode == 2)
		data->move_left = 0;
	else if (keycode == 124)
		data->rot_left = 0;
	else if (keycode == 123)
		data->rot_right = 0;
	return(0);
}

int	ft_close(t_data *data)
{
	mlx_destroy_window(data->ptr->mlx, data->ptr->win);
	exit(0);
}

void	DrawPlayer(t_data *data, char *row, int nbr_row)
{
	int i = 0;
	while (row[i] != '\0')
	{
		if (is_player(row[i], data->player, 1) == 1)
		{
			init_player_coordinates(data, (data->ptr->img_dim / 2) + (i * data->ptr->img_dim), (data->ptr->img_dim / 2) + (nbr_row * data->ptr->img_dim));
			DrawCircle(data, data->player->x, data->player->y, 5.0f);
			DrawLine(data, data->player->x, data->player->y);
		}
		i++;
	}
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

int	render_next_frame(t_data *data)
{
	if (data->move_up == 1 && data->move_down == 1)
		return (0);
	if (data->move_right == 1 && data->move_left == 1)
		return(0);
	if (data->rot_left == 1 && data->rot_right == 1)
		return (0);
	if (data->rot_right == 1)
		data->player->angle -= 3;
	else if (data->rot_left == 1)
		data->player->angle += 3;
	if (data->move_up == 1)
	{
		data->player->x = data->player->x + roundf((cos(data->player->angle * M_PI / 180) * 2.0f));
		data->player->y = data->player->y + roundf((sin(data->player->angle * M_PI / 180) * 2.0f));
	}
	else if (data->move_down == 1)
	{
		data->player->x = data->player->x + roundf((cos((data->player->angle + 180) * M_PI / 180) * 2.0f));
		data->player->y = data->player->y + roundf((sin((data->player->angle + 180) * M_PI / 180) * 2.0f));
	}
	if (data->move_left == 1)
	{
		data->player->x = data->player->x + roundf((cos((data->player->angle + 90) * M_PI / 180) * 2.0f));
		data->player->y = data->player->y + roundf((sin((data->player->angle + 90) * M_PI / 180) * 2.0f));
	}
	else if (data->move_right == 1)
	{
		data->player->x = data->player->x + roundf((cos((data->player->angle - 90) * M_PI / 180) * 2.0f));
		data->player->y = data->player->y + roundf((sin((data->player->angle - 90) * M_PI / 180) * 2.0f));
	}
	render_2D(data);
	return(0);
}

void	execution(t_data *data)
{
	data->ptr = malloc(sizeof(t_cub3d));
	data->ptr->mlx = mlx_init();
	if (!data->ptr->mlx)
		return ;
	init_move_and_rot(data);
	init_player_angle(data->player);
	data->ptr->img_dim = 50;
	data->size = get_height(data);
	data->ptr->win = mlx_new_window(data->ptr->mlx, data->ptr->img_dim * data->long_line, data->ptr->img_dim * data->size, "cub3D");
	data->ptr->img = mlx_new_image(data->ptr->mlx, data->ptr->img_dim * data->long_line, data->ptr->img_dim * data->size);
	data->ptr->addr = mlx_get_data_addr(data->ptr->img , &(data->ptr->bits_per_pixel), &(data->ptr->line_length), &(data->ptr->endian));
	draw_2Dmap(data);
	mlx_hook(data->ptr->win, ON_DESTROY, 1L << 0, ft_close, data);
	mlx_hook(data->ptr->win, KEY_PRESS, 0, key_press, data);
	mlx_hook(data->ptr->win, KEY_RELEASE, 0, key_release, data);
	mlx_loop_hook(data->ptr->mlx, render_next_frame, data);
	mlx_loop(data->ptr->mlx);
}
