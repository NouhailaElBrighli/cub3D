/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namine <namine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 03:14:31 by nel-brig          #+#    #+#             */
/*   Updated: 2023/04/02 00:10:37 by namine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/parsing.h"

void	set_x_y_v(t_data *data, double *x, double *y, double ray_angle)
{
	*x = floor(data->player->x / data->ptr->tile_size) * data->ptr->tile_size;
	if (data->ray->ray_right)
		*x = *x + 65;
	*y = data->player->y + ((*x - data->player->x) * tan(ray_angle));
}

t_point	find_step_v(t_point step, t_data *data, double ray_angle)
{
	step.x = data->ptr->tile_size;
	if (data->ray->ray_left)
		step.x = step.x * -1;
	step.y = data->ptr->tile_size * tan(ray_angle);
	if ((data->ray->ray_up && step.y > 0))
		step.y = step.y * -1;
	if ((data->ray->ray_down && step.y < 0))
		step.y = step.y * -1;
	return (step);
}

void	set_coordinates_v(double *x, double *y, t_point step)
{
	*x = *x + step.x;
	*y = *y + step.y;
}

void	set_i_v(t_data *data, double x, int *i)
{
	if (data->ray->ray_left)
		x = x - 1;
	*i = x;
}

void	vertical_intersection(t_data *data, double ray_angle, t_point *v_p)
{
	t_point	step;
	double	x;
	double	y;
	int		i;
	int		j;

	ray_angle = normalize_angle(ray_angle);
	set_x_y_v(data, &x, &y, ray_angle);
	step.x = 0;
	step.y = 0;
	step = find_step_v(step, data, ray_angle);
	while (x >= 0 && x <= data->fake_win_width && y >= 0 && y <= data->fake_win_height)
	{
		j = y;
		set_i_v(data, x, &i);
		if (((int)j / 65 >= data->size) || ((int)i / 65 >= \
			ft_strlen(data->map[(int)j / 65 + data->index])) || \
			(data->map[(int)j / 65 + data->index][(int)i / 65] == '1'))
			break ;
		else
			set_coordinates_v(&x, &y, step);
	}
	v_p->x = x;
	v_p->y = y;
}
