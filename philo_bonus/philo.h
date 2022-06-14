/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leldiss <leldiss@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 12:31:40 by leldiss           #+#    #+#             */
/*   Updated: 2022/06/14 17:47:29 by leldiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <pthread.h>
# include <semaphore.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <stdio.h>
# include <fcntl.h>
# define MAX_INT 2147483647

typedef struct s_philo
{
	int				id;
	int				ate_count;
	int				alive;
	int				is_eating;
	long long		time_last_meal;
	pid_t			philo_pid;
	struct s_info	*conditions;
}	t_philo;

typedef struct s_info
{
	int				philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_must_eat;
	long long		start_time;
	sem_t			*forks;
	sem_t			*dead;
	sem_t			*write;
	t_philo			*philosopher;
}	t_info;

t_info		*create_info(void);
int			is_late(t_philo *philo, t_info *info);
void		init_philo(t_info *info, int size);
void		free_all(t_info *info);
void		kill_process(t_info *info, t_philo *philosophers);

void		print_error_message(char *str);
void		error_message(int error, t_info *info);
int			ft_atoi(const char *str, t_info *info);
void		show_actions(t_philo *philo, char *msg);
long long	get_timestamp(void);
int			is_philo_dead(t_philo *philo);
void		philo_sleep(t_philo *philo);

void		init_mutex(t_info *info);
void		init_philosophers(t_info *info);
void		init(t_info *info, char **argv, int argc);

void		get_started(t_info *info);
void		start_actions(t_philo *args, int i);

#endif
