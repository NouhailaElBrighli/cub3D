#ifndef PARSING_H
#define PARSING_H

#include "../cube.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <mlx.h>

/**************************player_check***************************/
void	check_valid_path(t_data *data);


/***********************player_check*************************/
void	check_for_player(t_data *data);
int		is_player(char c, t_player *player, int flag);

/***********************invalid character**********************/
void	check_invalid_character(t_data *data);

/************************Extention*************************/

void	check_for_extention(t_data *data,int  check,char *path);

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
int		ft_atoi(const char *str);
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

#endif
