/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzanchi <tzanchi@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 17:45:38 by tzanchi           #+#    #+#             */
/*   Updated: 2023/09/19 15:31:50 by tzanchi          ###   ########.fr       */
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

/*Frees all memory allocated for one philosopher*/
void	free_philosopher(t_philo *philosopher)
{
	if (!philosopher)
		return ;
	if (philosopher->last_meal)
		free(philosopher->last_meal);
	free(philosopher);
	philosopher = NULL;
}

/*Frees the current_time structure inside t_data *data*/
void	free_timestamp(t_data *data)
{
	if (!data->current_time)
		return ;
	free(data->current_time);
	data->current_time = NULL;
}

/*Loops through all philosophers contained in data->philo and frees allocated
memory*/
int	free_data(t_data *data, int exit_code)
{
	t_philo	*first;
	t_philo	*current;
	t_philo	*next;

	destroy_forks(data);
	free_timestamp(data);
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
