#include "parsing.h"

int	is_player(char c, t_player *player, int flag)
{
	if (c == 'N' || c == 'E' || c == 'W' || c == 'S')
	{
		if (flag != 0)
			return (1);
		if (c == 'N')
			player->N++;
		else if (c == 'E')
			player->E++;
		else if (c == 'W')
			player->W++;
		else if (c == 'S')
			player->S++;
	}
	return(0);
}

void	search_player(t_data *data, char *s)
{
	int	i;

	i = 0;
	while(s[i])
	{
		is_player(s[i], data->player, 0);
		i++;
	}
}

void	check_t_player(t_data *data)
{
	int	sum;

	sum = data->player->N + data->player->E + data->player->S + data->player->W;
	if (sum != 1)
		ft_error(data, "Player Error\n");
}

void	check_for_player(t_data *data)
{
	int i;

	i = data->index;
	while (data->map[i])
	{
		search_player(data, data->map[i]);
		i++;
	}
	check_t_player(data);
}