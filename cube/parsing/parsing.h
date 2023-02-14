#ifndef PARSING_H
#define PARSING_H

#include "../cube.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

typedef struct s_identifier
{
	int NO;
	int SO;
	int WE;
	int EA;
	int F;
	int C;
}t_identifier;

typedef struct s_param
{
	char	**path;
	int		*floor;
	int		*ceiling;
}t_param;


typedef struct  s_data
{
	char **map;
	t_param *param;
	t_identifier *id;
}t_data;


char	**ft_split(char const *s, char c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strlen(char *s);
char	*ft_strdup(char *s);
int		check_new_line(char *s);
int		ft_strlen(char *s);
void	parsing(char *av, t_data *data);
void	ft_free(char **s);
char	*get_next_line(int fd);
void	ft_error(t_data *data, char *s);
char	*ft_strndup(char *s, size_t n);
void	init_identifier(t_data *data);
int		ft_atoi(const char *str);


/*********************TEST***********************/

void	print_id(t_identifier *id);
void	print_tab(char **s);
void	print_data(t_data *data);

/*********************TEST***********************/


#endif