/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-fvm <jpedro-fvm@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 16:22:42 by jpedro-fvm        #+#    #+#             */
/*   Updated: 2025/07/08 11:40:28 by jpedro-fvm       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	check if the filo died based on the difference between
	the last meal and time to die
*/
bool philo_died(t_philo *philo)
{
	long	elapsed;
	long	time_to_die;

	if (get_bool(&philo->philo_mutex, &philo->full))
		return (false);
	elapsed = get_time(MILISECONDS) - get_long(&philo->philo_mutex, &philo->last_meal);
	time_to_die = philo->data->time_to_die / 1e3;
	if (time_to_die < elapsed)
		return (true);
	return (false);
}

void	*monitor_dinner(void *data)
{
	t_data	*table;
	int		i;

	table = (t_data *)data;
	while (!all_threads_running(&table->table_mutex, &table->nbr_threads_running, table->philo_nbr));
		;
	while (!simulation_finished(table))
	{
		i = 0;
		while (i < table->philo_nbr)
		{
			if (philo_died(table->philo + i))
			{
				set_bool(&table->table_mutex, &table->end_dinner, true);
				write_status(DIED, table->philo + i);
				return (NULL);
			}
			i++;
		}
	}
	return (NULL);
}
