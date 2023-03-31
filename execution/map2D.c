/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map2D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namine <namine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 03:50:46 by namine            #+#    #+#             */
/*   Updated: 2023/03/31 05:54:00 by namine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/parsing.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < data->win_width && y >= 0 && y < data->win_height)
	{
		dst = data->ptr->addr +
			(y * data->ptr->line_length + x * (data->ptr->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

void	render_2d(t_data *data)
{
	int	row;

	mlx_destroy_image(data->ptr->mlx, data->ptr->img);
	mlx_clear_window(data->ptr->mlx, data->ptr->win);
	data->ptr->img = mlx_new_image(data->ptr->mlx, data->win_width,
			data->win_height);
	data->ptr->addr = mlx_get_data_addr(data->ptr->img,
			&(data->ptr->bits_per_pixel), &(data->ptr->line_length),
			&(data->ptr->endian));
	draw_rays(data);
	row = data->index;
	mlx_put_image_to_window(data->ptr->mlx, data->ptr->win, data->ptr->img, 0,
			0);
}

void	get_player_coordinates(t_data *data)
{
	int	row;
	int	j;

	row = data->index;
	while (data->map[row] && row <= data->end_of_map)
	{
		j = 0;
		while (data->map[row][j])
		{
			if (is_player(data->map[row][j], data->player, 1))
			{
				init_player_coordinates(data, (data->ptr->tile_size / 2) + (j
							* data->ptr->tile_size), (data->ptr->tile_size / 2)
						+ ((row - data->index) * data->ptr->tile_size));
				break ;
			}
			j++;
		}
		row++;
	}
}

void	execution(t_data *data)
{
	data->ptr = malloc(sizeof(t_cub3d));
	data->ptr->mlx = mlx_init();
	if (!data->ptr->mlx)
		exit(EXIT_FAILURE);
	init(data);
	data->ptr->tile_size *= data->scale;
	data->ptr->win = mlx_new_window(data->ptr->mlx, data->win_width,
			data->win_height, "cub3d");
	data->ptr->img = mlx_new_image(data->ptr->mlx, data->win_width,
			data->win_height);
	data->ptr->addr = mlx_get_data_addr(data->ptr->img,
			&(data->ptr->bits_per_pixel), &(data->ptr->line_length),
			&(data->ptr->endian));
	init_rays_and_walls(data);
	get_player_coordinates(data);
	draw_rays(data);
	mlx_put_image_to_window(data->ptr->mlx, data->ptr->win, data->ptr->img, 0,
			0);
	mlx_hook(data->ptr->win, ON_DESTROY, 1L << 0, ft_close, data);
	mlx_hook(data->ptr->win, KEY_PRESS, 0, key_press, data);
	mlx_hook(data->ptr->win, KEY_RELEASE, 0, key_release, data);
	mlx_loop_hook(data->ptr->mlx, render_next_frame, data);
	mlx_loop(data->ptr->mlx);
}
