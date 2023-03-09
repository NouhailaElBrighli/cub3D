#ifndef CUBE_H
#define CUBE_H

enum {
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

typedef struct s_identifier
{
	int NO;
	int SO;
	int WE;
	int EA;
	int F;
	int C;
}t_identifier;

typedef struct s_type
{
	int	N;
	int E;
	int W;
	int S;
}t_type;


typedef struct s_player
{
	t_type *type;
	int x;
	int y;
	float angle;
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


void	init_player_angle(t_player *player);
void	init_player_coordinates(t_data *data, int x, int y);

#endif
