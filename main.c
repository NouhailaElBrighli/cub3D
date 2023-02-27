#include "parsing/parsing.h"

int main(int ac, char **av)
{
	t_data *data;

	if (ac != 2)
		exit(EXIT_SUCCESS);
	data = malloc(sizeof(t_data));
	if (!data)
		exit(EXIT_FAILURE);
	init_identifier(data);
	parsing(av[1], data);
	execution(data);
	return (0);
}
