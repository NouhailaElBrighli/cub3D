#include "../parsing/parsing.h"
#include <limits.h>

int		get_exact_length_of_the_line(t_data *data, double angle ,double x_start, double y_start)
{
	double len = 0;
	double x_end;
	double y_end;
	int x_end_in_map;
	int y_end_in_map;
	int			max_x;
	int			max_y;

	while (1)
	{
		x_end = x_start + (cos(angle) * len);
		y_end = y_start + (sin(angle) * len);
		x_end_in_map = (int)(x_end) / data->ptr->tile_size;
		y_end_in_map = (int)(y_end) / data->ptr->tile_size;
		if (data->map[y_end_in_map + data->index][x_end_in_map] == '1')
		{
			len -= 1;
			break ;
		}
		else if (data->map[y_end_in_map + 1 + data->index][x_end_in_map] == '1' && data->map[y_end_in_map + data->index][x_end_in_map +  1] == '1')
		{
			max_x = (x_end_in_map + 1) * data->ptr->tile_size - 1;
			max_y = (y_end_in_map + 1) * data->ptr->tile_size - 1;
			// fprintf(stderr ,"max_x = %d\n", max_x);
			// fprintf(stderr ,"max_y = %d\n", max_y);
			// fprintf(stderr ,"x_end = %f\n", x_end);
			// fprintf(stderr ,"y_end = %f\n", y_end);
			if ((int)x_end >= max_x && (int)y_end >= max_y)
			{
				len -= 1;
				break;
			}
		}
		else if (data->map[y_end_in_map - 1 + data->index][x_end_in_map] == '1' && data->map[y_end_in_map + data->index][x_end_in_map -  1] == '1')
		{
			max_x = x_end_in_map * data->ptr->tile_size + 1;
			max_y = y_end_in_map * data->ptr->tile_size + 1;
			if ((int)x_end <= max_x && (int)y_end <= max_y)
			{
				// fprintf(stderr ,"here\n");
				len -= 1;
				break;
			}
		}
		else if (data->map[y_end_in_map + data->index][x_end_in_map - 1] == '1' && data->map[y_end_in_map + 1 + data->index][x_end_in_map] == '1')
		{
			max_x = x_end_in_map * data->ptr->tile_size + 1;
			max_y = (y_end_in_map + 1) * data->ptr->tile_size - 1;
			if ((int)x_end <= max_x && (int)y_end >= max_y)
			{
				// fprintf(stderr ,"here\n");
				len -= 1;
				break;
			}
		}
		else if (data->map[y_end_in_map - 1 + data->index][x_end_in_map] == '1' && data->map[y_end_in_map + data->index][x_end_in_map + 1] == '1')
		{
			max_x = (x_end_in_map + 1) * data->ptr->tile_size - 1;
			max_y = y_end_in_map * data->ptr->tile_size + 1;
			if ((int)x_end >= max_x && (int)y_end <= max_y)
			{
				// fprintf(stderr ,"here\n");
				len -= 1;
				break;
			}
		}
		len += 1;
	}
	return (len);
}

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

void find_the_fucking_point(t_data *data, double *x_end, double *y_end, double rayAngle)
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

    double horzHitDistance = foundHorzWallHit ? distanceBetweenPoints(data->player->x, data->player->y, horzWallHitX, horzWallHitY) : INT_MAX;
    double vertHitDistance = foundVertWallHit ? distanceBetweenPoints(data->player->x, data->player->y, vertWallHitX, vertWallHitY) : INT_MAX;


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

/*void  horizontal_intersection(t_data *data, double *x_end, double *y_end, double rayAngle)
{
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
		if (data->map[(int)(yToCheck / data->ptr->tile_size) + data->index][(int)(xToCheck / data->ptr->tile_size)] == '1')
		{
			foundHorzWallHit = 1;
			break;
		}
		else
		{
			nextHorzTouchX += xstep;
			nextHorzTouchY += ystep;
		}
	}
	*x_end = nextHorzTouchX;
	*y_end = nextHorzTouchY;
}*/

/*void  vertical_intersection(t_data *data, double *x_end, double *y_end, double rayAngle)
{
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
	int 	foundVertWallHit = 0;

	rayAngle = normalizeAngle(rayAngle);
	
	isRayFacingDown = rayAngle > 0 && rayAngle < M_PI;
	isRayFacingUp   = !isRayFacingDown;
	isRayFacingRight = (rayAngle < (0.5 * M_PI)) || (rayAngle > (1.5 * M_PI));
	isRayFacingLeft = !isRayFacingRight;

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
		float xToCheck = nextVertTouchX + (isRayFacingLeft ? -1 : 0);
		float yToCheck = nextVertTouchY;
		
		if (data->map[(int)(yToCheck / data->ptr->tile_size) + data->index][(int)(xToCheck / data->ptr->tile_size)] == '1')
		{
			// found a wall hit
			// vertWallHitX = nextVertTouchX;
			// vertWallHitY = nextVertTouchY;
			// vertWallContent = map[(int)floor(yToCheck / TILE_SIZE)][(int)floor(xToCheck / TILE_SIZE)];
			foundVertWallHit = 1;
			break;
		} 
			else
			{
				nextVertTouchX += xstep;
				nextVertTouchY += ystep;
			}
		}
	*x_end = nextVertTouchX;
	*y_end = nextVertTouchY;
}*/

void	get_xend_yend(t_data *data, double *x_end, double *y_end, double ray_angle)
{
	// horizontal_intersection(data, x_end, y_end, ray_angle);
	// vertical_intersection(data, x_end, y_end, ray_angle);
	find_the_fucking_point(data, x_end, y_end, ray_angle);
	// TODO CHOOSE WHICH POINT 
}
