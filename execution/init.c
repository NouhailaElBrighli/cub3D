#include "../parsing/parsing.h"

void	init_player_coordinates(t_data *data, int x, int y)
{
	data->player->x = x;
	data->player->y = y;
}


void	init_player_angle(t_player *player)
{
	if (player->type->E == 1)
		player->angle = 0.0f;
	if (player->type->N == 1)
		player->angle = 90;	
	if (player->type->W == 1)
		player->angle = 180.0f;
	if (player->type->S == 1)
		player->angle = 270.0f;
}