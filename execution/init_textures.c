/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-brig <nel-brig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 01:08:39 by nel-brig          #+#    #+#             */
/*   Updated: 2023/04/01 01:17:13 by nel-brig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/parsing.h"

void	init_textures_images(t_data *data)
{
	data->north_textures->img = mlx_xpm_file_to_image(data->ptr->mlx,
			data->path[0], &(data->north_textures->img_width),
			&(data->north_textures->img_height));
	if (!data->north_textures->img)
		exit(EXIT_FAILURE);
	data->south_textures->img = mlx_xpm_file_to_image(data->ptr->mlx,
			data->path[1], &(data->south_textures->img_width),
			&(data->south_textures->img_height));
	if (!data->south_textures->img)
		exit(EXIT_FAILURE);
	data->east_textures->img = mlx_xpm_file_to_image(data->ptr->mlx,
			data->path[3], &(data->east_textures->img_width),
			&(data->east_textures->img_height));
	if (!data->east_textures->img)
		exit(EXIT_FAILURE);
	data->west_textures->img = mlx_xpm_file_to_image(data->ptr->mlx,
			data->path[2], &(data->west_textures->img_width),
			&(data->west_textures->img_height));
	if (!data->west_textures->img)
		exit(EXIT_FAILURE);
}

void	init_images_info(t_data *data)
{
	data->north_textures->addr = mlx_get_data_addr(data->north_textures->img,
			&(data->north_textures->bits_per_pixel),
			&(data->north_textures->line_length),
			&(data->north_textures->endian));
	if (!data->north_textures->addr)
		exit(EXIT_FAILURE);
	data->south_textures->addr = mlx_get_data_addr(data->south_textures->img,
			&(data->south_textures->bits_per_pixel),
			&(data->south_textures->line_length),
			&(data->south_textures->endian));
	if (!data->south_textures->addr)
		exit(EXIT_FAILURE);
	data->east_textures->addr = mlx_get_data_addr(data->east_textures->img,
			&(data->east_textures->bits_per_pixel),
			&(data->east_textures->line_length),
			&(data->east_textures->endian));
	if (!data->east_textures->addr)
		exit(EXIT_FAILURE);
	data->west_textures->addr = mlx_get_data_addr(data->west_textures->img,
			&(data->west_textures->bits_per_pixel),
			&(data->west_textures->line_length),
			&(data->west_textures->endian));
	if (!data->west_textures->addr)
		exit(EXIT_FAILURE);
}

void	init_textures(t_data *data)
{
	data->north_textures = malloc(sizeof(t_textures));
	if (!data->north_textures)
		exit(EXIT_FAILURE);
	data->south_textures = malloc(sizeof(t_textures));
	if (!data->south_textures)
		exit(EXIT_FAILURE);
	data->east_textures = malloc(sizeof(t_textures));
	if (!data->east_textures)
		exit(EXIT_FAILURE);
	data->west_textures = malloc(sizeof(t_textures));
	if (!data->west_textures)
		exit(EXIT_FAILURE);
	init_textures_images(data);
	init_images_info(data);
}
