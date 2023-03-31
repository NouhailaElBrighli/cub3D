// TODO    
    
    int	color = 0xFFFFFF;
	if (data->ray->horizontal_hit == 1)
	{
		if (data->player->y > data->ray->y_hit)
			color = 0xdf83e2;
		else
			color = 0x8883fd;
	}
	else
	{
		if (data->player->x > data->ray->x_hit)
			color = 0x7cff47;
		else
			color = 0xff0001;
	}
	while (y_start < y_end)
	{
		my_mlx_pixel_put(data, x_start, y_start, 0xFFFFFF);
		my_mlx_pixel_put(data, x_start, y_start, color);
		y_start++;
	}
