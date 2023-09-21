/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzanchi <tzanchi@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 12:13:56 by tzanchi           #+#    #+#             */
/*   Updated: 2023/09/21 12:20:59 by tzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	philo_is_dead(t_philo *philo)
{
	clock_t	time_since_last_meal;

	gettimeofday(philo->data->current_time, NULL);
	time_since_last_meal = (philo->data->current_time->tv_sec
			- philo->last_meal->tv_sec) * 1000
		+ (philo->data->current_time->tv_usec - philo->last_meal->tv_usec)
		/ 1000;
	if (time_since_last_meal > philo->data->time_to_die)
		return (1);
	return (0);
}

int	all_full_philo(t_data *data)
{
	pthread_mutex_lock(&data->nbr_of_full_philo_mutex);
	if (data->nbr_of_meals && data->nbr_of_full_philo == data->nbr_of_philo)
	{
		pthread_mutex_unlock(&data->nbr_of_full_philo_mutex);
		return (1);
	}
	pthread_mutex_unlock(&data->nbr_of_full_philo_mutex);
	return (0);
}

void	*monitor_routine(void *void_data)
{
	t_data	*data;
	t_philo	*philo;

	data = (t_data *)void_data;
	philo = data->philo;
	while (1)
	{
		if (all_full_philo(data))
		{
			display_log(ALL_FULL_LOG, philo);
			detach_philo_threads(data);
			break ;
		}
		if (philo_is_dead(philo))
		{
			display_log(DEATH_LOG, philo);
			detach_philo_threads(data);
			break ;
		}
		philo = philo->next;
		usleep(100);
	}
	return (NULL);
}
