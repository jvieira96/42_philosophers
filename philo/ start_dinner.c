/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*    start_dinner.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-fvm <jpedro-fvm@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 11:46:19 by jpedro-fvm        #+#    #+#             */
/*   Updated: 2025/07/01 17:57:21 by jpedro-fvm       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_all_threads(t_data *data)
{
	int	value;

	value = false;

	while (value == false)
	{
		mutex_handler(&data->table_mutex, LOCK);
		value = data->all_threads_ready;
		mutex_handler(&data->table_mutex, UNLOCK);
	}
}

void	*dinner_sim(void	*data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->data);
	return (NULL);
}

bool	start_dinner(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_nbr)
	{
		tread_handle(&data->philo[i].thread_id, dinner_sim, &data->philo[i], CREATE);
		i++;
	}
	mutex_handler(&data->table_mutex, LOCK);
	data->all_threads_ready = true;
	mutex_handler(&data->table_mutex, UNLOCK);
}