/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-brig <nel-brig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 04:23:41 by namine            #+#    #+#             */
/*   Updated: 2023/03/31 04:08:39 by nel-brig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/parsing.h"

void	drawline(t_data *data, double angle, int flag)
{
	t_drawline_data	line;

	(void)flag;
	get_xend_yend(data, &line.x_end, &line.y_end, angle);
}

void	draw_rays(t_data *data)
{
	int	i;

	i = 0;
	data->ray->angle = data->player->angle - ((double)data->fov / 2);
	while (i < data->win_width)
	{
		drawline(data, data->ray->angle * M_PI / 180, 0);
		draw_wall_3d(data, data->ray->distance);
		data->ray->angle += (double)data->fov / (double)data->win_width;
		i++;
	}
	data->walls->x_start = 1;
}
