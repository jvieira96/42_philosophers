/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-fvm <jpedro-fvm@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 12:49:30 by jpedro-fvm        #+#    #+#             */
/*   Updated: 2025/07/01 17:47:31 by jpedro-fvm       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>  
#include <stdbool.h>
#include <limits.h>

#define PARSE_ERROR -2
#define NO_TIMES_TO_EAT -1


#define RESET   "\x1b[0m"
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define BLUE    "\x1b[34m"
#define YELLOW  "\x1b[33m"

typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}	t_opcode;

typedef	struct s_fork
{
	int				fork_id;
	pthread_mutex_t	fork;
}					t_fork;

typedef struct s_philo t_philo;

typedef struct s_data
{
	long			philo_nbr;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			nbr_times_eat;
	long			start_dinner;
	bool			end_dinner;
	bool			all_threads_ready;
	pthread_mutex_t	table_mutex;
	t_fork			*forks;
	t_philo			*philo;
}					t_data;

typedef	struct s_philo
{
	int			id;
	pthread_t	thread_id;
	long		last_meal;
	long		meals_counter;
	bool		full;
	t_fork		*first_fork;
	t_fork		*second_fork;
	t_data		*data;
}				t_philo;


//parsing.cv
bool	ft_isnumeric(char *str);
bool	ft_isspace(char c);
bool	ft_valid_input(char *str);
int		ft_atol(char *str);
int		parsing(t_data *data, char **args);

//data_init.c
void	ft_assign_forks(t_philo *philo, t_fork *forks, int philo_position);
void	ft_philo_init(t_data *data);
bool	data_init(t_data *data);

//handle_threads.c
void	mutex_handler(pthread_mutex_t *mutex, t_opcode opcode);
void	tread_handle(pthread_t *thread, void *(*routine)(void*), void *data, t_opcode opcode);
