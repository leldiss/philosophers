/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leldiss <leldiss@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 14:27:30 by leldiss           #+#    #+#             */
/*   Updated: 2022/06/10 13:24:09 by leldiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_late(t_philo *philo, t_info *info)
{
	int	death_time;
	int	time;

	if (info->philo % 2 == 1)
	{
		if (philo->id == info->philo - 1)
		{
			time = get_timestamp() - philo->time_last_meal;
			death_time = (philo->time_last_meal
					+ info->time_to_die) - get_timestamp();
			if (death_time <= time + info->time_to_eat)
			{
				philo->alive = 0;
				usleep((info->time_to_die - time) * 1000);
				pthread_mutex_unlock(&(info->forks[philo->left_fork_id]));
				return (1);
			}
		}
	}
	return (0);
}

void	init_mutex(t_info *info)
{
	int	count;

	count = 0;
	while (count < info->philo)
	{
		if (pthread_mutex_init(&(info->forks[count]), NULL))
			error_message(-4);
		count++;
	}
}

void	init_philosophers(t_info *info)
{
	int	count;

	count = 0;
	while (count < info->philo)
	{
		info->philosopher[count].id = count + 1;
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
