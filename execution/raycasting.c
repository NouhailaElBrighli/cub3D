/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-brig <nel-brig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 05:52:19 by namine            #+#    #+#             */
/*   Updated: 2023/03/30 06:11:16 by nel-brig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/parsing.h"

double	normalize_angle(double ray_angle)
{
	ray_angle = remainder(ray_angle, M_PI * 2);
	if (ray_angle <= 0)
	{
		ray_angle += (M_PI * 2);
	}
	return (ray_angle);
}

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

void	horizontal_intersection(t_data *data, double ray_angle, t_point *h_p)
{
	double	xstep;
	double	ystep;
	double	x;
	double	y;
	int		b;
	int		a;
	double	yto_check;
	double	xto_check;

	ray_angle = normalize_angle(ray_angle);
	set_ray_direction(data, ray_angle);
	y = floor(data->player->y / data->ptr->tile_size) * data->ptr->tile_size;
	y += data->ray->ray_down ? data->ptr->tile_size : 0;
	x = data->player->x + ((y - data->player->y) / tan(ray_angle));
	ystep = data->ptr->tile_size;
	ystep *= data->ray->ray_up ? -1 : 1;
	xstep = data->ptr->tile_size / tan(ray_angle);
	xstep *= (data->ray->ray_left && xstep > 0) ? - 1 : 1;
	xstep *= (data->ray->ray_right && xstep < 0) ? - 1 : 1;
	while (x >= 0 && x <= data->win_width
		&& y >= 0 && y <= data->win_height)
	{
		xto_check = x;
		yto_check = (y + (data->ray->ray_up ? - 1 : 0));
		a = xto_check / data->ptr->tile_size;
		b = yto_check / data->ptr->tile_size;
		if ((b >= data->size) || (a >= ft_strlen(data->map[b + data->index])))
			break ;
		if (data->map[b + data->index][a] == '1')
			break ;
		else
		{
			x += xstep;
			y += ystep;
		}
	}
	h_p->x = x;
	h_p->y = y;
}

void	vertical_intersection(t_data *data, double ray_angle, t_point *v_p)
{
	double	xstep;
	double	ystep;
	double	x;
	double	y;
	int		b;
	int		a;
	double	yto_check;
	double	xto_check;

	ray_angle = normalize_angle(ray_angle);
	x = floor(data->player->x / data->ptr->tile_size) * data->ptr->tile_size;
	x += data->ray->ray_right ? data->ptr->tile_size : 0;
	y = data->player->y + ((x - data->player->x) * tan(ray_angle));
	xstep = data->ptr->tile_size;
	xstep *= data->ray->ray_left ? -1 : 1;
	ystep = data->ptr->tile_size * tan(ray_angle);
	ystep *= (data->ray->ray_up && ystep > 0) ? -1 : 1;
	ystep *= (data->ray->ray_down && ystep < 0) ? -1 : 1;
	while (x >= 0 && x <= data->win_width && y >= 0 && y <= data->win_height)
	{
		xto_check = x + (data->ray->ray_left ? -1 : 0);
		yto_check = y;
		a = xto_check / data->ptr->tile_size;
		b = yto_check / data->ptr->tile_size;
		if ((b >= data->size) || (a >= ft_strlen(data->map[b + data->index])))
			break ;
		if (data->map[b + data->index][a] == '1')
			break ;
		else
		{
			x += xstep;
			y += ystep;
		}
	}
	v_p->x = x;
	v_p->y = y;
}

void	get_xend_yend(t_data *data, double *x_end, double *y_end, double ray_angle)
{
	double	horizontal_distance;
	double	vertical_distance;
	t_point	v_p;
	t_point	h_p;

	horizontal_distance = 0;
	vertical_distance = 0;
	horizontal_intersection(data, ray_angle, &h_p);
	vertical_intersection(data, ray_angle, &v_p);
	horizontal_distance = find_distance(data->player->x, data->player->y, h_p.x, h_p.y);
	vertical_distance = find_distance(data->player->x, data->player->y, v_p.x, v_p.y);
	if (vertical_distance < horizontal_distance)
	{
		*x_end = v_p.x;
		*y_end = v_p.y;
		data->ray->x_hit = *x_end;
		data->ray->y_hit = *y_end;
		data->ray->vertical_hit = 1;
		data->ray->distance = vertical_distance;
	}
	else
	{
		*x_end = h_p.x;
		*y_end = h_p.y;
		data->ray->x_hit = *x_end;
		data->ray->y_hit = *y_end;
		data->ray->horizontal_hit = 1;
		data->ray->distance = horizontal_distance;
	}
}

