/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzanchi <tzanchi@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:01:18 by tzanchi           #+#    #+#             */
/*   Updated: 2023/09/15 17:38:13 by tzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*Initializes the data with the arguments of argv:
• data->number_of_philosophers: the number of philosophers and forks
• data->time_to_die: if a philosopher does not eat time_to_die ms since the
beginning of their last meal or the beginning of the simulation, they die.
• data->time_to_eat: the time it takes a philosopher to eat in ms
• data->time_to_sleep: the time a philosopher sleeps after a meal
• data->nbr_of_meals: the number of meals a philosopher takes before the
simulation ends
• data->flag_all_have_eaten: initialized at 0, set to 1 when all philosophers had
nbr_of_meals meals*/
int	init_data(t_data *data, char **argv)
{
	data->number_of_philosophers = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		data->nbr_of_meals = ft_atoi(argv[5]);
	else
		data->nbr_of_meals = -1;
	data->flag_all_have_eaten = 0;
	data->philo = new_philosopher(1);
	if (!data->philo)
		return (1);
	return (0);
}

t_philo	*new_philosopher(size_t philo_id)
{
	t_philo	*new;

	new = malloc(sizeof(t_philo));
	if (!new)
	{
		printf(MALLOC_FAIL);
		return (NULL);
	}
	new->id = philo_id;
	new->left_fork_id = philo_id;
	new->right_fork_id = philo_id + 1;
	new->last_meal = malloc(sizeof(struct timeval));
	if (!new->last_meal)
	{
		printf(MALLOC_FAIL);
		return (NULL);
	}
	gettimeofday(new->last_meal, NULL);
	// if (pthread_create(&new->thread, NULL, routine, NULL) != 0)
	// {
	// 	printf(THREAD_CREATE_FAIL);
	// 	return (NULL);
	// }
	new->number_of_meals = 0;
	return (new);
}

int	init_philosophers(t_data *data)
{
	t_philo	*ptr;
	size_t	philo_id;

	ptr = data->philo;
	philo_id = 2;
	while (philo_id <= data->number_of_philosophers)
	{
		ptr->next = new_philosopher(philo_id++);
		if (!ptr->next)
			return (1);
		ptr = ptr->next;
	}
	ptr->right_fork_id = 1;
	ptr->next = data->philo;
	return (0);
}
