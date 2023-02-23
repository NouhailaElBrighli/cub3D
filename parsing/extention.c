#include "parsing.h"

void	check_for_extention(t_data *data,int  check,char *path)
{
	int fd;
	
	if (ft_strncmp(&path[check], ".xpm", ft_strlen(&path[check])) != 0)
	{
		free(path);
		ft_error(data, "Error\n");
	}
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		free(path);
		ft_error(data, "Error\n");
	}
	close(fd);
}

