/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzanchi <tzanchi@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:13:16 by tzanchi           #+#    #+#             */
/*   Updated: 2023/09/25 16:54:37 by tzanchi          ###   ########.fr       */
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
	int		end_of_simulation_local;

	pthread_mutex_lock(&philo->data->end_of_simulation_mutex);
	end_of_simulation_local = philo->data->end_of_simulation;
	pthread_mutex_unlock(&philo->data->end_of_simulation_mutex);
	if (end_of_simulation_local && ft_strcmp(log, ALL_FULL_LOG)
		&& ft_strcmp(log, DEATH_LOG))
		return (0);
	pthread_mutex_lock(&philo->data->display_mutex);
	gettimeofday(philo->data->current_time, NULL);
	time = (philo->data->current_time->tv_sec
			- philo->data->start_time->tv_sec) * 1000
		+ (philo->data->current_time->tv_usec
			- philo->data->start_time->tv_usec) / 1000;
	if (ft_strcmp(log, ALL_FULL_LOG) == 0)
		printf(log, time, philo->data->nbr_of_philo, philo->data->nbr_of_meals);
	else
		printf(log, time, philo->id);
	pthread_mutex_unlock(&philo->data->display_mutex);
	return (1);
}

/*• Initializes 'start_time' with the time when the process started
• Checks that arguments are valid
• Loads the arguments contained in argv in the structure s_data
• Launches one thread per philosopher for their eat-sleep-think routine
• Launches a monitor routine to check if the simulation should stop (by the
death of a philosopher or because they are all full)
• Properly frees the resources and returns EXIT_SUCCESS*/
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
	monitor_routine(&data);
	join_philo_threads(&data);
	return (free_data(&data, EXIT_SUCCESS));
}
