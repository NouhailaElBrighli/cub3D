#include "../parsing/parsing.h"

double	normalizeAngle(double rayAngle)
{
	rayAngle = remainder(rayAngle, M_PI * 2);
	if (rayAngle <= 0) // TODO <= ??
		rayAngle += (M_PI * 2);
	return (rayAngle);
}

double	find_distance(double x1, double y1, double x2, double y2)
{
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

void set_ray_direction(t_data *data, double rayAngle)
{
	data->ray->rayDown = rayAngle > 0 && rayAngle < M_PI;
	data->ray->rayUp   = !data->ray->rayDown;
	data->ray->rayRight = (rayAngle < 90 * (M_PI / 180)) || (rayAngle > (270 * (M_PI / 180)));
	data->ray->rayLeft = !data->ray->rayRight;
}

void	horizontal_intersection(t_data *data, double rayAngle, t_point *h_p)
{
	double 	xstep;
	double 	ystep;
	double	x;
	double	y;

	rayAngle = normalizeAngle(rayAngle);
	set_ray_direction(data, rayAngle);
	y = floor(data->player->y / data->ptr->tile_size) * data->ptr->tile_size;
	y += data->ray->rayDown ? data->ptr->tile_size : 0;
	x = data->player->x + ((y - data->player->y) / tan(rayAngle));
	ystep = data->ptr->tile_size;
	ystep *= data->ray->rayUp ? -1 : 1;
	xstep = data->ptr->tile_size / tan(rayAngle);
	xstep *= (data->ray->rayLeft && xstep > 0) ? - 1 : 1;
	xstep *= (data->ray->rayRight && xstep < 0) ? - 1 : 1;
	while (x >= 0 && x <= data->win_width
	&& y >= 0 && y <= data->win_height)
	{
		double xToCheck = x;
        double yToCheck = y + (data->ray->rayUp ? - 1 : 0);
		int a = xToCheck / data->ptr->tile_size;
		int b = yToCheck / data->ptr->tile_size;
		if ((b >= data->size) || (a >= ft_strlen(data->map[b + data->index])))
			break;
		if (data->map[b + data->index][a] == '1')
			break;
		else
		{
			x += xstep;
			y += ystep;
		}
	}
	h_p->x = x;
	h_p->y = y;
}

void	vertical_intersection(t_data *data, double rayAngle, t_point *v_p)
{
	double 	xstep;
	double 	ystep;
	double	x;
	double	y;

	rayAngle = normalizeAngle(rayAngle);
	x = floor(data->player->x / data->ptr->tile_size) * data->ptr->tile_size;
	x += data->ray->rayRight ? data->ptr->tile_size : 0;
	y = data->player->y + ((x - data->player->x) * tan(rayAngle));
	xstep = data->ptr->tile_size;
	xstep *= data->ray->rayLeft ? -1 : 1;
	ystep = data->ptr->tile_size * tan(rayAngle);
    ystep *= (data->ray->rayUp && ystep > 0) ? -1 : 1;
    ystep *= (data->ray->rayDown && ystep < 0) ? -1 : 1;
	while (x >= 0 && x <= data->win_width && y >= 0 && y <= data->win_height)
	{
		double xToCheck = x + (data->ray->rayLeft ? -1 : 0);
		double yToCheck = y;
		int a = xToCheck / data->ptr->tile_size;
		int b = yToCheck / data->ptr->tile_size;
		if ((b >= data->size) || (a >= ft_strlen(data->map[b + data->index])))
			break;
		if (data->map[b + data->index][a] == '1')
			break;
		else
		{
			x += xstep;
			y += ystep;
		}
	}
	v_p->x = x;
	v_p->y = y;
}

void	get_xend_yend(t_data *data, double *x_end, double *y_end, double rayAngle)
{
	double	horizontal_distance;
	double	vertical_distance;
	t_point	v_p;
	t_point	h_p;

	horizontal_distance = 0;
	vertical_distance = 0;
	horizontal_intersection(data, rayAngle, &h_p);
	vertical_intersection(data, rayAngle, &v_p);
	horizontal_distance = find_distance(data->player->x, data->player->y, h_p.x, h_p.y);
    vertical_distance = find_distance(data->player->x, data->player->y, v_p.x, v_p.y);
    if (vertical_distance < horizontal_distance)
	{
		*x_end = v_p.x;
		*y_end = v_p.y;
		data->ray->distance = vertical_distance;
    }
	else
	{
		*x_end = h_p.x;
		*y_end = h_p.y;
		data->ray->distance = horizontal_distance;
    }
}
