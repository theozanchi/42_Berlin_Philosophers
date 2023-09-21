/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzanchi <tzanchi@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 12:13:56 by tzanchi           #+#    #+#             */
/*   Updated: 2023/09/21 19:55:45 by tzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*Compares the time since a philosopher's last meal beginning  and the current
time. If the difference is bigger than data->time_to_die, the philosopher is
dead and the function returns 1*/
int	philo_is_dead(t_philo *philo)
{
	clock_t	time_since_last_meal;

	pthread_mutex_lock(&philo->last_meal_mutex);
	gettimeofday(philo->data->current_time, NULL);
	time_since_last_meal = (philo->data->current_time->tv_sec
			- philo->last_meal->tv_sec) * 1000
		+ (philo->data->current_time->tv_usec - philo->last_meal->tv_usec)
		/ 1000;
	pthread_mutex_unlock(&philo->last_meal_mutex);
	if (time_since_last_meal > philo->data->time_to_die)
		return (1);
	return (0);
}

/*Checks if the nu,ber of full philosophers in the structure s_data is equal
to the number of philosophers in the simulation.
Returns 1 if all philosophers are full, 0 if at least one of them is not*/
int	all_full_philo(t_data *data)
{
	pthread_mutex_lock(&data->nbr_of_full_philo_mutex);
	if (data->nbr_of_full_philo == data->nbr_of_philo)
	{
		pthread_mutex_unlock(&data->nbr_of_full_philo_mutex);
		return (1);
	}
	pthread_mutex_unlock(&data->nbr_of_full_philo_mutex);
	return (0);
}

/*Checks every 50 microseconds if all philosophers have eaten or if a
philosopher dies. The routine terminates and returns NULL if any of this
happens*/
void	monitor_routine(t_data *data)
{
	t_philo	*philo;

	philo = data->philo;
	while (1)
	{
		if (philo_is_dead(philo))
		{
			display_log(DEATH_LOG, philo);
			detach_philo_threads(data);
			break ;
		}
		if (data->nbr_of_meals)
		{
			if (all_full_philo(data))
			{
				display_log(ALL_FULL_LOG, philo);
				detach_philo_threads(data);
				break ;
			}
		}
		philo = philo->next;
		usleep(50);
	}
}
