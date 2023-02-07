#ifndef PARSING_H
#define PARSING_H

#include "../cube.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int		check_extention(char *av);
char	**ft_split(char const *s, char c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strlen(char *s);
char	*ft_strdup(char *s);
int		check_new_line(char *s);
int		ft_strlen(char *s);
void	parsing(char *av, t_data *data);


#endif