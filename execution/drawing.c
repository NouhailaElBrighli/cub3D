/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-brig <nel-brig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 03:12:00 by namine            #+#    #+#             */
/*   Updated: 2023/03/29 04:00:57 by nel-brig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/parsing.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	draw_line_of_wall(t_data *data, int y_start, int x_start, int y_end)
{
	while (y_start < y_end)
	{
		my_mlx_pixel_put(data, x_start, y_start, 0xFFFFFF);
		y_start++;
	}
}

void	draw_line_ceiling(t_data *data, int y_start, int x_start)
{
	int ceil;

	ceil = create_trgb(0, data->ceiling[0], data->ceiling[1], data->ceiling[2]);
	y_start--;
	while (y_start >= 0)
	{
		my_mlx_pixel_put(data, x_start, y_start, ceil);
		y_start--;
	}
}

void	draw_line_floor(t_data *data, int y_start, int x_start)
{
	int floor;

	floor = create_trgb(0, data->floor[0], data->floor[1], data->floor[2]);
	// y_start++;
	while (y_start <= data->win_height)
	{
		my_mlx_pixel_put(data, x_start, y_start, floor);
		y_start++;
	}
}

void	draw_wall_3d(t_data *data, double len)
{
	int 	y_end;
	double	exact_len;
	double angle;

	angle = (data->ray->angle - data->player->angle) * M_PI / 180;
	exact_len = cos(angle) * len;
	// if (exact_len == 0)
	// 	data->walls->height = (double)data->win_height;
	// else
		data->walls->height = (((double)data->ptr->tile_size * data->dis_3d) / exact_len);
	data->walls->y_start = (data->win_height / 2) - (data->walls->height / 2);
	y_end = data->walls->y_start + data->walls->height;
	draw_line_of_wall(data , data->walls->y_start, data->walls->x_start, y_end);
	draw_line_ceiling(data, data->walls->y_start, data->walls->x_start);
	draw_line_floor(data, y_end, data->walls->x_start);
	data->walls->x_start++;
}

void	drawline(t_data *data, double angle, double x_start, double y_start, int flag)
{
	double	x_end;
	double	y_end;
	double	dy;
	double	dx;
	double	x_incr;
	double	y_incr;
	double	x;
	double	y;
    int		step;

	x_end = 0;
	y_end = 0;
	get_xend_yend(data, &x_end, &y_end, angle);
    dy = y_end - y_start;
	dx = x_end - x_start;
    if (fabs(dx) > fabs(dy))
        step = fabs(dx);
    else
        step = fabs(dy);
    x_incr = dx / step;
    y_incr = dy / step;
    x = x_start;
    y = y_start;
    for (int i = 0; i <= step; i++)
	{
		if (flag == 1)
			my_mlx_pixel_put(data, round(x), round(y), 0xE24666);
        x += x_incr;
        y += y_incr;
    }
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

void	draw_walls(t_data *data, char *row, int nbr_row)
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
					my_mlx_pixel_put(data, x + (i * data->ptr->tile_size), y + (nbr_row * data->ptr->tile_size), 0x000000);
			}
		}
		i++;
	}
}

void	DrawRays(t_data *data)
{
	int i;

	i = 0;
	data->ray->angle = data->player->angle - ((double)data->FOV / 2);
	while (i < (double)data->win_width)
	{
		drawline(data, data->ray->angle * M_PI / 180, data->player->x, data->player->y, 0);
		draw_wall_3d(data, data->ray->distance); // uncomment this
		data->ray->angle += (double)data->FOV / (double)data->win_width; //typecast obligator
		i++;
	}
	data->walls->x_start = 1;
}

void	scale(t_data *data)
{
	data->player->radius *= data->scale;
	data->player->speed *= data->scale;
}

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
			drawline(data, data->player->angle * M_PI / 180 ,data->player->x, data->player->y, 0);
			DrawRays(data);
			break;
		}
		i++;
	}
}
