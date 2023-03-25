#include "../parsing/parsing.h"

void	init_player_coordinates(t_data *data, int x, int y)
{
	data->player->x = x;
	data->player->y = y;
	data->player->radius = 5;
	data->player->x_map = x;
	data->player->y_map = y;
}

void	init_move_and_rot(t_data *data)
{
	data->move_up = 0;
	data->move_down = 0;
	data->move_right = 0;
	data->move_left = 0;
	data->rot_left = 0;
	data->rot_right = 0;
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

void	init(t_data *data)
{
	init_move_and_rot(data);
	init_player_angle(data->player);
	data->size = get_height(data);
	data->ptr->tile_size = 40;
	data->FOV = 60;
	data->player->speed = 2;
	data->win_width = data->long_line * data->ptr->tile_size;
	data->win_height = data->size * data->ptr->tile_size;
	data->scale = 0.2;
	data->dis_3d = data->win_width / (2 * tan((double)data->FOV * M_PI / 180));
}

void	init_rays_and_walls(t_data *data)
{
	data->rays = malloc(sizeof(t_rays));
	if (!data->rays)
		exit(EXIT_FAILURE);
	data->rays->angle = data->player->angle - (data->FOV  / 2);
	data->rays->num_rays = data->win_width;
	data->walls = malloc(sizeof(t_walls));
	if (!data->walls)
		exit(EXIT_FAILURE);
	data->walls->x_start = 0;
	data->walls->y_start = 0;
}