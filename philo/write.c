/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-fvm <jpedro-fvm@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:10:15 by jpedro-fvm        #+#    #+#             */
/*   Updated: 2025/07/07 14:48:56 by jpedro-fvm       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_status(t_philo_status status, t_philo *philo)
{
	long	elapsed;

	elapsed = get_time(MILISECONDS) - philo->data->start_dinner;
	if (philo->full)
		return ;
	mutex_handler(&philo->data->write_lock, LOCK);
	if ((status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK)
		&& !simulation_finished(philo->data))
		printf(CYAN"%-6ld %ld has taken a fork\n"RESET, elapsed, philo->id);
	else if (status == EATING && !simulation_finished(philo->data))
		printf(GREEN"%-6ld %ld is eating\n"RESET, elapsed, philo->id);
	else if (status == SLEEPING && !simulation_finished(philo->data))
		printf(BLUE"%-6ld %ld is sleeping\n"RESET, elapsed, philo->id);
	else if (status == THINKING && !simulation_finished(philo->data))
		printf(YELLOW"%-6ld %ld is thinking\n"RESET, elapsed, philo->id);
	else if (status == DIED)
		printf(RED"%-6ld %ld died\n"RESET, elapsed, philo->id);
	mutex_handler(&philo->data->write_lock, UNLOCK);
}
