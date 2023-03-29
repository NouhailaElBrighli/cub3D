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
