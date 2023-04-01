/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-brig <nel-brig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 03:25:55 by namine            #+#    #+#             */
/*   Updated: 2023/04/01 03:29:04 by nel-brig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing/parsing.h"

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac != 2)
		exit(EXIT_FAILURE);
	data = malloc(sizeof(t_data));
	if (!data)
		exit (EXIT_FAILURE);
	init_identifier(data);
	parsing(av[1], data);
	execution(data);
	return (0);
}
