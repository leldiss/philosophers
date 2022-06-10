/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leldiss <leldiss@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 12:31:45 by leldiss           #+#    #+#             */
/*   Updated: 2022/06/10 15:45:39 by leldiss          ###   ########.fr       */
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
				sem_post(info->forks);
				return (1);
			}
		}
	}
	return (0);
}

void	free_all(t_info *info)
{
	if (info == NULL)
		return ;
	if (info->forks != NULL)
		sem_close(info->forks);
	if (info->philosopher != NULL)
		free(info->philosopher);
	if (info != NULL)
		free(info);
}

t_info	*create_info(void)
{
	t_info	*tmp;

	tmp = (t_info *)malloc(sizeof(*tmp));
	tmp->philo = 0;
	tmp->time_to_die = 0;
	tmp->time_to_eat = 0;
	tmp->times_must_eat = 0;
	tmp->start_time = 0;
	tmp->forks = NULL;
	tmp->philosopher = NULL;
	return (tmp);
}

int	main(int argc, char **argv)
{
	t_info	*info;
	int		i;
	int		ret;

	i = 0;
	info = NULL;
	if (argc == 6 || argc == 5)
	{
		info = create_info();
		init(info, argv, argc);
		get_started(info);
		while (i < info->philo)
		{
			waitpid(info->philosopher[i].philo_pid, &ret, 0);
			i++;
		}
		free_all(info);
	}
	else
		error_message(-1, info);
}
