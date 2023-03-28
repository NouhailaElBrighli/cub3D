/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-brig <nel-brig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 20:49:08 by nel-brig          #+#    #+#             */
/*   Updated: 2023/03/28 20:49:43 by nel-brig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	ft_free(char **s)
{
	int	i;

	i = 0;
	if (s == NULL)
		return ;
	while (s[i] != NULL)
		free(s[i++]);
	free(s);
}

void	free_path(t_data *data)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		if (data->path[i] != NULL)
			free(data->path[i]);
		i++;
	}
	free(data->path);
}

void	ft_error(t_data *data, char *s)
{
	write(1, s, ft_strlen(s));
	ft_free(data->map);
	free(data->id);
	free_path(data);
	free(data->ceiling);
	free(data->floor);
	free(data->player->direction);
	free(data->player);
	free(data);
	exit(EXIT_FAILURE);
}
