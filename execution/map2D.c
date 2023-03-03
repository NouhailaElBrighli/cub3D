#include "../parsing/parsing.h"

int	key_hook(int keycode, t_data *data)
{
	if (keycode == 53)
	{
		mlx_destroy_window(data->ptr->mlx, data->ptr->win);
		exit(0);
	}
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
    // static const double PI = 3.1415926535;
    float i, angle, x1, y1;

    for(i = 0; i < 360; i += 0.1)
    {
		angle = i;
		x1 = r * cos(angle * M_PI / 180);
		y1 = r * sin(angle * M_PI / 180);
		my_mlx_pixel_put(data, x + x1, y + y1, 0xE24666);
    }
}

void fill_window(t_data *data, char *row, int nbr_row)
{
	int i;

	i = 0;
	double r = 5.0;
	while (row[i] != '\0')
	{
		if (row[i] == '1')
		{
			for (int x = 0; x < 50; x++)
			{
				for (int y = 0; y < 50; y++)
					my_mlx_pixel_put(data, x, y, 0xFFFFFF);
			}
			mlx_put_image_to_window(data->ptr->mlx, data->ptr->win, data->ptr->img, i * data->ptr->img_dim, nbr_row * data->ptr->img_dim);
			free(data->ptr->img);
			data->ptr->img = mlx_new_image(data->ptr->mlx, data->ptr->img_dim, data->ptr->img_dim);
			data->ptr->addr = mlx_get_data_addr(data->ptr->img , &(data->ptr->bits_per_pixel), &(data->ptr->line_length), &(data->ptr->endian));
		}
		else if (row[i] == 'N')
		{

			while (r != 0)
			{
				DrawCircle(data, 25, 25, r);
				r -= 0.5;
			}
			mlx_put_image_to_window(data->ptr->mlx, data->ptr->win, data->ptr->img, i * data->ptr->img_dim, nbr_row * data->ptr->img_dim);
			free(data->ptr->img);
			data->ptr->img = mlx_new_image(data->ptr->mlx, data->ptr->img_dim, data->ptr->img_dim);
			data->ptr->addr = mlx_get_data_addr(data->ptr->img , &(data->ptr->bits_per_pixel), &(data->ptr->line_length), &(data->ptr->endian));
		}
		i++;
	}
}

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
		fill_window(data, data->map[row], row - data->index);
		row++;
	}
	mlx_hook(data->ptr->win, 17, 1L << 0, ft_close, data);
	mlx_hook(data->ptr->win, 2, 0, key_hook, data);
	mlx_loop(data->ptr->mlx);
}
