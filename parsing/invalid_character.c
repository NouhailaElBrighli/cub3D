/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invalid_character.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-brig <nel-brig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 20:35:32 by nel-brig          #+#    #+#             */
/*   Updated: 2023/03/29 04:00:17 by nel-brig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	is_valid(char c)
{
	if (c == ' ' || c == '\n' || c == '\0'
		|| c == '1' || c == '0' || c == 'N'
		|| c == 'E' || c == 'S' || c == 'W'
		|| c == '0')
		return (0);
	return (-1);
}

int	len_of_map(t_data *data)
{
	int	i;

	i = data->index;
	while (data->map[i])
		i++;
	return (--i);
}

int	find_end(t_data *data)
{
	int	size;
	int	i;

	size = len_of_map(data);
	i = 0;
	while (size > data->index)
	{
		if (data->map[size][i] == '1')
			return (size);
		if (data->map[size][i] == '\0')
		{
			i = 0;
			size--;
		}
		else
			i++;
	}
	return (0);
}

void	check_end_of_map(t_data *data, int i)
{
	int	j;

	i++;
	while (data->map[i])
	{
		j = 0;
		if (ft_strncmp(data->map[i], "\n", ft_strlen(data->map[i])) == 0)
		{
			i++;
			continue ;
		}
		else
		{
			while (data->map[i][j])
			{
				if (data->map[i][j] != '\t' && data->map[i][j] != ' '
				&& data->map[i][j] != '\n')
					ft_error(data, "invalid character\n");
				j++;
			}
		}
		i++;
	}
}

void	check_invalid_character(t_data *data)
{
	int	i;
	int	j;

	i = data->index;
	j = 0;
	while (data->map[i] && i <= data->end_of_map)
	{
		j = 0;
		if (ft_strncmp(data->map[i], "\n", ft_strlen(data->map[i])) == 0)
		{
			i++;
			continue ;
		}
		else
		{
			while (data->map[i][j])
			{
				if (is_valid(data->map[i][j]) == -1 || data->map[i][j] == '\t')
					ft_error(data, "invalid character\n");
				j++;
			}
		}
		i++;
	}
	check_end_of_map(data, data->end_of_map);
}
