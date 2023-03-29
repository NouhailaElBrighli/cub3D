/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namine <namine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 03:59:43 by namine            #+#    #+#             */
/*   Updated: 2023/03/29 04:01:26 by namine           ###   ########.fr       */
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

void	set_player_coordinates_and_check_collision(t_data *data, int flag)
{
	double		x;
	double		y;
	int			x1;
	int			y1;
	double		angle;
	int			max_x;
	int			max_y;
	double		x_next;
	double		y_next;

	if (flag == UP)
		angle = data->player->angle * M_PI / 180;
	else if (flag == DOWN)
		angle = (data->player->angle - 180)* M_PI / 180;
	else if (flag == LEFT)
		angle = (data->player->angle + 90) * M_PI / 180;
	else
		angle = (data->player->angle - 90) * M_PI / 180;
	x = data->player->x + (cos(angle) * data->player->speed);
	y = data->player->y + (sin(angle) * data->player->speed);
	x_next = x + (cos(angle) * data->player->speed);
	y_next = y + (sin(angle) * data->player->speed);
	x1 = (int)x_next / data->ptr->tile_size;
	y1 = ((int)y_next / data->ptr->tile_size);
	
	if (data->map[y1 + data->index][x1] == '1')
	{
		return ;
	}
	if (data->map[y1 + 1 + data->index][x1] == '1' && data->map[y1 + data->index][x1 +  1] == '1')
	{
		max_x = (x1 + 1) * data->ptr->tile_size - 5;    
		max_y = (y1 + 1) * data->ptr->tile_size - 5;
		if ((int)x > max_x && (int)y > max_y)
		{
			return ;
		}
	}
	if (data->map[y1 - 1 + data->index][x1] == '1' && data->map[y1 + data->index][x1 -  1] == '1')
	{
		max_x = x1 * data->ptr->tile_size + 5;    
		max_y = y1 * data->ptr->tile_size + 5;
		if ((int)x < max_x && (int)y < max_y)
		{
			return ;
		}
	}
	if (data->map[y1 + data->index][x1 - 1] == '1' && data->map[y1 + 1 + data->index][x1] == '1')
	{
		max_x = (x1) * data->ptr->tile_size + 5;    
		max_y = (y1 + 1) * data->ptr->tile_size - 5;
		if ((int)x < max_x && (int)y > max_y)
		{
			return ;
		}
	}
	if (data->map[y1 - 1 + data->index][x1] == '1' && data->map[y1 + data->index][x1 + 1] == '1')
	{
		max_x = (x1 + 1) * data->ptr->tile_size - 5;    
		max_y = y1 * data->ptr->tile_size + 5;
		if ((int)x > max_x && (int)y < max_y)
		{
			return ;
		}
	}
	data->player->x = x;
	data->player->y = y;
}

int	render_next_frame(t_data *data)
{
	if (sum_move_rot(data) == 0 || check_invalid_moves(data) == 0)
		return (0);
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
	render_2d(data);
	return (0);
}
