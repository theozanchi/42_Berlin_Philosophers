/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzanchi <tzanchi@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:38:49 by tzanchi           #+#    #+#             */
/*   Updated: 2023/09/19 16:36:25 by tzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	is_eating(t_philo	*philo)
{
	if (philo->philo_is_full)
		return ;
	pthread_mutex_lock(&philo->data->forks[philo->left_fork_id - 1]);
	display_log(FORK_LOG, philo);
	pthread_mutex_lock(&philo->data->forks[philo->right_fork_id - 1]);
	display_log(FORK_LOG, philo);
	display_log(EAT_LOG, philo);
	usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork_id - 1]);
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork_id - 1]);
	philo->nbr_of_meals++;
	if (philo->data->nbr_of_meals > 0
		&& (__ssize_t)philo->nbr_of_meals == philo->data->nbr_of_meals)
	{
		philo->philo_is_full = 1;
		philo->data->nbr_of_full_philo++;
	}
}

void	is_sleeping(t_philo *philo)
{
	display_log(SLEEP_LOG, philo);
	usleep(philo->data->time_to_sleep);
}

void	is_thinking(t_philo *philo)
{
	display_log(THINK_LOG, philo);
}

int	philo_is_dead(t_philo *philo)
{
	clock_t	time_since_last_meal;

	gettimeofday(philo->data->current_time, NULL);
	time_since_last_meal = philo->data->current_time->tv_usec
		- philo->last_meal->tv_usec;
	if (time_since_last_meal > philo->data->time_to_die)
	{
		display_log(DEATH_LOG, philo);
		return (1);
	}
	return (0);
}

void	*routine(void *void_philo)
{
	t_philo			*philo;

	philo = (t_philo *)void_philo;
	while (1)
	{
		is_eating(philo);
		is_sleeping(philo);
		is_thinking(philo);
		if (philo_is_dead(philo)
			|| (philo->data->nbr_of_meals > 0
				&& philo->data->nbr_of_full_philo == philo->data->nbr_of_philo))
			break ;
	}
	return (NULL);
}
