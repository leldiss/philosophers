/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leldiss <leldiss@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 12:31:40 by leldiss           #+#    #+#             */
/*   Updated: 2022/05/16 22:04:12 by leldiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# define MAX_INT 2147483647

typedef struct	s_philo 
{
	int	id;
	int	ate_count;
	int	left_fork_id;
	int	right_fork_id;
	int	alive;
	long long	time_last_meal;
	pthread_t	thread_id;
	struct s_info *conditions;
}	t_philo;

typedef struct s_info
{
	int	philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	times_must_eat;
	long long	start_time;
	pthread_mutex_t	forks[666];
	t_philo	philosopher[666];
} t_info;


void	print_error_message(char *str);
void	error_message(int error);
int	ft_atoi(const char *str);
void	show_actions(t_philo *philo, char *msg);
long long	get_timestamp(void);
int is_philo_dead(t_philo *philo);
void	philo_sleep(t_philo *philo);

void	init_mutex(t_info *info);
void	init_philosophers(t_info *info);
void	init(t_info *info, char **argv, int argc);

void	get_started(t_info *info);
void *start_actions(void *args);

#endif