/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map2D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-brig <nel-brig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 03:50:46 by namine            #+#    #+#             */
/*   Updated: 2023/03/30 06:39:40 by nel-brig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/parsing.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < data->win_width && y >= 0 && y < data->win_height)
	{
		dst = data->ptr->addr + \
			(y * data->ptr->line_length + x * (data->ptr->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

void	render_2d(t_data *data)
{
	int		row;

	mlx_destroy_image(data->ptr->mlx, data->ptr->img);
	mlx_clear_window(data->ptr->mlx, data->ptr->win);
	data->ptr->img = mlx_new_image
		(data->ptr->mlx, data->win_width, data->win_height);
	data->ptr->addr = mlx_get_data_addr
		(data->ptr->img, &(data->ptr->bits_per_pixel),
			&(data->ptr->line_length), &(data->ptr->endian));
	draw_rays(data);
	row = data->index;
	while (data->map[row])
	{
		draw_walls(data, data->map[row], row - data->index);
		row++;
	}
	draw_circle(data, data->player->x, data->player->y, data->player->radius);
	drawline(data, data->player->angle * M_PI / 180,
		data->player->x, data->player->y, 1);
	mlx_put_image_to_window
	(data->ptr->mlx, data->ptr->win, data->ptr->img, 0, 0);
}

void	draw_2dmap(t_data *data)
{
	int	row;

	row = data->index;
	while (data->map[row] && row <= data->end_of_map)
	{
		draw_player(data, data->map[row], row - data->index);
		row++;
	}
	row = data->index;
	while (data->map[row] && row <= data->end_of_map)
	{
		draw_walls(data, data->map[row], row - data->index);
		row++;
	}
	mlx_put_image_to_window
	(data->ptr->mlx, data->ptr->win, data->ptr->img, 0, 0);
}

void	execution(t_data *data)
{
	data->ptr = malloc(sizeof(t_cub3d));
	data->ptr->mlx = mlx_init();
	if (!data->ptr->mlx)
		exit(EXIT_FAILURE);
	init(data);
	data->ptr->tile_size *= data->scale;
	data->ptr->win = mlx_new_window
		(data->ptr->mlx, data->win_width, data->win_height, "cub3d");
	data->ptr->img = mlx_new_image
		(data->ptr->mlx, data->win_width, data->win_height);
	data->ptr->addr = mlx_get_data_addr
		(data->ptr->img, &(data->ptr->bits_per_pixel),
			&(data->ptr->line_length), &(data->ptr->endian));
	draw_2dmap(data);
	mlx_hook(data->ptr->win, ON_DESTROY, 1L << 0, ft_close, data);
	mlx_hook(data->ptr->win, KEY_PRESS, 0, key_press, data);
	mlx_hook(data->ptr->win, KEY_RELEASE, 0, key_release, data);
	mlx_loop_hook(data->ptr->mlx, render_next_frame, data);
	mlx_loop(data->ptr->mlx);
}
