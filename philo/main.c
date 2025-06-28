/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-fvm <jpedro-fvm@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 12:49:01 by jpedro-fvm        #+#    #+#             */
/*   Updated: 2025/06/28 13:12:00 by jpedro-fvm       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ph_isnumeric(char c)
{
	if (c < 49 || c > 57) 
		return (0);
	else
		return (1);	
}

int	ph_wrong_args(char *args[])
{
	int	i;
	int	x;

	i = 0;
	while (args[i])
	{
		x = 0;
		while (args[i][x])
		{
			if (!ph_isnumeric(args[i][x]))
			{
				printf ("Non numeric value detected");
				return (1);
			}
			x++;
		}
		i ++;
	}
	return (0);
}

void	main(int argc, char *argv[])
{
	if (argc < 5 || argc > 6)
	{
		printf (" Wrong number of arguments");
		return ;
	}
	if (ph_wrong_args(argv))
		return ;
	return ;
}
