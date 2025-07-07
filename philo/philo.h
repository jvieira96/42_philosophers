/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-fvm <jpedro-fvm@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 12:49:30 by jpedro-fvm        #+#    #+#             */
/*   Updated: 2025/07/07 17:36:38 by jpedro-fvm       ###   ########.fr       */
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

typedef enum e_time_code
{
	SECONDS,
	MILISECONDS,
	MICROSECONDS,
}	t_time_code;

typedef enum e_philo_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED,
}	t_philo_status;

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
	long			nbr_threads_running;
	pthread_t		monitor;
	pthread_mutex_t	table_mutex;
	pthread_mutex_t	write_lock;
	t_fork			*forks;
	t_philo			*philo;
}					t_data;

typedef	struct s_philo
{
	int				id;
	pthread_t		thread_id;
	long			last_meal;
	long			meals_counter;
	bool			full;
	t_fork			*first_fork;
	t_fork			*second_fork;
	t_data			*data;
	pthread_mutex_t	philo_mutex;
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
void	thread_handle(pthread_t *thread, void *(*routine)(void*), void *data, t_opcode opcode);

//getters_setters.c
void	set_bool(pthread_mutex_t *mutex, bool *dest, bool value);
bool	get_bool(pthread_mutex_t *mutex, bool *value);
void	set_long(pthread_mutex_t *mutex, long *dest, long value);
long	get_long(pthread_mutex_t *mutex, long *value);
bool	simulation_finished(t_data *data);

//sync_utils.c
void	wait_all_threads(t_data *data);
bool	all_threads_running(pthread_mutex_t *mutex, long *threads, long philo_nbr);
void	increase_long(pthread_mutex_t *mutex, long *value);

//utils.c
long	get_time(t_time_code time_code);
void	precise_usleep(long usec, t_data *data);
void	clean(t_data *data);

//write.c
void	write_status(t_philo_status status, t_philo *philo);

//start_dinner.c
void	eat(t_philo *philo);
void	*dinner_sim(void *data);
bool	start_dinner(t_data *data);

//monitor.c
bool 	philo_died(t_philo *philo);
void	*monitor_dinner(void *data);
