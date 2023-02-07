#include "parsing.h"
#include "../cube.h"

void	ft_free(char **s)
{
	int	i;

	i = 0;
	while (s[i] != NULL)
		free(s[i++]);
	free(s);
}

int	check_last_one(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	i--;
	if (ft_strncmp(s[i], "cub", ft_strlen("cub")) == 0)
	{
		ft_free(s);
		return (0);
	}
	ft_free(s);
	printf("Invalid Extention\n");
	return (1);
}

int	check_extention(char *av)
{
	char	**s;

	s = ft_split(av, '.');
	if (s == NULL)
	{
		ft_free(s);
		return (1);
	}
	if (check_last_one(s) == 1)
		return (1);
	return (0);
}

int get_size(char *av)
{
	int fd;
	int size;

	
}

void	read_map(t_data *data, char *av)
{
	int size;
	
	size = get_size(av);
}

void	parsing(char *av, t_data *data)
{
	int	fd;

	if (check_extention(av) == 1)
	{
		free(data);
		exit(EXIT_FAILURE);
	}
	fd = open(av, O_RDONLY);
	if(fd == -1)
	{
		free(data);
		perror("ERROR");
		exit(EXIT_FAILURE);
	}
	close(fd);
	read_map(data, av);
}