/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-fvm <jpedro-fvm@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 18:08:48 by jpedro-fvm        #+#    #+#             */
/*   Updated: 2025/07/07 18:00:04 by jpedro-fvm       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	ft_isnumeric(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
		{
			printf(RED "Only numeric values allowed!"RESET "\n");
			return (false);
		}
		i++;
	}
	return (true);
}

bool	ft_isspace(char c)
{
	if ((c >= 9 && c <= 13 ) || c == 32)
		return (true);
	return (false);
}

bool	ft_valid_input(char *str)
{
	int	i;
	
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
		{
			printf(RED "Only positive values allowed!" RESET "\n");
			return (false);
		}
		i++;
	}
	if (!str[i])
	{
		printf(RED "Empty value" RESET "\n");																		
		return (false);
	}
	if (!ft_isnumeric(&str[i]))
		return (false);
	return (true);
}

int	ft_atol(char *str)
{
	int		i;
	long	number;

	number = 0;
	i = 0;
	if (!ft_valid_input(str))
		return (PARSE_ERROR);
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		number = number * 10 + (str[i] - '0');
		i++;
	}
	if (number > INT_MAX)
	{
		printf(RED "Value bigger than INT_MAX!"RESET "\n");
		return (PARSE_ERROR);
	}
	return (number);
}

int	parsing(t_data *data, char **args)
{
	data->philo_nbr = ft_atol(args[1]);
	if (data->philo_nbr == PARSE_ERROR)
		return(false);
	data->time_to_die = ft_atol(args[2]) * 1e3; 
	if (data->time_to_die < 60000)
		return (false);
	data->time_to_eat = ft_atol(args[3]) * 1e3;
	if (data->time_to_eat < 60000)
		return (false);
	data->time_to_sleep = ft_atol(args[4]) * 1e3;
	if (data->time_to_sleep < 60000)
		return (false);
	if (args[5])
	{
		data->nbr_times_eat = ft_atol(args[5]);
		if (data->nbr_times_eat == PARSE_ERROR)
			return (data->nbr_times_eat);
	}
	else
		data->nbr_times_eat = NO_TIMES_TO_EAT;
	return (true) ;
}
