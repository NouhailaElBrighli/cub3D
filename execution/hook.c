/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namine <namine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 03:59:43 by namine            #+#    #+#             */
/*   Updated: 2023/04/02 05:48:17 by namine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/parsing.h"

int	key_release(int keycode, t_data *data)
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

int	key_press(int keycode, t_data *data)
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

void	check_wall_collisions(t_data *data, t_point p, double angle)
{
	t_integer_point	p_in_map;

	p_in_map.x = (int)p.x / data->ptr->tile_size;
	int x = (int)data->player->x / data->ptr->tile_size;
	p_in_map.y = ((int)p.y / data->ptr->tile_size);
	int y = ((int)data->player->y / data->ptr->tile_size);
	if (data->map[p_in_map.y + data->index][x] != '1')
		data->player->y = p.y - (sin(angle) * 40);
	if (data->map[y + data->index][p_in_map.x] != '1')
		data->player->x = p.x - (cos(angle) * 40);
}

void	set_player_coordinates_and_check_collision(t_data *data, int flag)
{
	t_point	p;
	double	angle;

	if (flag == UP)
		angle = data->player->angle * M_PI / 180;
	else if (flag == DOWN)
		angle = (data->player->angle - 180) * M_PI / 180;
	else if (flag == LEFT)
		angle = (data->player->angle + 90) * M_PI / 180;
	else
		angle = (data->player->angle - 90) * M_PI / 180;
	p.x = data->player->x + (cos(angle) * (data->player->speed + 50));
	p.y = data->player->y + (sin(angle) * (data->player->speed + 50));
	check_wall_collisions(data, p, angle);
}


int	render_next_frame(t_data *data)
{
	if (sum_move_rot(data) == 0 || check_invalid_moves(data) == 0)
		return (0);
	if (data->rot_right == 1)
		data->player->angle -= 5;
	else if (data->rot_left == 1)
		data->player->angle += 5;
	if (data->move_up == 1)
		set_player_coordinates_and_check_collision(data, UP);
	else if (data->move_down == 1)
		set_player_coordinates_and_check_collision(data, DOWN);
	if (data->move_left == 1)
		set_player_coordinates_and_check_collision(data, LEFT);
	else if (data->move_right == 1)
		set_player_coordinates_and_check_collision(data, RIGHT);
	render_2d(data);
	return (0);
}
