#include "../parsing/parsing.h"

void	DrawLine(t_data *data, double angle ,double x_start, double y_start)
{
	double len = get_exact_length_of_the_line(data, angle, x_start, y_start);
	double x_end = x_start + (cos(angle) * len);
	double y_end = y_start + (sin(angle) * len);

    double dy = y_end - y_start;
	double dx = x_end - x_start;

    int step;

    if (fabs(dx) > fabs(dy))
        step = fabs(dx);
    else
        step = fabs(dy);

    double x_incr = dx / step;
    double y_incr = dy / step;

    double x = x_start;
    double y = y_start;

    for (int i = 0; i <= step; i++)
	{
		my_mlx_pixel_put(data, x, y, 0xE24666);//don't round the value
        x += x_incr;
        y += y_incr;
    }
}

void	DrawCircle(t_data *data, double x, double y, double r)
{
    int i, angle, x1, y1;

	while (r != 0)
	{    	
		for(i = 0; i < 360; i += 1)
    	{
			angle = i;
			x1 = (int)(r * cos(angle * M_PI / 180));
			y1 = (int)(r * sin(angle * M_PI / 180));
			my_mlx_pixel_put(data, x + x1, y + y1, 0xE24666);
    	}
		r -= 0.5;
	}
}

void	Draw_walls(t_data *data, char *row, int nbr_row)
{
	int i;

	i = 0;
	while (row[i] != '\0')
	{
		if (row[i] == '1')
		{
			for (int x = 0; x < data->ptr->tile_size; x++)
			{
				for (int y = 0; y < data->ptr->tile_size; y++)
					my_mlx_pixel_put(data, x + (i * data->ptr->tile_size), y + (nbr_row * data->ptr->tile_size), 0xFFFFFF);
			}
		}
		i++;
	}
}

void	DrawRays(t_data *data)
{
	int i;

	i = 0;
	data->rays = malloc(sizeof(t_rays));
	if (!data->rays)
		exit(EXIT_FAILURE);
	data->rays->angle = data->player->angle - (data->FOV  / 2);
	while (i < (data->long_line * data->ptr->tile_size))
	{
		DrawLine(data, data->rays->angle * M_PI / 180, data->player->x, data->player->y);
		data->rays->angle += (double)data->FOV / (data->long_line * data->ptr->tile_size); // typdecast obligatoir
		i++;
	}
}

void	DrawPlayer(t_data *data, char *row, int nbr_row)
{
	int i = 0;

	while (row[i] != '\0')
	{
		if (is_player(row[i], data->player, 1) == 1)
		{
			init_player_coordinates(data, (data->ptr->tile_size / 2) + (i * data->ptr->tile_size), (data->ptr->tile_size / 2) + (nbr_row * data->ptr->tile_size));
			init_player_coordinates_map(data, nbr_row, i);
			DrawCircle(data, data->player->x, data->player->y, 5);
			DrawLine(data, data->player->angle * M_PI / 180 ,data->player->x, data->player->y);
			DrawRays(data);
			break;
		}
		i++;
	}
}