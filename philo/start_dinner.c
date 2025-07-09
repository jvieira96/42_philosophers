/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_dinner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-fvm <jpedro-fvm@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 11:46:19 by jpedro-fvm        #+#    #+#             */
/*   Updated: 2025/07/08 12:30:21 by jpedro-fvm       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	thinking(t_philo *philo, bool pre_sim)
{
	long	time_to_eat;
	long	time_to_sleep;
	long	time_to_think;

	if (pre_sim == false)
		write_status(THINKING, philo);
	if (philo->data->philo_nbr % 2 == 0)
		return ;
	time_to_eat = philo->data->time_to_eat;
	time_to_sleep = philo->data->time_to_sleep;
	time_to_think = (time_to_eat * 2) - time_to_sleep;
	if (time_to_think < 0)
		time_to_think = 0;
	precise_usleep(time_to_think * 0.46, philo->data);
}

/*
	routine for lonely philo
	fake lock fork
	sleep until he dies
*/
void	*lonely_philo(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->data);
	set_long(&philo->philo_mutex, &philo->last_meal, get_time(MILISECONDS));
	increase_long(&philo->data->table_mutex, &philo->data->nbr_threads_running);
	write_status(TAKE_FIRST_FORK, philo);
	while (!simulation_finished(philo->data))
		;
	return (NULL);
}

void	eat(t_philo *philo)
{
	mutex_handler(&philo->first_fork->fork, LOCK);
	write_status(TAKE_FIRST_FORK, philo);
	mutex_handler(&philo->second_fork->fork, LOCK);
	write_status(TAKE_SECOND_FORK, philo);
	set_long(&philo->philo_mutex, &philo->last_meal, get_time(MILISECONDS));
	philo->meals_counter++;
	write_status(EATING, philo);
	precise_usleep(philo->data->time_to_eat, philo->data);
	if (philo->data->nbr_times_eat > 0
		&& philo->meals_counter == philo->data->nbr_times_eat)
		set_bool(&philo->philo_mutex, &philo->full, true);
	mutex_handler(&philo->first_fork->fork, UNLOCK);
	mutex_handler(&philo->second_fork->fork, UNLOCK);
}

void	*dinner_sim(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->data);
	set_long(&philo->philo_mutex, &philo->last_meal, get_time(MILISECONDS));
	increase_long(&philo->data->table_mutex, &philo->data->nbr_threads_running);
	de_sync_philos(philo);
	while (!simulation_finished(philo->data))
	{
		if (philo->full)
			break ;
		eat(philo);
		write_status(SLEEPING, philo);
		precise_usleep(philo->data->time_to_sleep, philo->data);
		thinking(philo, false);
	}
	return (NULL);
}

bool	start_dinner(t_data *data)
{
	int	i;

	i = -1;
	if (data->nbr_times_eat == 0)
		return (false);
	else if (data->philo_nbr == 1)
		thread_handle(&data->philo[0].thread_id, lonely_philo,
			&data->philo[0], CREATE);
	else
	{
		while (++i < data->philo_nbr)
			thread_handle(&data->philo[i].thread_id, dinner_sim,
				&data->philo[i], CREATE);
	}
	thread_handle(&data->monitor, monitor_dinner, data, CREATE);
	data->start_dinner = get_time(MILISECONDS);
	set_bool(&data->table_mutex, &data->all_threads_ready, true);
	i = -1;
	while (++i < data->philo_nbr)
		thread_handle(&data->philo[i].thread_id, NULL, NULL, JOIN);
	set_bool(&data->table_mutex, &data->end_dinner, true);
	thread_handle(&data->monitor, NULL, NULL, JOIN);
	return (true);
}
