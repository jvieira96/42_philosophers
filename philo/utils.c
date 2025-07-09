/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-fvm <jpedro-fvm@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 11:48:34 by jpedro-fvm        #+#    #+#             */
/*   Updated: 2025/07/07 17:22:24 by jpedro-fvm       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(t_time_code time_code)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	if (time_code == SECONDS)
		return (tv.tv_sec + (tv.tv_usec / 1000000));
	else if (time_code == MILISECONDS)
		return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
	else if (time_code == MICROSECONDS)
		return ((tv.tv_sec * 1000000) + tv.tv_usec);
	return (1);
}

void	precise_usleep(long usec, t_data *data)
{
	long	start;
	long	elapsed;
	long	remaning;

	start = get_time(MICROSECONDS);
	while (get_time(MICROSECONDS) - start < usec)
	{
		if (simulation_finished(data))
			break ;
		elapsed = get_time(MICROSECONDS) - start;
		remaning = usec - elapsed;
		if (remaning > 1000)
			usleep(remaning / 2);
		else
		{
			while (get_time(MICROSECONDS) - start < usec)
				;
		}
	}
}

void	clean(t_data *data)
{
	t_philo	*philo;
	int		i;

	i = -1;
	while (++i < data->philo_nbr)
	{
		philo = data->philo + i;
		mutex_handler(&philo->philo_mutex, DESTROY);
	}
	mutex_handler(&data->table_mutex, DESTROY);
	mutex_handler(&data->write_lock, DESTROY);
	free(data->forks);
	free(data->philo);
}
