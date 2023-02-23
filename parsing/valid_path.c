#include "parsing.h"

void	check_for_space(t_data *data, int i, int j)
{
	if (data->map[i][j + 1] == '\n' || data->map[i][j + 1] == '\0' || j == 0)
		ft_error(data, "invalid map\n");
	if (data->map[i][j + 1] == ' ' || data->map[i][j - 1] == ' ')
		ft_error(data, "invalid map\n");
	if (data->map[i + 1] == NULL)
		ft_error(data, "invalid map\n");
	if (ft_strlen(data->map[i - 1]) < j || ft_strlen(data->map[i + 1]) < j)
		ft_error(data, "invalid map\n");
	if (data->map[i + 1][j] == '\n' || data->map[i - 1][j] == '\0')
		ft_error(data, "invalid map\n");
	if (data->map[i + 1][j] == ' ' || data->map[i - 1][j] == ' ')
		ft_error(data, "invalid map\n");
}

void	check_valid_path(t_data *data)
{
	int i;
	int j;

	i = data->index;
	j = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j] != '\0')
		{
			if (data->map[i][j] == '0' || is_player(data->map[i][j], data->player, 1) == 1)
				check_for_space(data, i, j);
			j++;
		}
		i++;
	}
}