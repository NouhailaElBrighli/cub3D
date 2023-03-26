#ifndef CUBE_H
#define CUBE_H

enum {
	KEY_PRESS = 2,
	KEY_RELEASE = 3,
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
	t_type	*direction;
	double	x;
	double	y;
	double	angle;
	int		x_map;
	int		y_map;
	double	speed;
	double	radius;
}t_player;

typedef struct s_cub3d
{
	int		bits_per_pixel;
	int		line_length;
	int		tile_size;
	int		endian;
	char	*addr;
    void    *mlx;
    void	*win;
    void	*img;
}t_cub3d;

typedef struct s_walls
{
	double	height;
	int	x_start;
	int	y_start;
}t_walls;



typedef struct s_rays
{
	double	angle;
	int		num_rays;
	int		len;
}t_rays;

typedef struct	s_data
{
	char			**map;
	char			**path; // textures
	int				*floor; // rgb
	int				*ceiling; //rgb
	int				index; // index start of the map
	t_identifier	*id;
	t_player		*player;
	int				long_line;
	int				size;
	t_cub3d			*ptr;
	t_rays			*rays;
	t_walls			*walls;
	int				FOV;
	int				move_left;
	int				move_right;
	int				move_up;
	int				move_down;
	int				rot_left;
	int				rot_right;
	double			scale;
	double			dis_3d;
	int				win_width;
	int				win_height;
}t_data;



enum {
	UP,
	DOWN,
	LEFT,
	RIGHT,
};



#endif
