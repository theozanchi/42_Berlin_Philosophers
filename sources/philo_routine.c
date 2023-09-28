/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzanchi <tzanchi@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:38:49 by tzanchi           #+#    #+#             */
/*   Updated: 2023/09/28 20:08:19 by tzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*The philosophers takes its first always starting by the fork with the smallest
ID to avoid data races. If the philosopher is alone, he unlocks his forks and
the function returns*/
void	takes_forks(t_philo *philo)
{
	int	first_fork;
	int	second_fork;

	first_fork = ft_min(philo->left_fork_id, philo->right_fork_id) - 1;
	second_fork = ft_max(philo->left_fork_id, philo->right_fork_id) - 1;
	pthread_mutex_lock(&philo->data->forks[first_fork]);
	display_log(FORK_LOG, philo);
	if (philo->data->nbr_of_philo == 1)
	{
		pthread_mutex_unlock(&philo->data->forks[first_fork]);
		return ;
	}
	pthread_mutex_lock(&philo->data->forks[second_fork]);
	display_log(FORK_LOG, philo);
}

/*If philosopher's id is even, philosopher starts by taking its left fork then
right fork, if philosopher's id is odd, philosopher starts by taking its right
fork then left fork. Then eats before releasing the forks.
philo->last_meal and philo->nbr_of_meals are updated. If philosopher had all
its meals, data->nbr_of_full_philo is updated
The edge case of just one philosopher is taken into account to break the
routine (return after taking the first fork)*/
void	is_eating(t_philo	*philo)
{
	takes_forks(philo);
	if (philo->data->nbr_of_philo == 1)
		return ;
	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->last_meal = get_time();
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

/*Philosopher starts thinking for a minimal duration of 2 millisecond*/
void	is_thinking(t_philo *philo)
{
	display_log(THINK_LOG, philo);
	usleep(2000);
}

/*Each philosopher starts by eating, before sleeping and then thinking
The edge case of just one philosopher is taken into account to break the
routine (return after trying to eat)*/
void	*routine(void *void_philo)
{
	t_philo	*philo;
	t_data	*data;
	int		end_of_simulation_local;

	philo = (t_philo *)void_philo;
	data = philo->data;
	wait_for_start(data);
	if (philo->id % 2 == 0)
		is_thinking(philo);
	while (1)
	{
		pthread_mutex_lock(&data->end_of_simulation_mutex);
		end_of_simulation_local = data->end_of_simulation;
		pthread_mutex_unlock(&data->end_of_simulation_mutex);
		if (end_of_simulation_local)
			break ;
		is_eating(philo);
		if (data->nbr_of_philo == 1)
			break ;
		is_sleeping(philo);
		is_thinking(philo);
	}
	return (NULL);
}
