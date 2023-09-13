/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzanchi <tzanchi@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:11:52 by tzanchi           #+#    #+#             */
/*   Updated: 2023/09/13 16:56:47 by tzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

/*libraries*/
# include <stdio.h>
# include <limits.h>

/*header_files*/
# include "messages.h"

/*data_model*/
typedef struct s_data
{
	size_t	number_of_philosophers;
	size_t	time_to_die;
	size_t	time_to_eat;
	size_t	time_to_sleep;
}	t_data;

/*_utils.c*/
int	ft_atoi(const char *nptr);

/*main.c*/
int	main(int argc, char **argv);

#endif
