/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _utils_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzanchi <tzanchi@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 19:12:13 by tzanchi           #+#    #+#             */
/*   Updated: 2023/09/28 19:32:20 by tzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*Returns the current time as a clock_t value type*/
clock_t	get_time(void)
{
	struct timeval	time;
	clock_t			output;

	gettimeofday(&time, NULL);
	output = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (output);
}

/*Displays the log passed as a string pointer for the philosopher 'philo'*/
int	display_log(char *log, t_philo *philo)
{
	clock_t	timestamp;
	int		end_of_simulation_local;

	pthread_mutex_lock(&philo->data->end_of_simulation_mutex);
	end_of_simulation_local = philo->data->end_of_simulation;
	pthread_mutex_unlock(&philo->data->end_of_simulation_mutex);
	if (end_of_simulation_local && ft_strcmp(log, ALL_FULL_LOG)
		&& ft_strcmp(log, DEATH_LOG))
		return (0);
	pthread_mutex_lock(&philo->data->display_mutex);
	timestamp = get_time() - philo->data->start_time;
	if (ft_strcmp(log, ALL_FULL_LOG) == 0)
		printf(log, timestamp, philo->data->nbr_of_philo,
			philo->data->nbr_of_meals);
	else
		printf(log, timestamp, philo->id);
	pthread_mutex_unlock(&philo->data->display_mutex);
	return (1);
}

/*The function loops indefinitely until the starting flag of the simulation
is one to start the simulation*/
void	wait_for_start(t_data *data)
{
	while (1)
	{
		pthread_mutex_lock(&data->start_of_simulation_mutex);
		if (data->start_of_simulation)
			break ;
		pthread_mutex_unlock(&data->start_of_simulation_mutex);
		usleep(50);
	}
	pthread_mutex_unlock(&data->start_of_simulation_mutex);
}
