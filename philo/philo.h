/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-fvm <jpedro-fvm@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 12:49:30 by jpedro-fvm        #+#    #+#             */
/*   Updated: 2025/06/28 18:08:27 by jpedro-fvm       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>  
#include <stdbool.h>

typedef	struct s_fork
{
	int				fork_id;
	pthread_mutex_t	fork;
}					t_fork;


typedef struct s_data
{
	long		philo_nbr;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long		nbr_times_eat;
	long		start_dinner;
	bool		end_dinner;
	t_fork		*forks;
	t_philo		*philos;
}				t_data;

typedef	struct s_philo
{
	int			id;
	pthread_t	thread_id;
	long		last_meal;
	long		meals_counter;
	bool		full;
	t_fork		*left_fork;
	t_fork		*right_fork;
	t_data		*data;
}				t_philo;


//parsing.c
