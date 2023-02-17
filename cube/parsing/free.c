#include "parsing.h"

void	ft_free(char **s)
{
	int	i;

	i = 0;
	while (s[i] != NULL)
		free(s[i++]);
	free(s);
}

void	free_param(t_data *data)
{
	ft_free(data->path);
	free(data->ceiling);
	free(data->floor);
}

void ft_error(t_data *data, char *s)
{
	write(1, s, ft_strlen(s));
	ft_free(data->map);
	free(data->id);
	free(data);
	ft_free(data->path);
	free(data->ceiling);
	free(data->floor);
	exit(EXIT_FAILURE);
}
