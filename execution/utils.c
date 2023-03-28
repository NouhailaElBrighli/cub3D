#include "../parsing/parsing.h"

int		sum_move_rot(t_data *data)
{
	return (data->move_down + data->move_left + data->move_right + data->move_up + data->rot_left + data->rot_right);
}

int		check_invalid_moves(t_data *data)
{
	if ((data->move_up == 1 && data->move_down == 1 )|| (data->move_right == 1 && data->move_left == 1) || (data->rot_left == 1 && data->rot_right == 1))
		return (0);
	return(1);
}

int		get_height(t_data *data)
{
	int count;

	count = data->index;
	while (data->map[count])
		count++;
	count -= data->index;
	return (count);
}

int		ft_close(t_data *data)
{
	mlx_destroy_window(data->ptr->mlx, data->ptr->win);
	exit(0);
}

double	normalizeAngle( double rayAngle)
{
	rayAngle = remainder(rayAngle, M_PI * 2);
	if (rayAngle < 0)
		rayAngle += (M_PI * 2);
	return (rayAngle);
}

double distanceBetweenPoints(double x1, double y1, double x2, double y2)
{
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

void	get_xend_yend(t_data *data, double *x_end, double *y_end, double rayAngle)
{
	// TODO horizontal_intersection

	double 	xstep;
	double 	ystep;
	double	xintercept;
	double	yintercept;
	int		isRayFacingUp;
	int		isRayFacingDown;
	int		isRayFacingLeft;
	int		isRayFacingRight;
	double	horzWallHitX = 0;
    double	horzWallHitY = 0;
	int foundHorzWallHit = 0;

	rayAngle = normalizeAngle(rayAngle);
	
	isRayFacingDown = rayAngle > 0 && rayAngle < M_PI;
	isRayFacingUp   = !isRayFacingDown;
	isRayFacingRight = (rayAngle < (0.5 * M_PI)) || (rayAngle > (1.5 * M_PI));
	isRayFacingLeft = !isRayFacingRight;

	// find our first intersection 
	yintercept = floor(data->player->y / data->ptr->tile_size) * data->ptr->tile_size;
	yintercept += isRayFacingDown ? data->ptr->tile_size : 0;
	
	xintercept = data->player->x + ((yintercept - data->player->y) / tan(rayAngle));

	ystep = data->ptr->tile_size;
	ystep *= isRayFacingUp ? -1 : 1;

	xstep = data->ptr->tile_size / tan(rayAngle);
	xstep *= (isRayFacingLeft && xstep > 0) ? - 1 : 1;
	xstep *= (isRayFacingRight && xstep < 0) ? - 1 : 1;

	double nextHorzTouchX = xintercept;
    double nextHorzTouchY = yintercept;

	// Increment xstep and ystep until we find a wall

	while (nextHorzTouchX >= 0 && nextHorzTouchX <= data->win_width
	&& nextHorzTouchY >= 0 && nextHorzTouchY <= data->win_height)
	{
		double xToCheck = nextHorzTouchX;
        double yToCheck = nextHorzTouchY + (isRayFacingUp ? - 1 : 0);
		int a = xToCheck / data->ptr->tile_size;
		int b = yToCheck / data->ptr->tile_size;
		if ((b >= data->size) || (a >= ft_strlen(data->map[b + data->index])))
		{
			break;
		}
		if (data->map[b + data->index][a] == '1')
		{
			horzWallHitX = nextHorzTouchX;
            horzWallHitY = nextHorzTouchY;
			foundHorzWallHit = 1;
			break;
		}
		else
		{
			nextHorzTouchX += xstep;
			nextHorzTouchY += ystep;
		}
	}

	// TODO vertical_intersection 
	
	int 	foundVertWallHit = 0;
	double vertWallHitX = 0;
    double vertWallHitY = 0;
	rayAngle = normalizeAngle(rayAngle);

	// find our first intersection 
	xintercept = floor(data->player->x / data->ptr->tile_size) * data->ptr->tile_size;
	xintercept += isRayFacingRight ? data->ptr->tile_size : 0;
	
	yintercept = data->player->y + ((xintercept - data->player->x) * tan(rayAngle));

	xstep = data->ptr->tile_size;
	xstep *= isRayFacingLeft ? -1 : 1;

	ystep = data->ptr->tile_size * tan(rayAngle);
    ystep *= (isRayFacingUp && ystep > 0) ? -1 : 1;
    ystep *= (isRayFacingDown && ystep < 0) ? -1 : 1;


	double nextVertTouchX = xintercept;
    double nextVertTouchY = yintercept;

	// Increment xstep and ystep until we find a wall
	while (nextVertTouchX >= 0 && nextVertTouchX <= data->win_width && nextVertTouchY >= 0 && nextVertTouchY <= data->win_height)
	{
		double xToCheck = nextVertTouchX + (isRayFacingLeft ? -1 : 0);
		double yToCheck = nextVertTouchY;
		int a = xToCheck / data->ptr->tile_size;
		int b = yToCheck / data->ptr->tile_size;
		if ((b >= data->size) || (a >= ft_strlen(data->map[b + data->index])))
		{
			break;
		}
		if (data->map[b + data->index][a] == '1')
		{
			vertWallHitX = nextVertTouchX;
            vertWallHitY = nextVertTouchY;
			foundVertWallHit = 1;
			break;
		} 
		else
		{
			nextVertTouchX += xstep;
			nextVertTouchY += ystep;
		}
	}
	
	// TODO Calculate both horizontal and vertical hit distances and choose the smallest one

	double horzHitDistance = distanceBetweenPoints(data->player->x, data->player->y, nextHorzTouchX, nextHorzTouchY);
    double vertHitDistance = distanceBetweenPoints(data->player->x, data->player->y, nextVertTouchX, nextVertTouchY);


    if (vertHitDistance < horzHitDistance)
	{
		*x_end = nextVertTouchX;
		*y_end = nextVertTouchY;
		data->rays->distance = vertHitDistance;
		// fprintf(stderr, "distance == %f", data->rays->distance);
    }
	else
	{
		*x_end = nextHorzTouchX;
		*y_end = nextHorzTouchY;
		data->rays->distance = horzHitDistance;
		// fprintf(stderr, "distance == %f", data->rays->distance);
    }
}


/*
	void	cast_ray(t_game *g, double angle, t_ray *ray)
	{
		t_point	v_inter;
		t_point	h_inter;
		double	h_distance;
		double	v_distance;

		h_distance = 0;
		v_distance = 0;
		find_horizontal_intersection(g, angle, &h_inter);
		find_vertical_intersection(g, angle, &v_inter);
		h_distance = get_distance(h_inter, g->player->pos);
		v_distance = get_distance(v_inter, g->player->pos);
		ray->distance = get_min(h_distance, v_distance);
		if (ray->distance == h_distance)
		{
			ray->inter_x = h_inter.x;
			ray->inter_y = h_inter.y;
		}
		else
		{
			ray->inter_x = v_inter.x;
			ray->inter_y = v_inter.y;
		}
	}

*/