/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-brig <nel-brig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 03:12:00 by namine            #+#    #+#             */
/*   Updated: 2023/04/01 04:12:22 by nel-brig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/parsing.h"

void	draw_line_of_wall(t_data *data, int y_start, int x_start, int y_end)
{
	int			offset_x;
	int			offset_y;
	t_textures	*tmp;

	offset_y = 0;
	tmp = NULL;
	if (data->ray->flag == 'v')
		offset_x = (int)data->ray->y % data->ptr->tile_size;
	else
		offset_x = (int)data->ray->x % data->ptr->tile_size;
	while (y_start < y_end)
	{
		choose_texture(data, &tmp);
		my_mlx_pixel_put(data, x_start, y_start,
			my_mlx_pixel_get_color(tmp, offset_x,
				offset_y * (data->ptr->tile_size / data->walls->height)));
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
	data->walls->height = \
		(((double)data->ptr->tile_size * data->dis_3d) / exact_len);
	data->walls->y_start = (data->win_height / 2) - (data->walls->height / 2);
	y_end = data->walls->y_start + data->walls->height;
	draw_line_of_wall(data, data->walls->y_start, data->walls->x_start, y_end);
	draw_line_ceiling(data, data->walls->y_start, data->walls->x_start);
	draw_line_floor(data, y_end, data->walls->x_start);
	data->walls->x_start++;
}
