#include "parsing.h"

void print_id(t_identifier *id)
{
	printf("NO == %d\n", id->NO);
	printf("SO == %d\n", id->SO);
	printf("WE == %d\n", id->WE);
	printf("EA == %d\n", id->EA);
	printf("C == %d\n", id->C);
	printf("F == %d\n", id->F);
}
void	print_tab(char **s)
{
	int i;

	i = 0;
	while (s[i] != NULL)
	{
		printf("s[%d] == %s", i, s[i]);
		i++;
	}
}

void print_colors(int *color)
{
	int i;

	i = 0;
	while (i < 3)
	{
		printf("RGB == %d\n", color[i]);
		i++;
	}
}

void	print_player(t_player *player)
{
	printf("player->N == %d\n", player->N);
	printf("player->S == %d\n", player->S);
	printf("player->E == %d\n", player->E);
	printf("player->W == %d\n", player->W);
}

void print_data(t_data *data)
{
	printf("===========map=============\n");
	print_tab(data->map);
	printf("===========id===============\n");
	print_id(data->id);
	printf("=============path===========\n");
	print_tab(data->path);
	printf("============floor===========\n");
	print_colors(data->floor);
	printf("===========ceiling===========\n");
	print_colors(data->ceiling);
	printf("=============start the map===========\n");
	printf("start == %s", data->map[data->index]);
	printf("=============player===========\n");
	print_player(data->player);
}