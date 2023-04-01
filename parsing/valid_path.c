/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-brig <nel-brig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 20:47:04 by nel-brig          #+#    #+#             */
/*   Updated: 2023/04/01 03:28:44 by nel-brig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	check_for_space(t_data *data, int i, int j)
{
	if (data->map[i][j + 1] == '\n' || data->map[i][j + 1] == '\0' || j == 0)
		ft_error(data, "Error\n");
	if (data->map[i][j + 1] == ' ' || data->map[i][j - 1] == ' ')
		ft_error(data, "Error\n");
	if (data->map[i + 1] == NULL)
		ft_error(data, "Error\n");
	if (ft_strlen(data->map[i - 1]) < j || ft_strlen(data->map[i + 1]) < j)
		ft_error(data, "Error\n");
	if (data->map[i + 1][j] == '\n' || data->map[i - 1][j] == '\0'
		|| data->map[i - 1][j] == '\n' || data->map[i + 1][j] == '\0')
		ft_error(data, "Error\n");
	if (data->map[i + 1][j] == ' ' || data->map[i - 1][j] == ' ')
		ft_error(data, "Error\n");
}

void	check_valid_path(t_data *data)
{
	int	i;
	int	j;

	i = data->index;
	j = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j] != '\0')
		{
			if (data->map[i][j] == '0'
				|| is_player(data->map[i][j], data->player, 1) == 1)
				check_for_space(data, i, j);
			j++;
		}
		i++;
	}
}
