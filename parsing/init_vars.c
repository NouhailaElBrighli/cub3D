#include "parsing.h"

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

void init_player(t_data *data)
{
	data->player = malloc(sizeof(t_player));
	if (!data->player)
		exit(EXIT_FAILURE);
	data->player->type = malloc(sizeof(t_type));
	if (!data->player)
		exit(EXIT_FAILURE);
	data->player->type->N = 0;
	data->player->type->E = 0;
	data->player->type->W = 0;
	data->player->type->S = 0;
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
	int	i;

	i = 0;
	init_colors(data);
	data->path = malloc(sizeof(char *) * 5);
	if (!data->path)
		exit(EXIT_FAILURE);
	while (i < 5)
		data->path[i++] = NULL;
	init_player(data);
}