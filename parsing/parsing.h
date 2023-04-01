/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-brig <nel-brig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 20:53:28 by nel-brig          #+#    #+#             */
/*   Updated: 2023/04/01 03:23:08 by nel-brig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../cube.h"
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# include <mlx.h>

void	check_valid_path(t_data *data);
void	check_for_player(t_data *data);
int		is_player(char c, t_player *player, int flag);
void	check_invalid_character(t_data *data);
int		find_end(t_data *data);
char	*check_path(t_data *data, char *s, int *id);
void	check_for_extention(t_data *data, char *path);
void	parsing(char *av, t_data *data);
int		ft_strlen(char *s);
char	*ft_strdup(char *s);
int		check_new_line(char *s);
char	*get_next_line(int fd);
char	**ft_split(char const *s, char c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_atoi(const char *str, int idx);
char	*ft_strndup(char *s, size_t n);
int		check_textures(t_data *data);
void	allocate_param(t_data *data);
void	init_identifier(t_data *data);
void	ft_error(t_data *data, char *s);
void	ft_free(char **s);
void	check_id(t_data *data);
int		tab_size(char **s);
int		check_range(char **numbers);
void	fill_color(int *color, char **numbers);
char	*get_path(char *s);
void	print_player(t_player *player);
void	execution(t_data *data);
void	init_player_angle(t_player *player);
void	init_player_coordinates(t_data *data, int x, int y);
void	init_move_and_rot(t_data *data);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	draw_circle(t_data *data, double x, double y, double r);
void	drawline(t_data *data, double angle, int flag);
void	draw_walls(t_data *data, char *row, int nbr_row);
void	draw_rays(t_data *data);
void	draw_player(t_data *data, char *row, int nbr_row);
void	init(t_data *data);
int		ft_close(t_data *data);
int		check_invalid_moves(t_data *data);
int		sum_move_rot(t_data *data);
void	render_2d(t_data *data);
int		render_next_frame(t_data *data);
int		key_press(int keycode, t_data *data);
int		key_release(int keycode, t_data *data);
void	scale(t_data *data);
void	init_rays_and_walls(t_data *data);
void	get_xend_yend(t_data *data, double *x_end, double *y_end,
			double ray_angle);
void	draw_wall_3d(t_data *data, double len);
int		create_trgb(int t, int r, int g, int b);
int		my_mlx_pixel_get_color(t_textures *textures, int x, int y);
void	choose_texture(t_data *data, t_textures **tmp);
int		check_corner_1(t_data *data, t_integer_point p_in_map, t_point p);
int		check_corner_2(t_data *data, t_integer_point p_in_map, t_point p);
int		check_corner_3(t_data *data, t_integer_point p_in_map, t_point p);
int		check_corner_4(t_data *data, t_integer_point p_in_map, t_point p);
void	init_textures(t_data *data);
double	normalize_angle(double ray_angle);
void	horizontal_intersection(t_data *data, double ray_angle, t_point *h_p);
void	set_ray_direction(t_data *data, double ray_angle);
void	vertical_intersection(t_data *data, double ray_angle, t_point *v_p);

#endif
