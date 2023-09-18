/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzanchi <tzanchi@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 17:45:38 by tzanchi           #+#    #+#             */
/*   Updated: 2023/09/18 12:26:51 by tzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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

/*Loops through all philosophers contained in data->philo and frees allocated
memory*/
int	free_data(t_data *data, int exit_code)
{
	t_philo	*first;
	t_philo	*current;
	t_philo	*next;

	current = data->philo;
	if (!current)
		return ;
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
