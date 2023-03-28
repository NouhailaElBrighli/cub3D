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

typedef struct s_point
{
	double x;
	double y;
}t_point;


void horizontal_intersection(t_data *data, double rayAngle, t_point *h_p)
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
	h_p->x = nextHorzTouchX;
	h_p->y = nextHorzTouchY;
}

void vertical_intersection(t_data *data, double rayAngle, t_point *v_p)
{
	double 	xstep;
	double 	ystep;
	double	xintercept;
	double	yintercept;
	int		isRayFacingUp;
	int		isRayFacingDown;
	int		isRayFacingLeft;
	int		isRayFacingRight;
	int 	foundVertWallHit = 0;
	double vertWallHitX = 0;
    double vertWallHitY = 0;
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
	v_p->x = nextVertTouchX;
	v_p->y = nextVertTouchY;
}

void	get_xend_yend(t_data *data, double *x_end, double *y_end, double rayAngle)
{
	t_point	v_p;
	t_point	h_p;
	double	horizontal_distance;
	double	vertical_distance;

	horizontal_intersection(data, rayAngle, &h_p);
	vertical_intersection(data, rayAngle, &v_p);
	horizontal_distance = distanceBetweenPoints(data->player->x, data->player->y, h_p.x, h_p.y);
    vertical_distance = distanceBetweenPoints(data->player->x, data->player->y, v_p.x, v_p.y);
    if (vertical_distance < horizontal_distance)
	{
		*x_end = v_p.x;
		*y_end = v_p.y;
		data->rays->distance = vertical_distance;
		// fprintf(stderr, "distance == %f", data->rays->distance);
    }
	else
	{
		*x_end = h_p.x;
		*y_end = h_p.y;
		data->rays->distance = horizontal_distance;
		// fprintf(stderr, "distance == %f", data->rays->distance);
    }
}
