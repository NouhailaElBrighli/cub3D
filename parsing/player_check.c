/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-brig <nel-brig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 20:45:28 by nel-brig          #+#    #+#             */
/*   Updated: 2023/03/31 04:07:24 by nel-brig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	is_player(char c, t_player *player, int flag)
{
	if (c == 'N' || c == 'E' || c == 'W' || c == 'S')
	{
		if (flag != 0)
			return (1);
		if (c == 'N')
			player->direction->nort++;
		else if (c == 'E')
			player->direction->east++;
		else if (c == 'W')
			player->direction->west++;
		else if (c == 'S')
			player->direction->south++;
	}
	return (0);
}

void	search_player(t_data *data, char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		is_player(s[i], data->player, 0);
		i++;
	}
}

void	check_t_player(t_data *data)
{
	int	sum;

	sum = data->player->direction->nort + data->player->direction->east
		+ data->player->direction->south + data->player->direction->west;
	if (sum != 1)
		ft_error(data, "Player Error\n");
}

void	check_for_player(t_data *data)
{
	int	i;

	i = data->index;
	while (data->map[i])
	{
		search_player(data, data->map[i]);
		i++;
	}
	check_t_player(data);
}
