/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzanchi <tzanchi@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:01:18 by tzanchi           #+#    #+#             */
/*   Updated: 2023/09/14 18:25:12 by tzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_philosophers(t_data *data)
{
	
}

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
void	init_data(t_data *data, char **argv)
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
}
