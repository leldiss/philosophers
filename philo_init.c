/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leldiss <leldiss@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 14:27:30 by leldiss           #+#    #+#             */
/*   Updated: 2022/05/16 21:52:56 by leldiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_mutex(t_info *info)
{
	int	count;

	count = 0;
	while (count < info->philo)
	{
		pthread_mutex_init(&(info->forks[count]), NULL); // Написать проверку
		count++;
	}
}


void	init_philosophers(t_info *info) 
{
	int	count;
	
	count = 0;
	while (count < info->philo) 
	{
		info->philosopher[count].id = count;
		info->philosopher[count].left_fork_id = count;
		info->philosopher[count].right_fork_id = (count + 1) % info->philo;
		info->philosopher[count].alive = 1;
		info->philosopher[count].ate_count = 0;
		info->philosopher[count].conditions = info;
		count++;
	}
}

void	init(t_info *info, char **argv, int argc) 
{
	info->philo = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		info->times_must_eat = ft_atoi(argv[5]);
	else
		info->times_must_eat = -1;
	init_philosophers(info);
	init_mutex(info);
}
