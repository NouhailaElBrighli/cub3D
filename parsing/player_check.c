/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-brig <nel-brig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 20:45:28 by nel-brig          #+#    #+#             */
/*   Updated: 2023/03/29 04:00:57 by nel-brig         ###   ########.fr       */
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
			player->direction->n++;
		else if (c == 'E')
			player->direction->e++;
		else if (c == 'W')
			player->direction->w++;
		else if (c == 'S')
			player->direction->s++;
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

	sum = data->player->direction->n + data->player->direction->e
		+ data->player->direction->s + data->player->direction->w;
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
