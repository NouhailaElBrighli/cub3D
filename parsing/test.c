#include "parsing.h"

void print_id(t_identifier *id)
{
	printf("NO == %d\n", id->no);
	printf("SO == %d\n", id->so);
	printf("WE == %d\n", id->we);
	printf("EA == %d\n", id->ea);
	printf("C == %d\n", id->c);
	printf("F == %d\n", id->f);
}

void	print_tab(char **s)
{
	int i;

	i = 0;
	while (s[i] != NULL)
	{
		printf("s[%d] == |%s|\n", i, s[i]);
		i++;
	}
}

void print_colors(int *color)
{
	int i;

	i = 0;
	while (i < 3)
	{
		printf("rgb == %d\n", color[i]);
		i++;
	}
}

void	print_player(t_player *player)
{
	printf("player->n == %d\n", player->direction->n);
	printf("player->s == %d\n", player->direction->s);
	printf("player->e == %d\n", player->direction->e);
	printf("player->w == %d\n", player->direction->w);
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