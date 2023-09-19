/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzanchi <tzanchi@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:13:50 by tzanchi           #+#    #+#             */
/*   Updated: 2023/09/19 19:29:26 by tzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGES_H
# define MESSAGES_H

/*errors*/
# define WRG_ARG_NR "The program expects 4 or 5 arguments: \
number_of_philosophers, time_to_die, time_to_eat, time_to_sleep and \
number_of_times_each_philosopher_must_eat (optional)\n"
# define INVALID_ARG "%s is an invalid argument: must be a positive int"
# define MALLOC_FAIL "Memory allocation failure\n"
# define THREAD_CREATION_FAIL "Failed to join thread for philosopher %zu\n"
# define THREAD_JOIN_FAIL "Failed to join thread for philosopher %zu\n"
# define MUTEX_FAIL "Mutex creation failure\n"

/*logs*/
# define FORK_LOG "[%d] Philo %d has taken a fork\n"
# define EAT_LOG "[%d] Philo %d is eating\n"
# define SLEEP_LOG "[%d] Philo %d is sleeping\n"
# define THINK_LOG "[%d] Philo %d is thinking\n"
# define DEATH_LOG "[%d] \033[1;31mPhilo %d died\033[0m\n"

#endif
