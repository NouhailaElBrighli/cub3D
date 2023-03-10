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
	int x_end = x_start + roundf((cos(angle) * 50.0f));// modify
	int y_end = y_start + roundf((sin(angle) * 50.0f));// modify

    int dy = y_end - y_start;
	int dx = x_end - x_start;

    int step;

    if (abs(dx) > abs(dy))
        step = abs(dx);
    else
        step = abs(dy);
 
    float x_incr = (float)dx / step;
    float y_incr = (float)dy / step;

    // Take the initial points as x and y
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
			for (int x = 0; x < 50; x++)
			{
				for (int y = 0; y < 50; y++)
					my_mlx_pixel_put(data, x + (i * 50), y + (nbr_row * 50), 0xFFFFFF);
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
	return(count);
}

void	render_map(t_data *data,int dir)
{
	int row;

	if (dir == UP)
		data->player->y -= 10;
	else if (dir == DOWN)
		data->player->y += 10;
	else if (dir == LEFT)
		data->player->x -= 10;
	else if (dir == RIGHT)
		data->player->x += 10;
	else if (dir == ROT_LEFT)
		data->player->angle += 30;
	else if (dir == ROT_RIGHT)
		data->player->angle -= 30;
 	mlx_clear_window(data->ptr->mlx, data->ptr->win);
	data->ptr->img = mlx_new_image(data->ptr->mlx, 50 * data->long_line, 50 * data->size);
	data->ptr->addr = mlx_get_data_addr(data->ptr->img , &(data->ptr->bits_per_pixel), &(data->ptr->line_length), &(data->ptr->endian));
	row = data->index;
	while (data->map[row])
	{
		Draw_walls(data, data->map[row], row - data->index);
		row++;
	}
	DrawCircle(data, data->player->x, data->player->y, 3.0f);
	DrawLine(data, data->player->x, data->player->y);
	mlx_put_image_to_window(data->ptr->mlx, data->ptr->win, data->ptr->img, 0, 0);
}

int	key_hook(int keycode, t_data *data)
{
	if (keycode == 53)
	{
		mlx_destroy_window(data->ptr->mlx, data->ptr->win);
		exit(0);
	}
	else if (keycode == 13)
		render_map(data, UP);
	else if (keycode == 1)
		render_map(data, DOWN);
	else if (keycode == 0)
		render_map(data, LEFT);
	else if (keycode == 2)
		render_map(data, RIGHT);
	else if (keycode == 124)
		render_map(data, ROT_LEFT);
	else if (keycode == 123)
		render_map(data, ROT_RIGHT);
	// else
	// 	fprintf(stderr, "keycode == %d\n", keycode);
	return (0);
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
			init_player_coordinates(data, 25 + (i * data->ptr->img_dim), 25 + (nbr_row * data->ptr->img_dim));
			DrawCircle(data, data->player->x, data->player->y, 3.0f);
			DrawLine(data, data->player->x, data->player->y);
		}
		i++;
	}
}

void	push_image(t_data *data)
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
	data->ptr->img_dim = 50; // 32
	data->size = get_height(data);
	data->ptr->win = mlx_new_window(data->ptr->mlx, 50 * data->long_line, 50 * data->size, "cub3D");
	data->ptr->img = mlx_new_image(data->ptr->mlx, 50 * data->long_line, 50 * data->size);
	data->ptr->addr = mlx_get_data_addr(data->ptr->img , &(data->ptr->bits_per_pixel), &(data->ptr->line_length), &(data->ptr->endian));
	init_player_angle(data->player);
	push_image(data);
	mlx_hook(data->ptr->win, ON_DESTROY, 1L << 0, ft_close, data);
	mlx_hook(data->ptr->win, ON_KEYDOWN, 0, key_hook, data);
	mlx_loop(data->ptr->mlx);
}
