#include "../parsing/parsing.h"

void	draw_line_of_wall(t_data *data, int y_start, int x_start, int y_end)
{
	while (y_start < y_end)
	{
		my_mlx_pixel_put(data, x_start, y_start, 0xFFFFFF);
		y_start++;
	}
}

void	Draw_Wall_3D(t_data *data, double len)
{
	int 	y_end;
	double	exact_len;
	double angle;

	angle = data->rays->angle - data->player->angle;
	exact_len = cos(angle) * len;
	printf("exact len == %f, len == %f\n", exact_len, len);
	if (len == 0)
		data->walls->height = (double)data->win_height;
	else
		data->walls->height = (((double)data->ptr->tile_size * data->dis_3d) / exact_len);
	data->walls->y_start = (data->win_height / 2) - (data->walls->height / 2);
	y_end = data->walls->y_start + data->walls->height;
	draw_line_of_wall(data , data->walls->y_start, data->walls->x_start, y_end);
	data->walls->x_start++;
}

int	DrawLine(t_data *data, double angle ,double x_start, double y_start)
{
	double x_end;
	double y_end;


	// data->rays->len = get_exact_length_of_the_line(data, angle, x_start, y_start);

	// x_end = x_start + (cos(angle) * data->rays->len);
	// y_end = y_start + (sin(angle) * data->rays->len);
	// if(angle == M_PI / 2)
	// 	return(-1);
	y_end = (floor(x_start / data->ptr->tile_size) * data->ptr->tile_size);
	x_end = x_start + ((y_end - y_start) / tan(angle));

    double dy = y_end - y_start;
	double dx = x_end - x_start;

    int step;

    if (fabs(dx) > fabs(dy))
        step = fabs(dx);
    else
        step = fabs(dy);

    double x_incr = dx / step;
    double y_incr = dy / step;

    double x = x_start;
    double y = y_start;

    for (int i = 0; i <= step; i++)
	{
		my_mlx_pixel_put(data, x, y, 0xE24666);//don't round the value
        x += x_incr;
        y += y_incr;
    }
	return (data->rays->len);
}

void	DrawCircle(t_data *data, double x, double y, double r)
{
    int i, angle, x1, y1;

	while (r != 0)
	{    	
		for(i = 0; i < 360; i += 1)
    	{
			angle = i;
			x1 = (int)(r * cos(angle * M_PI / 180));
			y1 = (int)(r * sin(angle * M_PI / 180));
			my_mlx_pixel_put(data, x + x1, y + y1, 0xE24666);
    	}
		r -= 0.5;
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
			for (int x = 0; x < data->ptr->tile_size; x++)
			{
				for (int y = 0; y < data->ptr->tile_size; y++)	
					my_mlx_pixel_put(data, x + (i * data->ptr->tile_size), y + (nbr_row * data->ptr->tile_size), 0xFFFFFF);
			}
		}
		i++;
	}
}

void	DrawRays(t_data *data)
{
	int i;


	i = 0;
	data->rays->angle = data->player->angle - (data->FOV  / 2);
	while (i < data->rays->num_rays)
	{
		DrawLine(data, data->rays->angle, data->player->x, data->player->y);
		// Draw_Wall_3D(data, data->rays->len);
		data->rays->angle += data->FOV/ data->rays->num_rays; // typecast obligator
		// fprintf(stderr, "ray angle == %f\n", data->rays->angle);
		i++;
	}
	// Draw_Walls_3d(data);
	data->walls->x_start = 1;
}

void	scale(t_data *data)
{
	data->player->radius *= data->scale;
	data->player->speed *= data->scale;
}


// void	DDA(t_data *data, double angle, double x_start, double y_start)
// {
// 	double	A_x = 0;
// 	double	A_y = 0;
// 	// (void)angle;
// 	// (void)y_start;
// 	// (void)angle;
// 	A_y = (floor(x_start / data->ptr->tile_size) * data->ptr->tile_size);
// 	A_x = x_start + ((A_y - y_start) / tan(angle));
// 	// fprintf(stderr, "y_start == %f, A_y == %f\n", x_start ,A_y);
// 	// fprintf(stderr, "x == %f\ny == %f\n", A_x, A_y);
// 	// my_mlx_pixel_put(data, A_x, A_y, 0xE24666);
// 	double dy = A_y - y_start;
// 	double dx = A_x - x_start;
//     int step;
//     if (fabs(dx) > fabs(dy))
//         step = fabs(dx);
//     else
//         step = fabs(dy);
//     double x_incr = dx / step;
//     double y_incr = dy / step;
//     double x = x_start;
//     double y = y_start;
//     for (int i = 0; i <= step; i++)
// 	{
// 		my_mlx_pixel_put(data, x, y, 0xE24666);//don't round the value
//         x += x_incr;
//         y += y_incr;
//     }
// 	// // A_y = 
// }

void	DrawPlayer(t_data *data, char *row, int nbr_row)
{
	int i;

	i = 0;
	init_rays_and_walls(data);
	while (row[i] != '\0')
	{
		if (is_player(row[i], data->player, 1) == 1)
		{
			init_player_coordinates(data, (data->ptr->tile_size / 2) + (i * data->ptr->tile_size), (data->ptr->tile_size / 2) + (nbr_row * data->ptr->tile_size));
			scale(data);
			DrawCircle(data, data->player->x, data->player->y, data->player->radius);
			DrawLine(data, data->player->angle ,data->player->x, data->player->y);
			// DDA(data, data->player->angle, data->player->x, data->player->y);
			DrawRays(data);
			break;
		}
		i++;
	}
}

