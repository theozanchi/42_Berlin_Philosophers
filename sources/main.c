/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzanchi <tzanchi@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:13:16 by tzanchi           #+#    #+#             */
/*   Updated: 2023/09/14 18:10:03 by tzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*Checks that the number of arguments is 4 or 5 (excluding program name) and
checks that every argument is a positive integer
Returns 1 if arguments are valid, -1 if they're not*/
int	check_arguments(int argc, char **argv)
{
	int	i;

	if (argc != 5 && argc != 6)
	{
		printf(WRG_ARG_NR);
		return (-1);
	}
	i = 1;
	while (argv[i])
	{
		if (!ft_isnumeric(argv[i]) || ft_atoi(argv[i]) < 0)
		{
			printf(INVALID_ARG, argv[i]);
			return (-1);
		}
		i++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (check_arguments(argc, argv) == -1)
		return (1);
	init_data(&data, argv);
}
