/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namine <namine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 03:12:00 by namine            #+#    #+#             */
/*   Updated: 2023/03/31 06:06:00 by namine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/parsing.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	my_mlx_pixel_get_color(t_textures *textures, int x, int y)
{
	char	*dst;

	dst = NULL;
	if (x >= 0 && x < 40 && y >= 0 && y < 40)
	{
		dst = textures->addr +
			(y * textures->line_length + x * (textures->bits_per_pixel / 8));
	}
	return (*(unsigned int *)dst);
}

void	draw_line_of_wall(t_data *data, int y_start, int x_start, int y_end)
{
	int	offset_x;
	int	offset_y;
	t_textures *tmp;

	offset_y = 0;
	if (data->ray->flag == 'v')
	{
		offset_x = (int)data->ray->y % data->ptr->tile_size;
	}
	else
	{
		offset_x = (int)data->ray->x % data->ptr->tile_size;
	}
	while (y_start < y_end)
	{
		if (data->ray->flag == 'h')
		{
			if (data->player->y > data->ray->y)
				tmp = data->north_textures;
			else
				tmp = data->south_textures;
		}
		else
		{
			if (data->player->x > data->ray->x)
				tmp = data->east_textures;
			else
				tmp = data->west_textures;
		}
		my_mlx_pixel_put(data, x_start, y_start,
						my_mlx_pixel_get_color(tmp, offset_x,
							offset_y * (data->ptr->tile_size
								/ data->walls->height)));
		offset_y++;
		y_start++;
	}
}

void	draw_line_ceiling(t_data *data, int y_start, int x_start)
{
	int	ceil;

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
	int	floor;

	floor = create_trgb(0, data->floor[0], data->floor[1], data->floor[2]);
	while (y_start <= data->win_height)
	{
		my_mlx_pixel_put(data, x_start, y_start, floor);
		y_start++;
	}
}

void	draw_wall_3d(t_data *data, double len)
{
	double	exact_len;
	int		y_end;
	double	angle;

	angle = (data->ray->angle - data->player->angle) * M_PI / 180;
	exact_len = cos(angle) * len;
	data->walls->height =
		(((double)data->ptr->tile_size * data->dis_3d) / exact_len);
	data->walls->y_start = (data->win_height / 2) - (data->walls->height / 2);
	y_end = data->walls->y_start + data->walls->height;
	draw_line_of_wall(data, data->walls->y_start, data->walls->x_start, y_end);
	draw_line_ceiling(data, data->walls->y_start, data->walls->x_start);
	draw_line_floor(data, y_end, data->walls->x_start);
	data->walls->x_start++;
}
