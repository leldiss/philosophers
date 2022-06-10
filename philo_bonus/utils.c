/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leldiss <leldiss@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 14:28:05 by leldiss           #+#    #+#             */
/*   Updated: 2022/06/10 15:41:18 by leldiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_error_message(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	write(1, "Error > ", 8);
	write(1, str, len);
	write(1, "\n", 1);
}

void	error_message(int error, t_info *info)
{
	if (error == -1)
		print_error_message("Wrong arguments");
	else if (error == -2)
		print_error_message("Couldn't create the thread");
	else if (error == -3)
		print_error_message("Couldn't join the thread");
	else if (error == -4)
		print_error_message("Initializing sem error");
	else if (error == -5)
		print_error_message("Negative argument");
	else if (error == -6)
		print_error_message("Argument is more than MAX_INT");
	else if (error == -7)
		print_error_message("Only numeral arguments is allowed");
	free_all(info);
	exit(error);
}

long long	get_timestamp(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	is_philo_dead(t_philo *philo)
{
	struct timeval	time;
	int				diff;

	gettimeofday(&time, NULL);
	diff = (time.tv_sec * 1000) + (time.tv_usec / 1000) - philo->time_last_meal;
	if (philo->conditions->time_to_die <= diff)
	{
		philo->alive = 0;
		return (1);
	}
	return (0);
}

int	ft_atoi(const char *str, t_info *info)
{
	unsigned int	result;

	result = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			error_message(-5, info);
		str++;
	}
	while (*str != '\0')
	{
		if (*str < '0' || *str > '9')
			error_message(-7, info);
		if (*str >= '0' && *str <= '9')
		{
			result = (result * 10) + (*str % 48);
		}
		str++;
	}
	if (result > MAX_INT)
		error_message(-6, info);
	return (result);
}
