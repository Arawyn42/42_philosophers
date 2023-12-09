/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 19:48:20 by drenassi          #+#    #+#             */
/*   Updated: 2023/12/09 19:16:48 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>

typedef struct s_data
{
	int				num_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				wanted_meals;
	int				is_a_philo_dead;
	long long		start_time;
	pthread_t		check;
	pthread_mutex_t	*fork;
	pthread_mutex_t	printing;
	pthread_mutex_t	eating;
	pthread_mutex_t	time;
	pthread_mutex_t	is_dead;
}				t_data;

typedef struct s_philo
{
	int				id;
	int				meals;
	long long		last_meal;
	int				ate_enough;
	int				left_fork;
	int				right_fork;
	pthread_t		thread;
	t_data			*data;
}				t_philo;

/*********************************** UTILS ************************************/
int			print_error(char *msg);
int			p_atoi(const char *s);
long long	get_time(void);
long long	get_time_from(long long time);
void		wait_time(t_data *data, long long time);
void		destroy_mutex(t_data *data);

/************************************ INIT ************************************/
int			check_args(int ac, char **av);
void		init_data(int ac, char **av, t_data *data);
void		init_philos(t_data *data, t_philo *philo);
int			init_mutex(t_data *data);
int			init_threads(t_data *data, t_philo *philo);

/*********************************** TASKS ************************************/
void		print_task(t_philo *philo, char *msg);
int			p_eat(t_philo *philo);
void		p_sleep(t_philo *philo);
void		check_dead(t_data *data, t_philo *philo);

#endif