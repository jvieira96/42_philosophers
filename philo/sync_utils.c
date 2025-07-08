/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-fvm <jpedro-fvm@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 11:45:38 by jpedro-fvm        #+#    #+#             */
/*   Updated: 2025/07/08 12:29:57 by jpedro-fvm       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	SPINLOCK to sync all threads starting
*/
void	wait_all_threads(t_data *data)
{
	while (!get_bool(&data->table_mutex, &data->all_threads_ready))
		;
}

/*
	monitor waits untill all threads are running
*/
bool	all_threads_running(pthread_mutex_t *mutex, \
long *threads, long philo_nbr)
{
	bool	ret;

	ret = false;
	mutex_handler(mutex, LOCK);
	if (*threads == philo_nbr)
		ret = true;
	mutex_handler(mutex, UNLOCK);
	return (ret);
}

/*
	increase threads running to sync monitor
*/
void	increase_long(pthread_mutex_t *mutex, long *value)
{
	mutex_handler(mutex, LOCK);
	(*value)++;
	mutex_handler(mutex, UNLOCK);
}

/*
	Fairness
*/
void	de_sync_philos(t_philo *philo)
{
	if (philo->data->philo_nbr % 2 == 0)
	{
		if (philo->id % 2 == 0)
			precise_usleep(3e4, philo->data);
	}
	else
	{
		if (philo->id % 2)
		{
			thinking(philo, true);
		}
	}
}
