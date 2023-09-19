/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _utils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzanchi <tzanchi@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:55:32 by tzanchi           #+#    #+#             */
/*   Updated: 2023/09/19 19:46:07 by tzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*ft_atoi converts the initial portion of the string pointed to by nptr to int,
ignoring initial spaces. If the value is below INT_MIN it returns INT_MIN, if 
teh value is above INT_MAX it returns INT_MAX*/
int	ft_atoi(const char *nptr)
{
	int		sign;
	int		result;

	sign = 1;
	result = 0;
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr++ == '-')
			sign *= -1;
	}
	while (ft_isdigit(*nptr))
	{
		if (result > INT_MAX / 10
			|| (result == INT_MAX / 10 && *nptr - '0' > INT_MAX % 10))
		{
			if (sign == 1)
				return (INT_MAX);
			else
				return (INT_MIN);
		}
		result = result * 10 + *nptr++ - '0';
	}
	return (result * sign);
}

/*ft_isspace returns 1 if character c is a space. Space includes space,
form-feed\f, new line \n, carriage return \r, horizontal tab \t and  vertical
tab\v*/
int	ft_isspace(int c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	else
		return (0);
}

/*ft_isalnum returns 1 if character c is a digit*/
int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

/*Returns 1 if the string 'str' is a number, 0 if not*/
int	ft_isnumeric(char *str)
{
	if (*str == '+' || *str == '-')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

/*Displays the log passed as a string pointer for the philosopher 'philo'*/
void	display_log(char *log, t_philo *philo)
{
	unsigned long	total_milliseconds;
	unsigned long	seconds;
	unsigned long	milliseconds;

	gettimeofday(philo->data->current_time, NULL);
	total_milliseconds = philo->data->current_time->tv_sec * 1000
		+ philo->data->current_time->tv_usec / 1000;
	seconds = total_milliseconds / 1000;
	milliseconds = total_milliseconds % 1000;
	printf(log, seconds, milliseconds, philo->id);
}
