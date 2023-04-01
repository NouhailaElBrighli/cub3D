/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-brig <nel-brig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 05:52:19 by namine            #+#    #+#             */
/*   Updated: 2023/04/01 03:16:45 by nel-brig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/parsing.h"

double	find_distance(double x1, double y1, double x2, double y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

void	set_ray_direction(t_data *data, double ray_angle)
{
	data->ray->ray_down = ((ray_angle > 0) && (ray_angle < M_PI));
	data->ray->ray_up = !data->ray->ray_down;
	data->ray->ray_right = ((ray_angle < 90 * (M_PI / 180)) || \
							(ray_angle > (270 * (M_PI / 180))));
	data->ray->ray_left = !data->ray->ray_right;
}

void	set_data_for_vertical(t_data *data, double *x_end,
	double *y_end, double vertical_distance)
{
	data->ray->flag = 'v';
	data->ray->x = *x_end;
	data->ray->y = *y_end;
	data->ray->distance = vertical_distance;
}

void	set_data_for_horizontal(t_data *data, double *x_end,
	double *y_end, double horizontal_distance)
{
	data->ray->flag = 'h';
	data->ray->x = *x_end;
	data->ray->y = *y_end;
	data->ray->distance = horizontal_distance;
}

void	get_xend_yend(t_data *data, double *x_end, double *y_end,
		double ray_angle)
{
	double	horizontal_distance;
	double	vertical_distance;
	t_point	v_p;
	t_point	h_p;

	horizontal_distance = 0;
	vertical_distance = 0;
	horizontal_intersection(data, ray_angle, &h_p);
	vertical_intersection(data, ray_angle, &v_p);
	horizontal_distance = find_distance(data->player->x, data->player->y,
			h_p.x, h_p.y);
	vertical_distance = find_distance(data->player->x, data->player->y,
			v_p.x, v_p.y);
	if (vertical_distance < horizontal_distance)
	{
		*x_end = v_p.x;
		*y_end = v_p.y;
		set_data_for_vertical(data, x_end, y_end, vertical_distance);
	}
	else
	{
		*x_end = h_p.x;
		*y_end = h_p.y;
		set_data_for_horizontal(data, x_end, y_end, horizontal_distance);
	}
}
