/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzanchi <tzanchi@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:13:16 by tzanchi           #+#    #+#             */
/*   Updated: 2023/09/21 12:27:20 by tzanchi          ###   ########.fr       */
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

/*Displays the log passed as a string pointer for the philosopher 'philo'*/
int	display_log(char *log, t_philo *philo)
{
	clock_t	time;

	pthread_mutex_lock(&philo->data->display_mutex);
	gettimeofday(philo->data->current_time, NULL);
	time = (philo->data->current_time->tv_sec
			- philo->data->start_time->tv_sec) * 1000
		+ (philo->data->current_time->tv_usec
			- philo->data->start_time->tv_usec) / 1000;
	if (ft_strcmp(log, ALL_FULL_LOG) == 0)
		printf(log, time, philo->data->nbr_of_meals);
	else
		printf(log, time, philo->id);
	pthread_mutex_unlock(&philo->data->display_mutex);
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	data;

	data.start_time = malloc(sizeof(struct timeval));
	if (!data.start_time)
	{
		printf(MALLOC_FAIL);
		return (EXIT_FAILURE);
	}
	gettimeofday(data.start_time, NULL);
	if (check_arguments(argc, argv))
		return (EXIT_FAILURE);
	if (init_data(&data, argv))
		return (free_data(&data, EXIT_FAILURE));
	if (launch_threads(&data))
		return (free_data(&data, EXIT_FAILURE));
	pthread_create(&data.monitor_routine, NULL, monitor_routine, (void *)&data);
	pthread_join(data.monitor_routine, NULL);
	return (free_data(&data, EXIT_SUCCESS));
}
