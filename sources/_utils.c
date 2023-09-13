/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _utils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzanchi <tzanchi@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:55:32 by tzanchi           #+#    #+#             */
/*   Updated: 2023/09/13 16:56:15 by tzanchi          ###   ########.fr       */
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
