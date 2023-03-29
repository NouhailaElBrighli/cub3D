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
	if (player->direction->e == 1)
		player->angle = 180.0f;
	if (player->direction->n == 1)
		player->angle = 270;
	if (player->direction->w == 1)
		player->angle = 0.0f;
	if (player->direction->s == 1)
		player->angle = 90.0f;
}

void	init(t_data *data)
{
	init_move_and_rot(data);
	init_player_angle(data->player);
	data->size = data->end_of_map - data->index + 1;
	data->ptr->tile_size = 40;
	data->FOV = 60;
	data->player->speed = 4;
	data->win_height = data->size * data->ptr->tile_size;
	data->win_width = data->long_line * data->ptr->tile_size;
	data->scale = 0.2;
	data->dis_3d = (double)data->win_width / (2 * tan((double)data->FOV * M_PI / 180));
}

void	init_rays_and_walls(t_data *data)
{
	data->ray = malloc(sizeof(t_ray));
	if (!data->ray)
		exit(EXIT_FAILURE);
	data->ray->angle = data->player->angle - (data->FOV  / 2);
	// data->rays->num_rays = data->win_width;
	data->walls = malloc(sizeof(t_walls));
	if (!data->walls)
		exit(EXIT_FAILURE);
	data->walls->x_start = 0;
	data->walls->y_start = 0;
}
