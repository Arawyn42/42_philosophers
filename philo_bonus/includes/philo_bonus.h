/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 19:48:20 by drenassi          #+#    #+#             */
/*   Updated: 2023/12/24 13:19:04 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>

typedef struct s_data
{
	int				num_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				wanted_meals;
	long long		start_time;
	sem_t			*forks;
	sem_t			*print;
	sem_t			*death;
	sem_t			*finished;
	sem_t			*all_eat;
}				t_data;

typedef struct s_philo
{
	int				id;
	int				meals;
	long long		last_meal;
	pid_t			pid;
	pthread_t		is_dead;
	t_data			*data;
}				t_philo;

/*********************************** UTILS ************************************/
int			print_error(char *msg);
int			p_atoi(const char *s);
long long	get_time(void);
long long	get_time_from(long long time);
void		wait_time(long long time);
void		destroy_semaphores(t_data *data, t_philo *philo);

/************************************ INIT ************************************/
int			check_args(int ac, char **av);
void		init_data(int ac, char **av, t_data *data);
void		init_philos(t_data *data, t_philo *philo);
void		init_semaphores(t_data *data);
void		init_processes(t_data *data, t_philo *philo);

/*********************************** TASKS ************************************/
void		routine(t_philo *philo);
void		print_task(t_philo *philo, char *msg);
void		p_eat(t_philo *philo, t_data *data);
void		p_sleep(t_philo *philo);

#endif