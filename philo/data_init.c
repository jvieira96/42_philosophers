/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-fvm <jpedro-fvm@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 17:26:40 by jpedro-fvm        #+#    #+#             */
/*   Updated: 2025/07/07 17:34:12 by jpedro-fvm       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_assign_forks(t_philo *philo, t_fork *forks, int philo_position)
{
	int	philo_nbr;

	philo_nbr = philo->data->philo_nbr;
	if (philo->id % 2 == 0)
	{
		philo->first_fork = &forks[philo_position];
		philo->second_fork = &forks[(philo_position + 1) % philo_nbr];
	}
	else
	{
		philo->first_fork = &forks[(philo_position + 1) % philo_nbr];
		philo->second_fork = &forks[philo_position];
	}
}

void	ft_philo_init(t_data *data)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while (++i < data->philo_nbr)
	{
		philo = data->philo + i;
		philo->id = i + 1;
		philo->full = false;
		philo->meals_counter = 0;
		philo->data = data;
		mutex_handler(&philo->philo_mutex, INIT);
		ft_assign_forks(philo, data->forks, i);
	}
}

bool	data_init(t_data *data)
{
	int	i;

	i = -1;
	data->end_dinner = false;
	data->all_threads_ready = false;
	data->nbr_threads_running = 0;
	data->philo = malloc(sizeof(t_philo) * data->philo_nbr);
	if (!data->philo)
		return (false);
	data->forks = malloc(sizeof(t_fork) * data->philo_nbr);
	if (!data->forks)
		return (false);
	mutex_handler(&data->table_mutex, INIT);
	mutex_handler(&data->write_lock, INIT);
	while (++i < data->philo_nbr)
	{
		mutex_handler(&data->forks[i].fork, INIT);
		data->forks[i].fork_id = i;
	}
	ft_philo_init(data);
	return (true);
}
