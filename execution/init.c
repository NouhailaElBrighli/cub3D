/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namine <namine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 03:58:42 by namine            #+#    #+#             */
/*   Updated: 2023/03/31 06:13:31 by namine           ###   ########.fr       */
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
	data->north_textures = malloc(sizeof(t_textures));
	if (!data->north_textures)
		exit(EXIT_FAILURE);
	data->south_textures = malloc(sizeof(t_textures));
	if (!data->south_textures)
		exit(EXIT_FAILURE);
	fprintf(stderr, "WAAAAAAA\n");
	data->east_textures = malloc(sizeof(t_textures));
	if (!data->east_textures)
		exit(EXIT_FAILURE);
	data->west_textures = malloc(sizeof(t_textures));
	if (!data->west_textures)
		exit(EXIT_FAILURE);
	data->north_textures->img = mlx_xpm_file_to_image(data->ptr->mlx,
	"textures/1.xpm",
	&(data->north_textures->img_width),
	&(data->north_textures->img_height));
	if (!data->north_textures->img)
		exit(EXIT_FAILURE);
	data->north_textures->addr = mlx_get_data_addr(data->north_textures->img,
													&(data->north_textures->bits_per_pixel),
													&(data->north_textures->line_length),
													&(data->north_textures->endian));
	if (!data->north_textures->addr)
		exit(EXIT_FAILURE);
	data->south_textures->img = mlx_xpm_file_to_image(data->ptr->mlx,
														"textures/2.xpm",
														&(data->south_textures->img_width),
														&(data->south_textures->img_height));
	if (!data->south_textures->img)
		exit(EXIT_FAILURE);
	data->south_textures->addr = mlx_get_data_addr(data->south_textures->img,
													&(data->south_textures->bits_per_pixel),
													&(data->south_textures->line_length),
													&(data->south_textures->endian));
	if (!data->south_textures->addr)
		exit(EXIT_FAILURE);
	data->east_textures->img = mlx_xpm_file_to_image(data->ptr->mlx,
														"textures/3.xpm",
														&(data->east_textures->img_width),
														&(data->east_textures->img_height));
	if (!data->east_textures->img)
		exit(EXIT_FAILURE);
	data->east_textures->addr = mlx_get_data_addr(data->east_textures->img,
													&(data->east_textures->bits_per_pixel),
													&(data->east_textures->line_length),
													&(data->east_textures->endian));
	if (!data->east_textures->addr)
		exit(EXIT_FAILURE);
	data->west_textures->img = mlx_xpm_file_to_image(data->ptr->mlx,
														"textures/4.xpm",
														&(data->west_textures->img_width),
														&(data->west_textures->img_height));
	if (!data->west_textures->img)
		exit(EXIT_FAILURE);
	data->west_textures->addr = mlx_get_data_addr(data->west_textures->img,
													&(data->west_textures->bits_per_pixel),
													&(data->west_textures->line_length),
													&(data->west_textures->endian));
	if (!data->west_textures->addr)
		exit(EXIT_FAILURE);
	data->ray = malloc(sizeof(t_ray));
	if (!data->ray)
		exit(EXIT_FAILURE);
	data->walls = malloc(sizeof(t_walls));
	if (!data->walls)
		exit(EXIT_FAILURE);
	data->size = data->end_of_map - data->index + 1;
	data->ptr->tile_size = 65;
	data->fov = 60;
	data->player->speed = 1;
	data->win_height = 600;
	data->win_width = 1200;
	data->scale = 0.4;
	data->dis_3d = (double)data->win_width / (2 * tan((double)data->fov * M_PI
				/ 180));
}

void	init_rays_and_walls(t_data *data)
{
	data->ray->angle = data->player->angle - (data->fov / 2);
	data->walls->x_start = 0;
	data->walls->y_start = 0;
}
