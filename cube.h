/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-brig <nel-brig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 03:24:35 by namine            #+#    #+#             */
/*   Updated: 2023/03/30 06:10:39 by nel-brig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

typedef struct s_drawline_data
{
	double	x_incr;
	double	y_incr;
	double	x_end;
	double	y_end;
	int		step;
	double	dy;
	double	dx;
	double	x;
	double	y;
}t_drawline_data;

enum
{
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
	int	NO;
	int	SO;
	int	WE;
	int	EA;
	int	F;
	int	C;
}t_identifier;

typedef struct s_type
{
	int	nort;
	int	east;
	int	west;
	int	south;
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
	void	*mlx;
	void	*win;
	void	*img;
}t_cub3d;

typedef struct s_walls
{
	double	height;
	int		x_start;
	int		y_start;
}t_walls;

typedef struct s_ray
{
	double	angle;
	double	distance;
	int		ray_up;
	int		ray_down;
	int		ray_left;
	int		ray_right;
	int		vertical_hit;
	int		horizontal_hit;
	int		x_hit;
	int		y_hit;
}t_ray;

typedef struct s_data
{
	char			**map;
	char			**path;
	int				*floor;
	int				*ceiling;
	int				index;
	int				end_of_map;
	t_identifier	*id;
	t_player		*player;
	int				long_line;
	int				size;
	t_cub3d			*ptr;
	t_ray			*ray;
	t_walls			*walls;
	int				fov;
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
	double	x;
	double	y;
}t_point;

enum
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
};


#endif
