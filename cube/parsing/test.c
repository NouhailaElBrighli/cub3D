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
		printf("s[%d] == %s\n", i, s[i]);
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

// void	print_param(t_param *param)
// {
// 	printf("-----------path-----------\n");
// 	print_tab(param->path);
// 	// printf("-----------floor-----------\n");
// 	// print_colors(param->floor);
// 	// printf("-----------floor-----------\n");
// 	// print_colors(param->ceiling);
// }

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
	// print_param(data->param);
}