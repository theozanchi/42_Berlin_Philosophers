/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzanchi <tzanchi@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:38:49 by tzanchi           #+#    #+#             */
/*   Updated: 2023/09/22 10:43:57 by tzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*The philosophers first takes the fork with id 'first_fork' then the fork with
id 'second_fork'. Mutexes are used to prevent a philosopher to steal forks*/
void	takes_forks(t_philo *philo, int first_fork, int second_fork)
{
	pthread_mutex_lock(&philo->data->forks[first_fork - 1]);
	display_log(FORK_LOG, philo);
	pthread_mutex_lock(&philo->data->forks[second_fork - 1]);
	display_log(FORK_LOG, philo);
}

/*If philosopher's id is even, philosopher starts by taking its left fork then
right fork, if philosopher's id is odd, philosopher starts by taking its right
fork then left fork. Then eats before releasing the forks.
philo->last_meal and philo->nbr_of_meals are updated. If philosopher had all
its meals, data->nbr_of_full_philo is updated*/
void	is_eating(t_philo	*philo)
{
	if (philo->id % 2 == 0)
		takes_forks(philo, philo->left_fork_id, philo->right_fork_id);
	else
		takes_forks(philo, philo->right_fork_id, philo->left_fork_id);
	pthread_mutex_lock(&philo->last_meal_mutex);
	gettimeofday(philo->last_meal, NULL);
	display_log(EAT_LOG, philo);
	pthread_mutex_unlock(&philo->last_meal_mutex);
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork_id - 1]);
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork_id - 1]);
	philo->nbr_of_meals++;
	if (philo->data->nbr_of_meals
		&& philo->nbr_of_meals == philo->data->nbr_of_meals
		&& philo->philo_is_full != 1)
	{
		pthread_mutex_lock(&philo->data->nbr_of_full_philo_mutex);
		philo->philo_is_full = 1;
		philo->data->nbr_of_full_philo++;
		pthread_mutex_unlock(&philo->data->nbr_of_full_philo_mutex);
	}
}

/*Puts the philosopher asleep for data->time_to_sleep milliseconds*/
void	is_sleeping(t_philo *philo)
{
	display_log(SLEEP_LOG, philo);
	usleep(philo->data->time_to_sleep * 1000);
}

/*Philosopher starts thinking for a minimal duration of 1 millisecond*/
void	is_thinking(t_philo *philo)
{
	display_log(THINK_LOG, philo);
	usleep(1000);
}

/*Each philosopher starts by eating, before sleeping and then thinking*/
void	*routine(void *void_philo)
{
	t_philo			*philo;

	philo = (t_philo *)void_philo;
	while (1)
	{
		pthread_mutex_lock(&philo->data->end_of_simulation_mutex);
		if (philo->data->end_of_simulation)
		{
			pthread_mutex_unlock(&philo->data->end_of_simulation_mutex);
			break ;
		}
		else
		{
			pthread_mutex_unlock(&philo->data->end_of_simulation_mutex);
			is_eating(philo);
			is_sleeping(philo);
			is_thinking(philo);
		}
	}
	return (NULL);
}
