/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-brig <nel-brig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 20:19:17 by nel-brig          #+#    #+#             */
/*   Updated: 2023/04/01 03:27:59 by nel-brig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	ft_check_successive(char *s, t_data *data)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == ',' && s[i + 1] == ',')
			ft_error(data, "Error\n");
		i++;
	}
}

void	check_rgb(t_data *data, char *s, int *id, int *color)
{
	char	**numbers;
	char	*s1;
	int		idx;

	s1 = NULL;
	idx = 0;
	while (s[idx] == ' ' || s[idx] == '\t')
		idx++;
	ft_check_successive(&s[idx], data);
	numbers = ft_split(&s[idx], ',');
	if (numbers == NULL || tab_size(numbers) != 3)
	{
		ft_free(numbers);
		ft_error(data, "Error\n");
	}
	if (check_range(numbers) == -1)
	{
		ft_free(numbers);
		ft_error(data, "Error\n");
	}
	fill_color(color, numbers);
	*id += 1;
}

int	is_path(t_data *data, char *s)
{
	int	i;

	i = 0;
	if (ft_strncmp(&s[i], "NO", ft_strlen("NO")) == 0 && data->id->no != 1)
	{
		data->path[0] = check_path(data, &s[i + 2], &data->id->no);
		return (1);
	}
	else if (ft_strncmp(&s[i], "SO", ft_strlen("SO")) == 0 && data->id->so != 1)
	{
		data->path[1] = check_path(data, &s[i + 2], &data->id->so);
		return (1);
	}
	else if (ft_strncmp(&s[i], "WE", ft_strlen("WE")) == 0 && data->id->we != 1)
	{
		data->path[2] = check_path(data, &s[i + 2], &data->id->we);
		return (1);
	}
	else if (ft_strncmp(&s[i], "EA", ft_strlen("EA")) == 0 && data->id->ea != 1)
	{
		data->path[3] = check_path(data, &s[i + 2], &data->id->ea);
		return (1);
	}
	return (0);
}

int	check_identifier(char *s, t_data *data)
{
	int	i;

	i = 0;
	while (s[i] == ' ' || s[i] == '\t')
		i++;
	if (s[i] == '\n')
		return (0);
	if (is_path(data, &s[i]))
		return (0);
	else if (ft_strncmp(&s[i], "F", ft_strlen("F")) == 0 && data->id->f != 1)
	{
		check_rgb(data, &s[i + 1], &data->id->f, data->floor);
		return (0);
	}
	else if (ft_strncmp(&s[i], "C", ft_strlen("C")) == 0 && data->id->c != 1)
	{
		check_rgb(data, &s[i + 1], &data->id->c, data->ceiling);
		return (0);
	}
	else
		check_id(data);
	return (1);
}

int	check_textures(t_data *data)
{
	int	i;

	i = 0;
	allocate_param(data);
	while (data->map[i])
	{
		if (ft_strncmp(data->map[i], "\n", ft_strlen(data->map[i])) != 0)
		{
			if (check_identifier(data->map[i], data) == 1)
				return (i);
		}
		i++;
	}
	return (0);
}
