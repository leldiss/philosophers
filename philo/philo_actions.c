/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leldiss <leldiss@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 14:46:34 by leldiss           #+#    #+#             */
/*   Updated: 2022/06/15 08:41:40 by leldiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	show_actions(t_philo *philo, char *msg)
{
	long long	time;

	time = get_timestamp() - philo->conditions->start_time;
	if (philo->conditions->closet == 0)
	{
		pthread_mutex_lock(&(philo->conditions->write));
		printf("%lld philo %d %s\n", time, philo->id, msg);
		pthread_mutex_unlock(&(philo->conditions->write));
	}
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
	pthread_mutex_lock(&(conditions->forks[philo->left_fork_id]));
	show_actions(philo, "has taken a fork");
	if ((is_late(philo, conditions)) == 1)
		return ;
	pthread_mutex_lock(&(conditions->forks[philo->right_fork_id]));
	show_actions(philo, "has taken a fork");
	show_actions(philo, "is eating");
	philo->time_last_meal = get_timestamp();
	usleep(philo->conditions->time_to_eat * 1000);
	pthread_mutex_unlock(&(conditions->forks[philo->right_fork_id]));
	pthread_mutex_unlock(&(conditions->forks[philo->left_fork_id]));
	philo->ate_count++;
}

void	*start_actions(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
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
			if (philo->ate_count == philo->conditions->times_must_eat)
				return (philo);
		}
		if (philo->conditions->closet)
			break ;
		is_philo_dead(philo);
		philo_sleep(philo);
	}
	time_to_die(philo->conditions, philo);
	return (philo);
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
		if (pthread_create(&(philosophers[i].thread_id),
				NULL, start_actions, &(philosophers[i])))
			error_message(-2);
		philosophers[i].time_last_meal = get_timestamp();
		i++;
	}
	i = 0;
	while (i < info->philo)
	{
		if (pthread_join(*(&(philosophers[i].thread_id)), NULL))
			error_message(-3);
		i++;
	}
}
