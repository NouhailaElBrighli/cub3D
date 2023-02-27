#include "parsing.h"

int	is_valid(char c)
{
	if (c == ' ' || c == '\n' || c == '\0' || c == '1' || c == '0' || c == 'N' || c == 'E' || c == 'S' || c == 'W' || c == '0')
		return (0);
	return (-1);
}

void	check_invalid_character(t_data *data)
{
	int	i;
	int	j;

	i = data->index;
	j = 0;
	while (data->map[i])
	{
		if (ft_strncmp(data->map[i], "\n", ft_strlen(data->map[i])) == 0)
			i++;
		else if (is_valid(data->map[i][j]) == -1)
		{
			printf("char == |%c|\n", data->map[i][j]);
			ft_error(data, "invalid character\n");
		}
		else if (data->map[i][j] == '\0')
		{
			j = 0;
			i++;
		}
		else
			j++;
	}
}