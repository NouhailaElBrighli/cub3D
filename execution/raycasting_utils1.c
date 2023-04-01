/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-brig <nel-brig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 03:12:01 by nel-brig          #+#    #+#             */
/*   Updated: 2023/04/01 21:16:45 by nel-brig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/parsing.h"

t_point	find_step(t_point step, t_data *data, double ray_angle)
{
	step.y = data->ptr->tile_size;
	if (data->ray->ray_up)
		step.y = step.y * -1;
	step.x = data->ptr->tile_size / tan(ray_angle);
	if (data->ray->ray_left && step.x > 0)
		step.x = step.x * -1;
	if (data->ray->ray_right && step.x < 0)
		step.x = step.x * -1;
	return (step);
}

void	set_x_y(t_data *data, double *x, double *y, double ray_angle)
{
	*y = floor(data->player->y / data->ptr->tile_size) * data->ptr->tile_size;
	if (data->ray->ray_down)
		*y = *y + data->ptr->tile_size;
	*x = data->player->x + ((*y - data->player->y) / tan(ray_angle));
}

void	set_coordinates(double *x, double *y, t_point step)
{
	*x += step.x;
	*y += step.y;
}

void	set_j(t_data *data, double y, double *j)
{
	if (data->ray->ray_up)
		y = y - 1;
	*j = y;
}

void	horizontal_intersection(t_data *data, double ray_angle, t_point *h_p)
{
	t_point	step;
	double	x;
	double	y;
	double	i;
	double	j;

	ray_angle = normalize_angle(ray_angle);
	set_ray_direction(data, ray_angle);
	set_x_y(data, &x, &y, ray_angle);
	step.x = 0;
	step.y = 0;
	step = find_step(step, data, ray_angle);
	while (x >= 0 && x <= data->fake_win_width && y >= 0 && y <= data->fake_win_height)
	{
		i = x;
		set_j(data, y, &j);
		if (((int)j / 40 >= data->size) || ((int)i / 40 >= \
			ft_strlen(data->map[(int)j / 40 + data->index]))
			|| data->map[(int)j / 40 + data->index][(int)i / 40] == '1')
			break ;
		else
			set_coordinates(&x, &y, step);
	}
	h_p->x = x;
	h_p->y = y;
}
