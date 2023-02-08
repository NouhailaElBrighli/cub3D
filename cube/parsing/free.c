#include "parsing.h"

void ft_error(t_data *data)
{
	write(1, "Error\n", 6);
	ft_free(data->map);
	free(data);
	exit(EXIT_FAILURE);
}

void	ft_free(char **s)
{
	int	i;

	i = 0;
	while (s[i] != NULL)
		free(s[i++]);
	free(s);
}