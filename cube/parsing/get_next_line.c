/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-brig <nel-brig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 11:54:00 by nel-brig          #+#    #+#             */
/*   Updated: 2023/02/05 21:05:09 by nel-brig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*ft_strjoin(char *save, char *buff)
{
	char	*a;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!*buff && !save)
		return (NULL);
	if (!save)
		return (ft_strdup(buff));
	a = (char *) malloc(sizeof(char) * (ft_strlen(save) + ft_strlen(buff) + 1));
	if (!a)
		return (NULL);
	while (save[i])
	{
		a[i] = save[i];
		i++;
	}
	while (buff[j])
		a[i++] = buff[j++];
	a[i] = '\0';
	free (save);
	return (a);
}

char	*read_func(int fd, char *save)
{
	char	*buff;
	int		d;

	d = 1;
	buff = NULL;
	buff = (char *) malloc (sizeof(char) * 2);
	if (!buff)
		return (NULL);
	while (check_new_line(save) == -1 && d != 0)
	{
		d = read(fd, buff, 1);
		if (d == -1)
		{
			free (buff);
			return (NULL);
		}
		buff[d] = '\0';
		save = ft_strjoin(save, buff);
	}
	free (buff);
	return (save);
}

char	*ft_substr(char *s)
{
	char	*a;
	int		i;

	i = 0;
	a = NULL;
	a = (char *) malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!a)
		return (NULL);
	while (s[i] && s[i] != '\n')
	{
		a[i] = s[i];
		i++;
	}
	if (s[i] == '\n')
		a[i++] = '\n';
	a[i] = '\0';
	return (a);
}

char	*ft_substr1(char *save)
{
	char	*a;
	int		j;
	int		d;

	j = 0;
	a = NULL;
	d = check_new_line(save);
	if (d == -1 || save[d + 1] == '\0')
	{
		free (save);
		return (NULL);
	}
	a = malloc (sizeof(char) * (ft_strlen(save) - d));
	if (!a)
		return (NULL);
	d = d + 1;
	while (save[d])
		a[j++] = save[d++];
	a[j] = '\0';
	free (save);
	return (a);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*save;

	line = NULL;
	save = read_func(fd, save);
	if (!save)
		return (NULL);
	line = ft_substr(save);
	save = ft_substr1(save);
	return (line);
}
