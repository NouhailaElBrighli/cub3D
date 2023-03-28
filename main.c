/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-brig <nel-brig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 21:11:21 by nel-brig          #+#    #+#             */
/*   Updated: 2023/03/28 21:11:23 by nel-brig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	system("leaks cub3D");
	// execution(data);
	return (0);
}
