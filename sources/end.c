/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzanchi <tzanchi@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 17:45:38 by tzanchi           #+#    #+#             */
/*   Updated: 2023/09/21 18:22:54 by tzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*Destroys all the mutex initialized for the forks and then frees the forks
pointer*/
void	destroy_forks(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->nbr_of_philo)
		pthread_mutex_destroy(&data->forks[i++]);
	free(data->forks);
}

/*Loops through all the philosophers to join the thread created for each of
them. If one joint fails, function returns EXIT_FAILURE*/
int	detach_philo_threads(t_data *data)
{
	t_philo	*ptr;
	size_t	i;

	i = data->nbr_of_philo;
	ptr = data->philo;
	while (i--)
	{
		if (pthread_detach(ptr->routine) != 0)
		{
			printf(THREAD_DETACH_FAIL, ptr->id);
			return (EXIT_FAILURE);
		}
		ptr = ptr->next;
	}
	return (EXIT_SUCCESS);
}

/*Frees all memory allocated for one philosopher*/
void	free_philosopher(t_philo *philosopher)
{
	if (!philosopher)
		return ;
	if (philosopher->last_meal)
		free(philosopher->last_meal);
	pthread_mutex_destroy(&philosopher->last_meal_mutex);
	free(philosopher);
	philosopher = NULL;
}

/*Frees the current_time structure inside t_data *data*/
void	free_timestamps(t_data *data)
{
	if (data->current_time)
		free(data->current_time);
	data->current_time = NULL;
	if (data->start_time)
		free(data->start_time);
	data->start_time = NULL;
}

/*Loops through all philosophers contained in data->philo and frees allocated
memory*/
int	free_data(t_data *data, int exit_code)
{
	t_philo	*first;
	t_philo	*current;
	t_philo	*next;

	destroy_forks(data);
	pthread_mutex_destroy(&data->nbr_of_full_philo_mutex);
	pthread_mutex_destroy(&data->display_mutex);
	free_timestamps(data);
	current = data->philo;
	if (!current)
		return (exit_code);
	first = current;
	next = current->next;
	while (current && next != first)
	{
		free_philosopher(current);
		current = next;
		if (current)
			next = current->next;
	}
	if (current)
		free_philosopher(current);
	return (exit_code);
}
