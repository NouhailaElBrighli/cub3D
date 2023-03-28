/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-brig <nel-brig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 20:53:28 by nel-brig          #+#    #+#             */
/*   Updated: 2023/03/28 20:56:35 by nel-brig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../cube.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <mlx.h>
# include <math.h>

/**************************player_check***************************/
void	check_valid_path(t_data *data);
/***********************player_check*************************/
void	check_for_player(t_data *data);
int		is_player(char c, t_player *player, int flag);
/***********************invalid character**********************/
void	check_invalid_character(t_data *data);
int		find_end(t_data *data);
/************************Extention*************************/
char	*check_path(t_data *data, char *s, int *id);
void	check_for_extention(t_data *data, char *path);
/*************************Parsing*****************************/
void	parsing(char *av, t_data *data);
void	init_identifier(t_data *data);
/**************************get_next_line*****************************/
int		ft_strlen(char *s);
char	*ft_strdup(char *s);
int		check_new_line(char *s);
char	*get_next_line(int fd);
/**************************libft******************************/
char	**ft_split(char const *s, char c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_atoi(const char *str, int idx);
char	*ft_strndup(char *s, size_t n);
/*******************textures_check.c*********************/
int		check_textures(t_data *data);
/*******************init_vars*************************/
void	allocate_param(t_data *data);
void	init_identifier(t_data *data);
/*********************Free.c***********************/
void	ft_error(t_data *data, char *s);
void	ft_free(char **s);
/*****************textures_utils****************/
void	check_id(t_data *data);
int		tab_size(char **s);
int		check_range(char **numbers);
void	fill_color(int *color, char **numbers);
char	*get_path(char *s);
/*********************TEST****************/
void	print_id(t_identifier *id);
void	print_tab(char **s);
void	print_data(t_data *data);
void	print_player(t_player *player);
/*********************EXECUTION****************/
void	execution(t_data *data);
void	init_player_angle(t_player *player);
void	init_player_coordinates(t_data *data, int x, int y);
// void	init_player_coordinates_map(t_data *data, int x, int y);
void	init_move_and_rot(t_data *data);
void	casting_rays(t_data *data);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		DrawLine(t_data *data, double angle, double x_start, double y_start);
void	DrawCircle(t_data *data, double x, double y, double r);
void	Draw_walls(t_data *data, char *row, int nbr_row);
void	DrawRays(t_data *data);
void	DrawPlayer(t_data *data, char *row, int nbr_row);
void	init(t_data *data);
int		get_height(t_data *data);
int		ft_close(t_data *data);
int		get_height(t_data *data);
int		check_invalid_moves(t_data *data);
int		sum_move_rot(t_data *data);
void	render_2D(t_data *data);
int		render_next_frame(t_data *data);
int		key_press(int keycode, t_data *data);
int		key_release(int keycode, t_data *data);
int		get_exact_length_of_the_line(t_data *data, double angle,
			double x_start, double y_start);
void	scale(t_data *data);
void	init_rays_and_walls(t_data *data);

#endif
