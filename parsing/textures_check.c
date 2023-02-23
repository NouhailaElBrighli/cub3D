#include "parsing.h"

void	check_RGB(t_data *data,char *s, int idx, int *id, int *color)
{
	char	**numbers;
	char	*s1;
	s1 = NULL;
	while (s[idx] == ' ')
		idx++;
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

char	*check_path(t_data *data, char *s, int *id)
{
	int	idx;
	int	check;
	char *path;

	idx = 0;
	while (s[idx] == ' ')
		idx++;
	path = get_path(&s[idx]);
	check = ft_strlen(path) - 4;
	check_for_extention(data, check, path);
	idx += ft_strlen(path);
	while (s[idx] == ' ')
		idx++;
	if (s[idx] != '\n')
	{
		free(path);
		ft_error(data, "Error\n");
	}
	(*id)++;
	return (path);
}

int	is_path(t_data *data,char *s)
{
	int i;

	i = 0;
	if (ft_strncmp(&s[i], "NO ", ft_strlen("NO ")) == 0 && data->id->NO != 1)
	{
		data->path[0] = check_path(data, &s[i + 3], &data->id->NO);
		return (1);
	}
	else if (ft_strncmp(&s[i], "SO ", ft_strlen("SO ")) == 0 && data->id->SO != 1)
	{
		data->path[1] = check_path(data, &s[i + 3], &data->id->SO);
		return (1);
	}
	else if (ft_strncmp(&s[i], "WE ", ft_strlen("WE ")) == 0 && data->id->WE != 1)
	{
		data->path[2] = check_path(data, &s[i + 3], &data->id->WE);
		return (1);
	}
	else if (ft_strncmp(&s[i], "EA ", ft_strlen("EA ")) == 0 && data->id->EA != 1)
	{
		data->path[3] = check_path(data, &s[i + 3], &data->id->EA);
		return (1);
	}
	return (0);
}

int	check_identifier(char *s, t_data *data)
{
	int	i;

	i = 0;
	while (s[i] == ' ')
		i++;
	if (s[i] == '\n')
		return (0);
	if (is_path(data, &s[i]))
		return (0);
	else if (ft_strncmp(&s[i], "F ", ft_strlen("F ")) == 0 && data->id->F != 1)
	{
		check_RGB(data, s, i + 2, &data->id->F, data->floor);
		return (0);
	}
	else if (ft_strncmp(&s[i], "C ", ft_strlen("C ")) == 0 && data->id->C != 1)
	{
		check_RGB(data, s, i + 2, &data->id->C, data->ceiling);
		return (0);
	}
	else
		check_id(data);
	return(1);
}

int	check_textures(t_data *data)
{
	int	i;
	int j;

	i = 0;
	j = 0;
	allocate_param(data);
	while (data->map[i])
	{
		j = 0;
		if (ft_strncmp(data->map[i], "\n", ft_strlen(data->map[i])) != 0)
		{
			if (check_identifier(data->map[i], data) == 1)
				return (i);
		}
		i++;
	}
	return (0);
}