/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzanchi <tzanchi@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:38:49 by tzanchi           #+#    #+#             */
/*   Updated: 2023/09/20 16:04:50 by tzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	takes_forks(t_philo *philo, int first_fork, int second_fork)
{
	pthread_mutex_lock(&philo->data->forks[first_fork - 1]);
	display_log(FORK_LOG, philo);
	pthread_mutex_lock(&philo->data->forks[second_fork - 1]);
	display_log(FORK_LOG, philo);
}

void	is_eating(t_philo	*philo)
{
	if (philo->id % 2 == 0)
		takes_forks(philo, philo->left_fork_id, philo->right_fork_id);
	else
		takes_forks(philo, philo->right_fork_id, philo->left_fork_id);
	display_log(EAT_LOG, philo);
	usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork_id - 1]);
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork_id - 1]);
	philo->nbr_of_meals++;
	if (philo->data->nbr_of_meals > 0
		&& (__ssize_t)philo->nbr_of_meals == philo->data->nbr_of_meals)
	{
		pthread_mutex_lock(&philo->data->nbr_of_full_philo_mutex);
		philo->philo_is_full = 1;
		philo->data->nbr_of_full_philo++;
		pthread_mutex_unlock(&philo->data->nbr_of_full_philo_mutex);
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

void	*routine(void *void_philo)
{
	t_philo			*philo;

	philo = (t_philo *)void_philo;
	while (1)
	{
		if (philo->data->nbr_of_meals > 0
			&& philo->data->nbr_of_full_philo == philo->data->nbr_of_philo)
			break ;
		is_eating(philo);
		is_sleeping(philo);
		is_thinking(philo);
	}
	return (NULL);
}
