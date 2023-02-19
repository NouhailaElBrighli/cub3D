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


typedef struct s_player
{
	int	N;
	int E;
	int W;
	int S;
}t_player;

typedef struct	s_data
{
	char			**map;
	char			**path;// textures
	int				*floor;// rgb
	int				*ceiling;//rgb
	int				index; // index start of the map
	t_identifier	*id;
	t_player		*player;
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
void	print_player(t_player *player);
/*********************TEST***********************/


#endif