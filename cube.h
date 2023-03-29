/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-brig <nel-brig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 03:24:35 by namine            #+#    #+#             */
/*   Updated: 2023/03/29 04:00:33 by nel-brig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

enum
{
	KEY_PRESS = 2,
	KEY_RELEASE = 3,
	ON_DESTROY = 17
};

typedef struct s_identifier
{
	int	no;
	int	so;
	int	we;
	int	ea;
	int	f;
	int	c;
}t_identifier;

typedef struct s_type
{
	int	n;
	int e;
	int w;
	int s;
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

typedef struct s_ray
{
	double	angle;
    double	distance;
	int		rayUp;
	int		rayDown;
	int		rayLeft;
	int		rayRight;
}t_ray;

typedef struct	s_data
{
	char			**map;
	char			**path; // textures
	int				*floor; // rgb
	int				*ceiling; //rgb
	int				index; // index start of the map
	int				end_of_map;
	t_identifier	*id;
	t_player		*player;
	int				long_line;
	int				size;
	t_cub3d			*ptr;
	t_ray			*ray;
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

typedef struct s_point
{
	double x;
	double y;
}t_point;

enum
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
};

#endif
