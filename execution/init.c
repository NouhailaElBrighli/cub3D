#include "../parsing/parsing.h"

void	init_player_coordinates_win(t_data *data, int x, int y)
{
	data->player->x_win = x;
	data->player->y_win = y;
}

void	init_player_coordinates_map(t_data *data, int x, int y)
{
	data->player->x_map = x;
	data->player->y_map = y;
}

void	init_player_angle(t_player *player)
{
	if (player->direction->E == 1)
		player->angle = 180.0f;
	if (player->direction->N == 1)
		player->angle = 270;	
	if (player->direction->W == 1)
		player->angle = 0.0f;
	if (player->direction->S == 1)
		player->angle = 90.0f;
}
