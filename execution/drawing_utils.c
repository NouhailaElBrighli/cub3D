/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namine <namine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 00:35:09 by nel-brig          #+#    #+#             */
/*   Updated: 2023/04/02 00:10:37 by namine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/parsing.h"

void	choose_texture(t_data *data, t_textures **tmp)
{
	if (data->ray->flag == 'h')
	{
		if (data->player->y > data->ray->y)
			*tmp = data->north_textures;
		else
			*tmp = data->south_textures;
	}
	else
	{
		if (data->player->x > data->ray->x)
			*tmp = data->east_textures;
		else
			*tmp = data->west_textures;
	}
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	my_mlx_pixel_get_color(t_textures *textures, int x, int y)
{
	char	*dst;

	dst = NULL;
	if (x >= 0 && x < 65 && y >= 0 && y < 65)
	{
		dst = textures->addr + \
			(y * textures->line_length + x * (textures->bits_per_pixel / 8));
	}
	return (*(unsigned int *)dst);
}
