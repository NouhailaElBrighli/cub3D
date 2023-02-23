#include "parsing.h"

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

void	fill_color(int *color, char **numbers)
{
	int i;

	i = 0;
	while (i < 3)
	{
		color[i] = ft_atoi(numbers[i]);
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
		num = ft_atoi(numbers[i]);
		if (num < 0 || num > 255)
			return(-1);
		i++;
	}
	return (0);
}