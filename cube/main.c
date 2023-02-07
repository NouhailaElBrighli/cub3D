#include "cube.h"
#include "parsing/parsing.h"

int main(int ac, char **av)
{
	t_data *data;

	data = malloc(sizeof(t_data));
	if (!data)
		exit(EXIT_FAILURE);
	if (ac != 2)
		exit(EXIT_SUCCESS);
	parsing(av[1], data);

}