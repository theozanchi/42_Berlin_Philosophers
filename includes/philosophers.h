/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzanchi <tzanchi@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:11:52 by tzanchi           #+#    #+#             */
/*   Updated: 2023/09/14 16:14:58 by tzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

/*libraries*/
# include <stdio.h>
# include <limits.h>
# include <time.h>
# include <pthread.h>

/*header_files*/
# include "messages.h"

/*data_model*/
typedef struct s_data
{
	size_t		number_of_philosophers;
	clock_t		time_to_die;
	clock_t		time_to_eat;
	clock_t		time_to_sleep;
	__ssize_t	nbr_of_meals;
	int			flag_all_have_eaten;
}	t_data;

typedef struct s_philosopher
{
	size_t		id;
	int			left_fork_id;
	int			right_fork_id;
	clock_t		last_meal;
	size_t		number_of_meals;
	pthread_t	thread_id;
}	t_philosopher;


/*_utils.c*/
int		ft_atoi(const char *nptr);
int		ft_isspace(int c);
int		ft_isdigit(int c);
int		ft_isnumeric(char *str);

/*init.c*/
void	init_data(t_data *data, char **argv);

/*main.c*/
int		main(int argc, char **argv);

#endif
