#include "parsing.h"
#include "../cube.h"

void	init_identifier(t_data *data)
{
	data->id = malloc(sizeof(t_identifier));
	if(!data->id)
		exit(EXIT_FAILURE);
	data->id->NO = 0;
	data->id->SO = 0;
	data->id->EA = 0;
	data->id->WE = 0;
	data->id->F = 0;
	data->id->C = 0;
}

int	check_file(char *s)
{
	int	fd;
	int cmp;

	cmp = ft_strlen(s) - 4;
	if(ft_strncmp(&s[cmp], ".cub", ft_strlen((&s[cmp]))) != 0)
	{
		printf("Invalid Extention\n");
		return(1);
	}
	fd = open(s, O_RDONLY);
	if(fd == -1)
	{
		perror("ERROR");
		return(1);
	}
	close(fd);
	return (0);
}

int	get_size(char *av, t_data *data)
{
	int	fd;
	int	size;

	size = 0;
	fd = open(av, O_RDONLY);
	while(get_next_line(fd) != NULL)
		size++;
	if (size == 0)
	{
		close(fd);
		write(1, "Empty map", 10);
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

char	*get_path(char *s)
{
	int		i;
	char	*path;

	i = 0;
	path = NULL;
	while (s[i] && s[i] != ' ' && s[i] != '\n')
		i++;
	path = ft_strndup(s, i);
	return (path);
}

int	get_idx(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != ' ' && s[i] != '\n')
		i++;
	while (s[i] == ' ')
		i++;
	return (i);
}

char	*check_path(t_data *data, char *s, int *id)
{
	int	fd;
	int	idx;
	int	check;
	char *path;

	idx = 0;
	while (s[idx] == ' ')
		idx++;
	path = get_path(&s[idx]);
	check = ft_strlen(path) - 4;
	if (ft_strncmp(&path[check], ".xpm", ft_strlen(&path[check])) != 0)
		ft_error(data, "Error\n");
	fd = open(path, O_RDONLY);
	if (fd == -1)
		ft_error(data, "Error\n");
	close(fd);
	(*id)++;
	if (s[get_idx(&s[idx])] != '\n')
		ft_error(data, "Error\n");
	return (path);
}

void	check_id(t_data *data)
{
	if(data->id->NO != 1 || data->id->SO != 1 || data->id->WE != 1 
			|| data->id->EA != 1 || data->id->F != 1 || data->id->C != 1)
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

int	check_range(char **numbers)
{
	int	i;
	int	num;

	i = 0;
	while (numbers[i])
	{
		num = ft_atoi(numbers[i]);
		if (num < 0 || num > 255)
			return(-1);
		i++;
	}
	return (0);
}

void	fill_color(int *color, char **numbers)
{
	int i;

	i = 0;
	while (i < 3)
	{
		color[i] = ft_atoi(numbers[i]);
		i++;
	}
}

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

void	check_identifier(char *s, t_data *data)
{
	int	i;

	i = 0;
	while (s[i])
	{
		while (s[i] == ' ')
			i++;
		if (s[i] == '\n')
			break;
		if (ft_strncmp(&s[i], "NO ", ft_strlen("NO ")) == 0)
		{
			data->path[0] = check_path(data, &s[i + 3], &data->id->NO);
			break;
		}
		else if (ft_strncmp(&s[i], "SO ", ft_strlen("SO ")) == 0)
		{
			data->path[1] = check_path(data, &s[i + 3], &data->id->SO);
			break;
		}
		else if (ft_strncmp(&s[i], "WE ", ft_strlen("WE ")) == 0)
		{
			data->path[2] = check_path(data, &s[i + 3], &data->id->WE);
			break;
		}
		else if (ft_strncmp(&s[i], "EA ", ft_strlen("EA ")) == 0)
		{
			data->path[3] = check_path(data, &s[i + 3], &data->id->EA);
			break;
		}
		else if (ft_strncmp(&s[i], "F ", ft_strlen("F ")) == 0)
		{
			check_RGB(data, s, i + 2, &data->id->F, data->floor);
			break;
		}
		else if (ft_strncmp(&s[i], "C ", ft_strlen("C ")) == 0)
		{
			check_RGB(data, s, i + 2, &data->id->C, data->ceiling);
			break;
		}
		else
		{
			check_id(data);
			break;
		}
	}
}

void init_colors(t_data *data)
{
	int i;
	i = 0;
	data->floor = malloc(sizeof(int) * 3);
	if (!data->floor)
		exit(EXIT_FAILURE);
	data->ceiling = malloc(sizeof(int) * 3);
	if (!data->ceiling)
		exit(EXIT_FAILURE);
	while(i < 3)
	{
		data->floor[i] = 0;
		data->ceiling[i] = 0;
		i++;
	}
}

void	allocate_param(t_data *data)
{
	init_colors(data);
	data->path = malloc(sizeof(char *) * 5);
	if (!data->path)
		exit(EXIT_FAILURE);
	data->path[4] = NULL;
}

void	check_texture(t_data *data)
{
	int	i;

	i = 0;
	allocate_param(data);
	while (data->map[i])
	{
		if (ft_strncmp(data->map[i], "\n", ft_strlen(data->map[i])) != 0)
			check_identifier(data->map[i], data);
		i++;
	}
	check_id(data);//add it after loop
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
	check_texture(data);
	print_data(data);
	printf("everything is ok\n");
}
