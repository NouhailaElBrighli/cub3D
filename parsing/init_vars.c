/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-brig <nel-brig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 20:51:43 by nel-brig          #+#    #+#             */
/*   Updated: 2023/03/29 04:00:57 by nel-brig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	init_identifier(t_data *data)
{
	data->id = malloc(sizeof(t_identifier));
	if (!data->id)
		exit(EXIT_FAILURE);
	data->id->no = 0;
	data->id->so = 0;
	data->id->ea = 0;
	data->id->we = 0;
	data->id->f = 0;
	data->id->c = 0;
}

void	init_player(t_data *data)
{
	data->player = malloc(sizeof(t_player));
	if (!data->player)
		exit(EXIT_FAILURE);
	data->player->direction = malloc(sizeof(t_type));
	if (!data->player)
		exit(EXIT_FAILURE);
	data->player->direction->n = 0;
	data->player->direction->e = 0;
	data->player->direction->w = 0;
	data->player->direction->s = 0;
}

void	init_colors(t_data *data)
{
	int	i;

	i = 0;
	data->floor = malloc(sizeof(int) * 3);
	if (!data->floor)
		exit(EXIT_FAILURE);
	data->ceiling = malloc(sizeof(int) * 3);
	if (!data->ceiling)
		exit(EXIT_FAILURE);
	while (i < 3)
	{
		data->floor[i] = 0;
		data->ceiling[i] = 0;
		i++;
	}
}

void	allocate_param(t_data *data)
{
	int	i;

	i = 0;
	init_colors(data);
	data->path = malloc(sizeof(char *) * 5);
	if (!data->path)
		exit(EXIT_FAILURE);
	while (i < 5)
		data->path[i++] = NULL;
	init_player(data);
}
