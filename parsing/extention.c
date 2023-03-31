/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extention.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namine <namine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 20:30:07 by nel-brig          #+#    #+#             */
/*   Updated: 2023/03/30 22:25:23 by namine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*check_path(t_data *data, char *s, int *id)
{
	int		idx;
	char	*path;

	idx = 0;
	if (s[idx] != ' ' && s[idx] != '\t')
		ft_error(data, "Error\n");
	while (s[idx] == ' ' || s[idx] == '\t')
		idx++;
	path = get_path(&s[idx]);
	check_for_extention(data, path);
	idx += ft_strlen(path);
	while (s[idx] == ' ' || s[idx] == '\t')
		idx++;
	if (s[idx] != '\n')
	{
		free(path);
		ft_error(data, "Error\n");
	}
	(*id)++;
	return (path);
}

void	check_for_extention(t_data *data, char *path)
{
	int	fd;
	int	check;

	if (ft_strlen(path) < 4)
	{
		free(path);
		ft_error(data, "Error\n");
	}
	check = ft_strlen(path) - 4;
	if (ft_strncmp(&path[check], ".xpm", ft_strlen(&path[check])) != 0)
	{
		free(path);
		ft_error(data, "Error\n");
	}
	fd = open(path, O_RDONLY);
	fprintf(stderr, "path == %s\n", path);
	if (fd == -1)
	{
	fprintf(stderr, "here\n");
		free(path);
		ft_error(data, "Error\n");
	}
	close(fd);
}
