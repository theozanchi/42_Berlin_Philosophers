/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzanchi <tzanchi@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:13:16 by tzanchi           #+#    #+#             */
/*   Updated: 2023/09/18 12:34:00 by tzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*Checks that the number of arguments is 4 or 5 (excluding program name) and
checks that every argument is a positive integer
Returns 0 if arguments are valid, a positive int if they're not*/
int	check_arguments(int argc, char **argv)
{
	int	i;

	if (argc != 5 && argc != 6)
		return (printf(WRG_ARG_NR));
	i = 1;
	while (argv[i])
	{
		if (!ft_isnumeric(argv[i]) || ft_atoi(argv[i]) <= 0)
			return (printf(INVALID_ARG, argv[i]));
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (check_arguments(argc, argv))
		return (EXIT_FAILURE);
	if (init_data(&data, argv))
		return (free_data(&data, EXIT_FAILURE));
	return (free_data(&data, EXIT_SUCCESS));
}
