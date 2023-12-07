/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 19:48:20 by drenassi          #+#    #+#             */
/*   Updated: 2023/12/07 22:32:13 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				id;
	int				meals;
	long long		time_to_die;
	int				left_fork;
	int				right_fork;
	pthread_t		thread;
	
}				t_philo;

typedef struct s_p
{
	int				num_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				wanted_meals;
	int				thread_id;
	int				is_a_philo_dead;
	long long		start_time;
	pthread_t		check;
	pthread_mutex_t	*fork;
	pthread_mutex_t	printing;
	t_philo			*philo;
}				t_p;

/*********************************** UTILS ************************************/
int			print_error(char *msg);
int			p_atoi(const char *s);
long long	get_time(void);
long long	get_time_since(long long time);
void		wait_time(t_p *p, long long time);
void		free_all(t_p *p);

/************************************ INIT ************************************/
int			check_args(int ac, char **av);
int			init(int ac, char **av, t_p *p);
int			init_threads(t_p *p);

/*********************************** TASKS ************************************/
int			p_eat(t_p *p, int i);
int			p_sleep(t_p *p, int i);
int			p_think(t_p *p, int i);
int			p_is_dead(t_p *p, int *i);

#endif