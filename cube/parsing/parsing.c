#include "parsing.h"
#include "../cube.h"

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
		close(fd);
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
		printf("Empty Map");
		free(data);
		exit(EXIT_FAILURE);
	}
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



int check_identifier(char *s, t_data *data)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == ' ')
			i++;
		else
		{
			if (ft_strncmp(&s[i], "NO ", ft_strlen("NO ")) == 0)
				return (i + 3);
			else
				ft_error(data);
		}
	}
	return (0);
}

void	chek_path(t_data *data, char *s, int idx)
{
	while (s[idx])
	{
		while (s[idx] == ' ')
			idx++;
		int fd = open(&s[idx], O_RDONLY);
		if (fd == -1)
			ft_error(data);
	 	close(fd);
		// break;
	}
	exit(EXIT_FAILURE);
	(void) data;
}

void check_texture(t_data *data)
{
	int	i;
	int	j;
	int idx;

	i = 0;
	j = 0;
	while (data->map[i])
	{
		if (ft_strncmp(data->map[i], "\n", ft_strlen(data->map[i])) == 0)
			i++;

		else
		{
			idx = check_identifier(data->map[i], data);
			chek_path(data, data->map[i],idx);
		}
	}
}

void map_parsing(t_data *data)
{
	check_texture(data);
}

void	parsing(char *av, t_data *data)
{
	if (check_file(av) == 1)
	{
		free(data);
		exit(EXIT_FAILURE);
	}
	read_map(data, av);
	map_parsing(data);
}