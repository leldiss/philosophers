/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leldiss <leldiss@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 14:46:34 by leldiss           #+#    #+#             */
/*   Updated: 2022/06/10 13:38:29 by leldiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	show_actions(t_philo *philo, char *msg)
{
	long long	time;

	time = get_timestamp() - philo->conditions->start_time;
	printf("%lld philo %d %s\n", time, philo->id, msg);
}

void	philo_sleep(t_philo *philo)
{
	int	time;

	time = get_timestamp() - philo->time_last_meal;
	if (time < philo->conditions->time_to_die)
	{
		if (philo->conditions->time_to_die - time
			>= philo->conditions->time_to_sleep)
			time = philo->conditions->time_to_sleep;
		else
			time = philo->conditions->time_to_die - time;
		show_actions(philo, "is sleeping");
		usleep(time * 1000);
	}
	else
	{
		philo->alive = 0;
		time = 1;
	}
}

void	start_eating(t_philo *philo)
{
	t_info	*conditions;

	conditions = philo->conditions;
	sem_wait(conditions->forks);
	show_actions(philo, "has taken a fork");
	if ((is_late(philo, conditions)) == 1)
		return ;
	sem_wait(conditions->forks);
	show_actions(philo, "has taken a fork");
	show_actions(philo, "is eating");
	usleep(philo->conditions->time_to_eat * 1000);
	sem_post(conditions->forks);
	sem_post(conditions->forks);
	philo->time_last_meal = get_timestamp();
	philo->ate_count++;
}

void	start_actions(t_philo *args, int i)
{
	t_philo	*philo;

	philo = &args[i];
	if (philo->id % 2 == 0)
	{
		philo_sleep(philo);
		is_philo_dead(philo);
	}
	while (philo->alive == 1)
	{
		if (philo->conditions->philo > 1)
		{
			if (philo->ate_count != philo->conditions->times_must_eat)
				start_eating(philo);
		}
		philo_sleep(philo);
		if (is_philo_dead(philo))
			break ;
		show_actions(philo, "is thinking");
	}
	show_actions(philo, "died");
}

void	get_started(t_info *info)
{
	int		i;
	t_philo	*philosophers;

	philosophers = info->philosopher;
	i = 0;
	info->start_time = get_timestamp();
	while (i < info->philo)
	{
		philosophers[i].time_last_meal = get_timestamp();
		philosophers[i].philo_pid = fork();
		if (philosophers[i].philo_pid < 0)
			error_message(-2);
		else if (philosophers[i].philo_pid == 0)
		{
			start_actions(philosophers, i);
			free_all(info);
			exit(1);
		}
		i++;
	}
}
