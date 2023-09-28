/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzanchi <tzanchi@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:01:18 by tzanchi           #+#    #+#             */
/*   Updated: 2023/09/28 18:50:50 by tzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*Allocates memory and initializes a new t_philo object with its forks IDs and
the current time for its last meal time (corresponding to the beginning of the
simulation)*/
t_philo	*new_philosopher(size_t philo_id, t_data *data)
{
	t_philo	*new;

	new = malloc(sizeof(t_philo));
	if (!new)
		return (NULL);
	new->id = philo_id;
	new->left_fork_id = philo_id;
	new->right_fork_id = philo_id + 1;
	new->last_meal = malloc(sizeof(struct timeval));
	if (!new->last_meal)
	{
		printf(MALLOC_FAIL);
		return (NULL);
	}
	if (pthread_mutex_init(&new->last_meal_mutex, NULL))
	{
		printf(MUTEX_FAIL);
		return (NULL);
	}
	new->nbr_of_meals = 0;
	new->philo_is_full = 0;
	new->data = data;
	gettimeofday(new->last_meal, NULL);
	return (new);
}

/*Initializes the list of all philosophers as a circular list. Philosophers 1 
and data->number_of_philosophers are seated one to each other and share their
fork (left_fork_id of philosopher 1 is equal to right_for_id of philosopher
data->number_of_philosophers)
If the creation of one philosopher fails, function returns EXIT_FAILURE*/
int	init_philosophers(t_data *data)
{
	t_philo	*ptr;
	size_t	philo_id;

	data->philo = new_philosopher(1, data);
	if (!data->philo)
		return (EXIT_FAILURE);
	ptr = data->philo;
	philo_id = 2;
	while (philo_id <= data->nbr_of_philo)
	{
		ptr->next = new_philosopher(philo_id++, data);
		if (!ptr->next)
			return (EXIT_FAILURE);
		ptr = ptr->next;
	}
	ptr->right_fork_id = 1;
	ptr->next = data->philo;
	return (EXIT_SUCCESS);
}

/*Initializes of mutex for each fork. Returns EXIT_FAILURE in case the memory
allocation or the mutex creation fails for any of the forks*/
int	init_forks(t_data *data)
{
	size_t	i;

	data->forks = malloc(data->nbr_of_philo * sizeof(pthread_mutex_t));
	if (!data->forks)
	{
		printf(MALLOC_FAIL);
		return (EXIT_FAILURE);
	}
	i = 0;
	while (i < data->nbr_of_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
		{
			printf(MUTEX_FAIL);
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

/*Initializes the data with the arguments of argv and the first philosophers
then calls init_philosophers to initializes all philosophers
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
	data->nbr_of_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		data->nbr_of_meals = ft_atoi(argv[5]);
	else
		data->nbr_of_meals = 0;
	data->end_of_simulation = 0;
	data->start_of_simulation = 0;
	data->nbr_of_full_philo = 0;
	if (init_philosophers(data))
		return (free_data(data, EXIT_FAILURE));
	if (init_forks(data))
		return (free_data(data, EXIT_FAILURE));
	if (pthread_mutex_init(&data->nbr_of_full_philo_mutex, NULL)
		|| pthread_mutex_init(&data->display_mutex, NULL)
		|| pthread_mutex_init(&data->end_of_simulation_mutex, NULL)
		|| pthread_mutex_init(&data->start_of_simulation_mutex, NULL))
		return (free_data(data, EXIT_FAILURE));
	data->current_time = malloc(sizeof(struct timeval));
	if (!data->current_time)
		return (free_data(data, EXIT_FAILURE));
	return (EXIT_SUCCESS);
}

/*Loops through all the philosophers to create a thread for each of them. If
one thread fails, function returns EXIT_FAILURE*/
int	launch_threads(t_data *data)
{
	size_t	i;
	t_philo	*ptr;

	i = data->nbr_of_philo;
	ptr = data->philo;
	while (i--)
	{
		if (pthread_create(&ptr->routine, NULL, routine, (void *)ptr) != 0)
		{
			printf(THREAD_CREATION_FAIL, ptr->id);
			return (EXIT_FAILURE);
		}
		ptr = ptr->next;
	}
	pthread_mutex_lock(&data->display_mutex);
	gettimeofday(data->start_time, NULL);
	pthread_mutex_unlock(&data->display_mutex);
	pthread_mutex_lock(&data->start_of_simulation_mutex);
	data->start_of_simulation = 1;
	pthread_mutex_unlock(&data->start_of_simulation_mutex);
	return (EXIT_SUCCESS);
}
