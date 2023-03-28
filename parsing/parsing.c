/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-brig <nel-brig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 20:13:39 by nel-brig          #+#    #+#             */
/*   Updated: 2023/03/28 20:48:54 by nel-brig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	check_file(char *s)
{
	int	fd;
	int	cmp;

	cmp = ft_strlen(s) - 4;
	if (ft_strncmp(&s[cmp], ".cub", ft_strlen((&s[cmp]))) != 0)
	{
		printf("Invalid Extention\n");
		return (1);
	}
	fd = open(s, O_RDONLY);
	if (fd == -1)
	{
		perror("ERROR");
		return (1);
	}
	close(fd);
	return (0);
}

int	get_size(char *av, t_data *data)
{
	int		fd;
	int		size;
	char	*s;

	size = 1;
	fd = open(av, O_RDONLY);
	s = get_next_line(fd);
	while (s != NULL)
	{
		free(s);
		s = get_next_line(fd);
		size++;
	}
	if (size == 0)
	{
		write(1, "Empty map\n", 10);
		close(fd);
		free(data->id);
		free(data);
		exit(EXIT_FAILURE);
	}
	close(fd);
	return (size);
}

void	read_map(t_data *data, char *av)
{
	int		size;
	int		fd;
	int		i;

	i = 0;
	size = get_size(av, data);
	data->map = malloc(sizeof(char *) * (size + 1));
	if (!data->map)
		exit(EXIT_FAILURE);
	fd = open(av, O_RDONLY);
	data->map[i] = get_next_line(fd);
	while (data->map[i] != NULL)
		data->map[++i] = get_next_line(fd);
	close(fd);
}

void	get_long_line(t_data *data)
{
	int	max;
	int	i;
	int	j;

	i = data->index;
	max = ft_strlen(data->map[i]);
	j = i;
	while (i <= data->end_of_map)
	{
		if (ft_strlen(data->map[i]) >= max)
		{
			max = ft_strlen(data->map[i]);
			if (data->map[i][ft_strlen(data->map[i]) - 1] == '\n')
				max--;
			j = i;
		}
		i++;
	}
	data->long_line = max;
}

void	parsing(char *av, t_data *data)
{
	if (check_file(av) == 1)
	{
		free(data->id);
		free(data);
		exit(EXIT_FAILURE);
	}
	read_map(data, av);
	data->index = check_textures(data);
	data->end_of_map = find_end(data);
	check_invalid_character(data);
	check_for_player(data);
	check_valid_path(data);
	get_long_line(data);
	printf("there is no error\n");
}
