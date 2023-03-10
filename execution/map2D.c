#include "../parsing/parsing.h"

int	key_hook(int keycode, t_data *data)
{
	if (keycode == 53)
	{
		mlx_destroy_window(data->ptr->mlx, data->ptr->win);
		exit(0);
	}
	if (keycode == 126)
	{
		// data->player->x += 
		//lfo9
	}
	if (keycode == 125)
	{
		//lta7t
	}
	if (keycode == 123)
	{
		//left
	}
	if (keycode == 124)
	{
		//right
	}
	fprintf(stderr, "keycode == %d\n", keycode);
	return (0);
}

int	ft_close(t_data *data)
{
	mlx_destroy_window(data->ptr->mlx, data->ptr->win);
	exit(0);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->ptr->addr + (y * data->ptr->line_length + x * (data->ptr->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void DrawCircle(t_data *data, int x, int y, int r)
{
    int i, angle, x1, y1;

    for(i = 0; i < 360; i += 1)
    {
		angle = i;
		x1 = r * cos(angle * M_PI / 180);
		y1 = r * sin(angle * M_PI / 180);
		my_mlx_pixel_put(data, x + x1, y + y1, 0xE24666);
    }
}

void DrawLine(t_data *data, int x_start, int y_start)
{
	float angle = 30.0f * M_PI / 180;
	int x_end = x_start + roundf((cos(angle) * 25.0f));// modify
	int y_end = y_start + roundf((sin(angle) * 25.0f));// modify

	int dx = x_end - x_start; //==> 27
    int dy = y_end - y_start; //==> 38

    int step;
	// fprintf(stderr, "cos(angle) * 30.0f == %f\n", cos(angle) * 30.0f);
	// fprintf(stderr, "sin(angle) * 30.0f == %f\n", sin(angle) * 30.0f);
    // If dx > dy we will take step as dx
    // else we will take step as dy to draw the complete
    // line
    if (abs(dx) > abs(dy))
        step = abs(dx);
    else
        step = abs(dy);
 
    // Calculate x-increment and y-increment for each step
    float x_incr = (float)dx / (float)step;//  ==> (x_start - x_end) / |(x_start - x_end)| == -+1
    float y_incr = (float)dy / (float)step;// ==> (y_start - y_end) / |(x_start - x_end)| == 

    // Take the initial points as x and y
    float x = (float)x_start;
    float y = (float)y_start;

	// fprintf(stderr, "x_start == %d, x_end == %d\n", x_start, x_end);
	// fprintf(stderr, "x_incr == %f, y_incr == %f, steps == %d\n", x_incr, y_incr, step);
	// fprintf(stderr, "y_start == %d, y_end == %d\n", y_start, y_end);
	// fprintf(stderr, "dx ==  == %d, dy == %d\n", dx, dy);
    for (int i = 0; i < step; i++) {
		my_mlx_pixel_put(data, round(x), round(y), 0xE24666);// should i round value of x and y
		// my_mlx_pixel_put(data, roundf(x), roundf(y), 0xE24666);// should i round value of x and y
		// fprintf(stderr, "(x, y) == (%f, %f)\n", x, y);
        x += x_incr;
        y += y_incr;
    }
}

void	DrawPlayer(t_data *data, char *row, int nbr_row)
{
	int i = 0;

	double r = 3.0;
	while (row[i] != '\0')
	{
		init_player_coordinates(data, i + 25, nbr_row + 25);
		if (row[i] == 'N')
		{
			while (r != 0)
			{
				DrawCircle(data, 25, 25, r);
				r -= 0.5;
			}
			DrawLine(data, 25, 25);
			// my_mlx_pixel_put(data, 0, 0, 0xE24666);
			// mlx_put_image_to_window(data->ptr->mlx, data->ptr->win, data->ptr->img, data->player->x, data->player->y);
			mlx_put_image_to_window(data->ptr->mlx, data->ptr->win, data->ptr->img, i * data->ptr->img_dim, nbr_row * data->ptr->img_dim);
			free(data->ptr->img);
			data->ptr->img = mlx_new_image(data->ptr->mlx, data->ptr->img_dim, data->ptr->img_dim);
			data->ptr->addr = mlx_get_data_addr(data->ptr->img , &(data->ptr->bits_per_pixel), &(data->ptr->line_length), &(data->ptr->endian));
		}
		i++;
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
			for (int x = 0; x < 50; x++)
			{
				for (int y = 0; y < 50; y++) {
					my_mlx_pixel_put(data, x, y, 0xFFFFFF);
				}
			}
			mlx_put_image_to_window(data->ptr->mlx, data->ptr->win, data->ptr->img, i * data->ptr->img_dim, nbr_row * data->ptr->img_dim);
			free(data->ptr->img);
			data->ptr->img = mlx_new_image(data->ptr->mlx, data->ptr->img_dim, data->ptr->img_dim);
			data->ptr->addr = mlx_get_data_addr(data->ptr->img , &(data->ptr->bits_per_pixel), &(data->ptr->line_length), &(data->ptr->endian));
		}
		i++;
	}
}

/*int drawing {
map
player
update coordonate of player func
}*/

void	execution(t_data *data)
{
	int row;

	data->ptr = malloc(sizeof(t_cub3d));
	data->ptr->mlx = mlx_init();
	if (!data->ptr->mlx)
		return ;
	data->ptr->img_dim = 50; // 32
	data->ptr->win = mlx_new_window(data->ptr->mlx, 1250, 450, "cub3D");
	data->ptr->img = mlx_new_image(data->ptr->mlx, data->ptr->img_dim, data->ptr->img_dim);
	data->ptr->addr = mlx_get_data_addr(data->ptr->img , &(data->ptr->bits_per_pixel), &(data->ptr->line_length), &(data->ptr->endian));
	row = data->index;
	while (data->map[row])
	{
		Draw_walls(data, data->map[row], row - data->index);
		row++;
	}
	init_player_angle(data->player);
	row = data->index;
	while (data->map[row])
	{
		DrawPlayer(data, data->map[row], row - data->index);
		row++;
	}
	mlx_hook(data->ptr->win, ON_DESTROY, 1L << 0, ft_close, data);
	mlx_hook(data->ptr->win, ON_KEYDOWN, 0, key_hook, data);
	mlx_loop(data->ptr->mlx);
}
