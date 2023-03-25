#include "../parsing/parsing.h"

int		key_release(int keycode, t_data *data)
{
	if (keycode == 13)
		data->move_up = 0;
	else if (keycode == 1)
		data->move_down = 0;
	else if (keycode == 0)
		data->move_right = 0;
	else if (keycode == 2)
		data->move_left = 0;
	else if (keycode == 124)
		data->rot_left = 0;
	else if (keycode == 123)
		data->rot_right = 0;
	return (0);
}


int		key_press(int keycode, t_data *data)
{
	if (keycode == 53)
		ft_close(data);
	else if (keycode == 13)
		data->move_up = 1;
	else if (keycode == 1)
		data->move_down = 1;
	else if (keycode == 0)
		data->move_right = 1;
	else if (keycode == 2)
		data->move_left = 1;
	else if (keycode == 124)
		data->rot_left = 1;
	else if (keycode == 123)
		data->rot_right = 1;
	return (0);
}

void	set_player_coordinates_and_check_collision(t_data *data, int flag)
{
	double	x;
	double	y;
	int		x1;
	int		y1;
	double	angle;

	if (flag == UP)
		angle = data->player->angle * M_PI / 180;
	else if (flag == DOWN)
		angle = (data->player->angle - 180)* M_PI / 180;
	else if (flag == LEFT)
		angle = (data->player->angle + 90) * M_PI / 180;
	else
		angle = (data->player->angle - 90) * M_PI / 180;
	
	x = data->player->x + cos(angle) * data->player->speed;
	y = data->player->y + sin(angle) * data->player->speed;

	x1 = (int)x / data->ptr->tile_size;
	y1 = (int)y / data->ptr->tile_size;
	if (data->map[y1 + data->index][x1] != '1')
	{
		data->player->x = x;
 		data->player->y = y;
	}
}

int		render_next_frame(t_data *data)
{
	if (sum_move_rot(data) == 0 || check_invalid_moves(data) == 0)
		return(0);
	if (data->rot_right == 1)
		data->player->angle -= 3;
	else if (data->rot_left == 1)
		data->player->angle += 3;
	if (data->move_up == 1)
		set_player_coordinates_and_check_collision(data, UP);
	else if (data->move_down == 1)
		set_player_coordinates_and_check_collision(data, DOWN);
	if (data->move_left == 1)
		set_player_coordinates_and_check_collision(data, LEFT);
	else if (data->move_right == 1)
		set_player_coordinates_and_check_collision(data, RIGHT);
	render_2D(data);
	return (0);
}
