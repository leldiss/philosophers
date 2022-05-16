/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leldiss <leldiss@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 12:31:45 by leldiss           #+#    #+#             */
/*   Updated: 2022/05/16 21:53:05 by leldiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

int	main(int argc, char **argv) {
	t_info info;

	if (argc == 6 || argc == 5) 
	{
		init(&info, argv, argc);
		get_started(&info);
	}
	else
		error_message(-1);
}