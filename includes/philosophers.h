/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzanchi <tzanchi@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:11:52 by tzanchi           #+#    #+#             */
/*   Updated: 2023/09/19 16:51:54 by tzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

/*libraries*/
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include <time.h>
# include <pthread.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>
# include <unistd.h>

/*header_files*/
# include "messages.h"

/*data_model*/
typedef struct s_philo
{
	size_t			id;
	int				left_fork_id;
	int				right_fork_id;
	struct timeval	*last_meal;
	size_t			nbr_of_meals;
	int				philo_is_full;
	pthread_t		thread;
	struct s_data	*data;
	struct s_philo	*next;
}	t_philo;

typedef struct s_data
{
	size_t			nbr_of_philo;
	clock_t			time_to_die;
	clock_t			time_to_eat;
	clock_t			time_to_sleep;
	__ssize_t		nbr_of_meals;
	size_t			nbr_of_full_philo;
	pthread_mutex_t	nbr_of_full_philo_mutex;
	t_philo			*philo;
	pthread_mutex_t	*forks;
	struct timeval	*current_time;
}	t_data;

/*_utils.c*/
int		ft_atoi(const char *nptr);
int		ft_isspace(int c);
int		ft_isdigit(int c);
int		ft_isnumeric(char *str);
void	display_log(char *log, t_philo *philo);

/*free.c*/
void	destroy_forks(t_data *data);
void	free_philosopher(t_philo *philosopher);
int		free_data(t_data *data, int exit_code);

/*init.c*/
t_philo	*new_philosopher(size_t philo_id, t_data *data);
int		init_philosophers(t_data *data);
int		init_forks(t_data *data);
int		init_data(t_data *data, char **argv);
int		launch_threads(t_data *data);

/*main.c*/
int		main(int argc, char **argv);

/*routine.c*/
void	is_eating(t_philo	*philo);
void	is_sleeping(t_philo *philo);
void	is_thinking(t_philo *philo);
int		philo_is_dead(t_philo *philo);
void	*routine(void *void_philo);

#endif
