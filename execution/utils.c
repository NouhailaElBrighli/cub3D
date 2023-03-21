#include "../parsing/parsing.h"

double	get_exact_length_of_the_line(t_data *data, double angle ,double x_start, double y_start)
{
	double len = 0;
	double x_end;
	double y_end;
	int x_end_in_map;
	int y_end_in_map;

	while (1)
	{
		x_end = x_start + (cos(angle) * len);
		y_end = y_start + (sin(angle) * len);
		x_end_in_map = (int)(x_end / data->ptr->tile_size);
		y_end_in_map = (int)(y_end / data->ptr->tile_size);
		if (data->map[y_end_in_map + data->index][x_end_in_map] == '1')
		{
			len -= 1;
			break ;
		}
		len += 1;
	}
	return (len);
}


int		sum_move_rot(t_data *data)
{
	return (data->move_down + data->move_left + data->move_right + data->move_up + data->rot_left + data->rot_right);
}


int	check_invalid_moves(t_data *data)
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
