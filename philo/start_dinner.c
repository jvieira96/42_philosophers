/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_dinner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-fvm <jpedro-fvm@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 11:46:19 by jpedro-fvm        #+#    #+#             */
/*   Updated: 2025/07/07 17:43:52 by jpedro-fvm       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	routine for lonely philo
	fake lock fork
	sleep until he dies
*/
void	*lonely_philo(void * data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->data);
	set_long(&philo->philo_mutex, &philo->last_meal,  get_time(MILISECONDS));
	increase_long(&philo->data->table_mutex,  &philo->data->nbr_threads_running);
	write_status(TAKE_FIRST_FORK, philo);
	while (!simulation_finished(philo->data))
		usleep(200);
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
	increase_long(&philo->data->table_mutex,  &philo->data->nbr_threads_running);
	while (!simulation_finished(philo->data))
	{
		// 1 check am i full?
		if (philo->full)
			break ;
		// 2 eat
		eat(philo);
		// 3 sleep -> wriTe status & precise usleep
		write_status(SLEEPING, philo);
		precise_usleep(philo->data->time_to_sleep, philo->data);
		// 4 thinking
		write_status(THINKING, philo);
	}
	return (NULL);
}

bool	start_dinner(t_data *data)
{
	int	i;

	i = 0;
	if (data->nbr_times_eat == 0)
		return (false);
	else if (data->philo_nbr == 1)
		thread_handle(&data->philo[0].thread_id, lonely_philo, &data->philo[0], CREATE);
	else
	{
		while (i < data->philo_nbr)
		{
			thread_handle(&data->philo[i].thread_id, dinner_sim, &data->philo[i], CREATE);
			i++;
		}
	}
	thread_handle(&data->monitor, monitor_dinner, data, CREATE);
	data->start_dinner = get_time(MILISECONDS);
	set_bool(&data->table_mutex, &data->all_threads_ready, true);
	i = 0;
	while (i < data->philo_nbr)
	{
		thread_handle(&data->philo[i].thread_id, NULL, NULL, JOIN);
		i++;
	}
	set_bool(&data->table_mutex, &data->end_dinner, true);
	thread_handle(&data->monitor, NULL, NULL, JOIN);
	return (true);
}
