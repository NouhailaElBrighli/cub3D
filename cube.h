#ifndef CUBE_H
#define CUBE_H

typedef struct s_identifier
{
	int NO;
	int SO;
	int WE;
	int EA;
	int F;
	int C;
}t_identifier;

typedef struct s_player
{
	int	N;
	int E;
	int W;
	int S;
}t_player;

typedef struct s_cub3d
{
	int		bits_per_pixel;
	int		line_length;
	int		img_dim;
	int		endian;
	char	*addr;
    void    *mlx;
    void	*win;
    void	*img;
}t_cub3d;

typedef struct	s_data
{
	char			**map;
	char			**path; // textures
	int				*floor; // rgb
	int				*ceiling; //rgb
	int				index; // index start of the map
	t_identifier	*id;
	t_player		*player;
	t_cub3d			*ptr;
}t_data;

#endif
