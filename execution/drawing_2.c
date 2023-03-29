/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namine <namine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 04:23:41 by namine            #+#    #+#             */
/*   Updated: 2023/03/29 06:21:12 by namine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/parsing.h"

void	drawline(t_data *data, double angle, double x_start, double y_start, int flag)
{
	t_drawline_data	line;
	int				i;

	line.x_end = 0;
	line.y_end = 0;
	get_xend_yend(data, &line.x_end, &line.y_end, angle);
	line.dy = line.y_end - y_start;
	line.dx = line.x_end - x_start;
	if (fabs(line.dx) > fabs(line.dy))
		line.step = fabs(line.dx);
	else
		line.step = fabs(line.dy);
	line.x_incr = line.dx / line.step;
	line.y_incr = line.dy / line.step;
	line.x = x_start;
	line.y = y_start;
	i = 0;
	while (i <= line.step)
	{
		if (flag == 1)
			my_mlx_pixel_put(data, round(line.x), round(line.y), 0xE24666);
		line.x += line.x_incr;
		line.y += line.y_incr;
		i++;
	}
}

void	draw_circle(t_data *data, double x, double y, double r)
{
	int	angle;
	int	x1;
	int	y1;
	int	i;

	while (r != 0)
	{
		i = 0;
		while (i < 360)
		{
			angle = i;
			x1 = (int)(r * cos(angle * M_PI / 180));
			y1 = (int)(r * sin(angle * M_PI / 180));
			my_mlx_pixel_put(data, x + x1, y + y1, 0xE24666);
			i++;
		}
		r -= 0.5;
	}
}

void	draw_walls(t_data *data, char *row, int nbr_row)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	while (row[i] != '\0')
	{
		if (row[i] == '1')
		{
			x = 0;
			while (x < data->ptr->tile_size)
			{
				y = 0;
				while (y < data->ptr->tile_size)
				{
					my_mlx_pixel_put(data, x + (i * data->ptr->tile_size),
						y + (nbr_row * data->ptr->tile_size), 0x000000);
					y++;
				}
				x++;
			}
		}
		i++;
	}
}

void	draw_rays(t_data *data)
{
	int	i;

	i = 0;
	data->ray->angle = data->player->angle - ((double)data->FOV / 2);
	while (i < (double)data->win_width)
	{
		drawline(data, data->ray->angle * M_PI / \
		180, data->player->x, data->player->y, 0);
		draw_wall_3d(data, data->ray->distance);
		data->ray->angle += (double)data->FOV / \
		(double)data->win_width;
		i++;
	}
	data->walls->x_start = 1;
}

void	draw_player(t_data *data, char *row, int nbr_row)
{
	int	i;

	i = 0;
	init_rays_and_walls(data);
	while (row[i] != '\0')
	{
		if (is_player(row[i], data->player, 1) == 1)
		{
			init_player_coordinates
			(data, (data->ptr->tile_size / 2) + (i * data->ptr->tile_size),
			(data->ptr->tile_size / 2) + (nbr_row * data->ptr->tile_size));
			scale(data);
			draw_circle
			(data, data->player->x, data->player->y, data->player->radius);
			drawline
			(data, data->player->angle * M_PI / 180,
			data->player->x, data->player->y, 0);
			draw_rays(data);
			break ;
		}
		i++;
	}
}
