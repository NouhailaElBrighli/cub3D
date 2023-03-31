/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-brig <nel-brig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 20:50:02 by nel-brig          #+#    #+#             */
/*   Updated: 2023/03/31 04:08:48 by nel-brig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*get_path(char *s)
{
	int		i;
	char	*path;

	i = 0;
	path = NULL;
	while (s[i] && s[i] != ' ' && s[i] != '\t' && s[i] != '\n')
		i++;
	path = ft_strndup(s, i);
	return (path);
}

void	check_id(t_data *data)
{
	if (data->id->no != 1 || data->id->so != 1 || data->id->we != 1
		|| data->id->ea != 1 || data->id->f != 1 || data->id->c != 1)
		ft_error(data, "Error\n");
}

int	tab_size(char **s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

void	fill_color(int *color, char **numbers)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		color[i] = ft_atoi(numbers[i], i);
		i++;
	}
	ft_free(numbers);
}

int	check_range(char **numbers)
{
	int	i;
	int	num;

	i = 0;
	while (numbers[i])
	{
		num = ft_atoi(numbers[i], i);
		if (num < 0 || num > 255)
			return (-1);
		i++;
	}
	return (0);
}
