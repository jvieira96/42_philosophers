/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-fvm <jpedro-fvm@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 12:49:01 by jpedro-fvm        #+#    #+#             */
/*   Updated: 2025/06/29 18:12:06 by jpedro-fvm       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
 
int	main(int argc, char *argv[])
{
	t_data	data;

	if (argc == 5 || argc == 6)
	{
		if (!parsing(&data, argv))
			return (0);
		if (!data_init(&data));
		{
			// clean(&data);
			printf(RED "Malloc failed!" RESET "\n");
			return (0);
		}
		// start_dinner(&data);
		// clean(&data);
	}
	else
		printf(RED "Error: wrong number of arguments" RESET "\n");
	return (0);
}
