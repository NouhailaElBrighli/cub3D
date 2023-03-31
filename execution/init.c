/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-brig <nel-brig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 03:58:42 by namine            #+#    #+#             */
/*   Updated: 2023/03/30 22:05:16 by nel-brig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/parsing.h"

void	init_player_coordinates(t_data *data, int x, int y)
{
	data->player->x = x;
	data->player->y = y;
	data->player->radius = 5;
	data->player->x_map = x;
	data->player->y_map = y;
}

void	init_move_and_rot(t_data *data)
{
	data->move_up = 0;
	data->move_down = 0;
	data->move_right = 0;
	data->move_left = 0;
	data->rot_left = 0;
	data->rot_right = 0;
}

void	init_player_angle(t_player *player)
{
	if (player->direction->east == 1)
		player->angle = 180.0f;
	if (player->direction->nort == 1)
		player->angle = 270;
	if (player->direction->west == 1)
		player->angle = 0.0f;
	if (player->direction->south == 1)
		player->angle = 90.0f;
}

void	init(t_data *data)
{
	init_move_and_rot(data);
	init_player_angle(data->player);
	data->textures = malloc(sizeof(t_textures));
	if (!data->textures)
		exit(EXIT_FAILURE);
	data->mini_map = malloc(sizeof(t_mini_map));
	if (!data->mini_map)
		exit(EXIT_FAILURE);
	data->textures->img_texture = mlx_xpm_file_to_image(data->ptr->mlx, "textures/IMG-20221123-WA0067-_1_.xpm", &(data->textures->img_width), &(data->textures->img_height));
	if (data->textures->img_texture)
		data->textures->addr = mlx_get_data_addr(data->textures->img_texture, &(data->textures->bits_per_pixel), &(data->textures->line_length), &(data->textures->endian));
	data->ray = malloc(sizeof(t_ray));
	if (!data->ray)
		exit(EXIT_FAILURE);
	data->walls = malloc(sizeof(t_walls));
	if (!data->walls)
		exit(EXIT_FAILURE);
	data->size = data->end_of_map - data->index + 1;
	data->ptr->tile_size = 40;
	data->fov = 60;
	data->player->speed = 10;
	data->win_height = 800;
	data->win_width = 1800;
	data->scale = 1;
	data->dis_3d = (double)data->win_width
		/ (2 * tan((double)data->fov * M_PI / 180));
}

void	init_rays_and_walls(t_data *data)
{
	data->ray->angle = data->player->angle - (data->fov / 2);
	data->walls->x_start = 0;
	data->walls->y_start = 0;
}
