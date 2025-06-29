/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-fvm <jpedro-fvm@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 12:49:01 by jpedro-fvm        #+#    #+#             */
/*   Updated: 2025/06/29 15:39:09 by jpedro-fvm       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
 
int	main(int argc, char *argv[])
{
	t_data	data;

	if (argc == 5 || argc == 6)
	{
		if (!ft_parse_input(&data, argv))
			return (0);
		// data_init(&data);
		// start_dinner(&data);
		// clean(&data);
	}
	else
		printf(RED "Error: wrong number of arguments" RESET "\n");
	return (0);
}
