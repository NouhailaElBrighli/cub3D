/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_collision.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-brig <nel-brig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 00:57:16 by nel-brig          #+#    #+#             */
/*   Updated: 2023/04/01 01:17:42 by nel-brig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/parsing.h"

int	check_corner_1(t_data *data, t_integer_point p_in_map, t_point p)
{
	t_point	p_max;

	if (data->map[p_in_map.y + 1 + data->index][p_in_map.x] == '1'
		&& data->map[p_in_map.y + data->index][p_in_map.x + 1] == '1')
	{
		p_max.x = ((p_in_map.x + 1) * data->ptr->tile_size - 5);
		p_max.y = ((p_in_map.y + 1) * data->ptr->tile_size - 5);
		if ((int)p.x > p_max.x && (int)p.y > p_max.y)
			return (1);
	}
	return (0);
}

int	check_corner_2(t_data *data, t_integer_point p_in_map, t_point p)
{
	t_point	p_max;

	if (data->map[p_in_map.y - 1 + data->index][p_in_map.x] == '1'
		&& data->map[p_in_map.y + data->index][p_in_map.x - 1] == '1')
	{
		p_max.x = (p_in_map.x * data->ptr->tile_size + 5);
		p_max.y = (p_in_map.y * data->ptr->tile_size + 5);
		if ((int)p.x < p_max.x && (int)p.y < p_max.y)
			return (1);
	}
	return (0);
}

int	check_corner_3(t_data *data, t_integer_point p_in_map, t_point p)
{
	t_point	p_max;

	if (data->map[p_in_map.y + data->index][p_in_map.x - 1] == '1'
		&& data->map[p_in_map.y + 1 + data->index][p_in_map.x] == '1')
	{
		p_max.x = (p_in_map.x) * data->ptr->tile_size + 5;
		p_max.y = (p_in_map.y + 1) * data->ptr->tile_size - 5;
		if ((int)p.x < p_max.x && (int)p.y > p_max.y)
			return (1);
	}
	return (0);
}

int	check_corner_4(t_data *data, t_integer_point p_in_map, t_point p)
{
	t_point	p_max;

	if (data->map[p_in_map.y - 1 + data->index][p_in_map.x] == '1'
		&& data->map[p_in_map.y + data->index][p_in_map.x + 1] == '1')
	{
		p_max.x = (p_in_map.x + 1) * data->ptr->tile_size - 5;
		p_max.y = p_in_map.y * data->ptr->tile_size + 5;
		if ((int)p.x > p_max.x && (int)p.y < p_max.y)
			return (1);
	}
	return (0);
}
