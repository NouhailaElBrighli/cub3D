#include "parsing.h"

void	ft_free(char **s)
{
	int	i;

	i = 0;
	while (s[i] != NULL)
		free(s[i++]);
	free(s);
}

void	free_param(t_param *param)
{
	ft_free(param->path);
	free(param->floor);
	free(param->ceiling);
	free(param);
}

void ft_error(t_data *data, char *s)
{
	write(1, s, ft_strlen(s));
	ft_free(data->map);
	free(data->id);
	free(data);
	free_param(data->param);
	exit(EXIT_FAILURE);
}
