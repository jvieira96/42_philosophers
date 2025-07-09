/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-fvm <jpedro-fvm@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 17:00:42 by jpedro-fvm        #+#    #+#             */
/*   Updated: 2025/07/07 15:13:42 by jpedro-fvm       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	mutex_handler(pthread_mutex_t *mutex, t_opcode opcode)
{
	if (opcode == LOCK)
		pthread_mutex_lock(mutex);
	else if (opcode == UNLOCK)
		pthread_mutex_unlock(mutex);
	else if (opcode == INIT)
		pthread_mutex_init(mutex, NULL);
	else if (opcode == DESTROY)
		pthread_mutex_destroy(mutex);
}

void	thread_handle(pthread_t *thread, void *(*routine)(void*),
void *data, t_opcode opcode)
{
	if (opcode == CREATE)
		pthread_create(thread, NULL, routine, data);
	if (opcode == JOIN)
		pthread_join(*thread, NULL);
	if (opcode == DETACH)
		pthread_detach(*thread);
}
