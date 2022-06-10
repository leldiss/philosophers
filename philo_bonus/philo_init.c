/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leldiss <leldiss@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 14:27:30 by leldiss           #+#    #+#             */
/*   Updated: 2022/06/10 15:42:50 by leldiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philo(t_info *info, int size)
{
	t_philo	*tmp;
	int		i;

	tmp = (t_philo *)malloc((sizeof(*tmp) * size));
	info->philosopher = tmp;
	i = 1;
	while (i <= size)
	{
		tmp->alive = 1;
		tmp->ate_count = 0;
		tmp->time_last_meal = 0;
		tmp->id = i;
		tmp->conditions = info;
		tmp->philo_pid = 0;
		tmp++;
		i++;
	}
}

void	init_sem(t_info *info)
{
	sem_unlink("/forks");
	info->forks = sem_open("/forks", O_CREAT, S_IRWXU, info->philo);
	if (info->forks == SEM_FAILED)
		error_message(-4, info);
}

void	init(t_info *info, char **argv, int argc)
{
	info->philo = ft_atoi(argv[1], info);
	info->time_to_die = ft_atoi(argv[2], info);
	info->time_to_eat = ft_atoi(argv[3], info);
	info->time_to_sleep = ft_atoi(argv[4], info);
	if (argc == 6)
		info->times_must_eat = ft_atoi(argv[5], info);
	else
		info->times_must_eat = -1;
	init_philo(info, info->philo);
	init_sem(info);
}
