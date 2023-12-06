/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 21:30:04 by drenassi          #+#    #+#             */
/*   Updated: 2023/12/06 21:05:43 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/************************ Initializes philos structure ************************/
static int	init_philos(t_p *p)
{
	int	i;

	p->philo = malloc((p->num_of_philos) * sizeof(t_philo));
	if (!p->philo)
		return (0);
	i = 0;
	while (i < p->num_of_philos)
	{
		p->philo[i].id = i + 1;
		p->philo[i].meals = 0;
		p->philo[i].time_to_die = 0;
		if (i == 0)
			p->philo[i].left_fork = p->num_of_philos;
		else
			p->philo[i].left_fork = i;
		p->philo[i].right_fork = i + 1;
	}
	return (1);
}

/************************* Initializes forks (mutex) **************************/
static int	init_forks(t_p *p)
{
	int	i;

	p->fork = malloc(p->num_of_philos * sizeof(pthread_mutex_t));
	if (!p->fork)
		return (0);
	i = 0;
	while (i < p->num_of_philos)
	{
		if (pthread_mutex_init(&p->fork[i], NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}

void	task()
{
	
}

int	join_threads(t_p *p)
{
	int	i;

	i = 0;
	while (i < p->num_of_philos)
	{
		if (pthread_join(p->philo[i].thread, NULL) != 0)
			return (0);
		i++;
	}
	if (pthread_join(p->thread, NULL) != 0)
		return (0);
	return (1);
}

/* ??????????????????????????????????????????????????????????????? */
static int	init_threads(t_p *p)
{
	int	i;

	p->is_a_philo_dead = 0;
	p->start_time = get_time();
	if (pthread_mutex_init(&p->act, NULL) != 0)
		return (0);
	i = 0;
	while (i < p->num_of_philos)
	{
		p->num_of_threads = i;
		if (pthread_create(&p->philo[i].thread, NULL, &task, (void *) p) != 0)
			return (0);
		wait_time(1);
		i++;
	}
	if (pthread_create(&p->thread, NULL, &check, (void *) p) != 0)
		return (0);
	wait_time(1);
	if (!join_threads(p))
		return (0);
	return (1);
}

/*************** Checks arguments, initializes philos and forks ***************/
int	init(int ac, char **av, t_p *p)
{
	if (!check_args)
		return (0);
	p->num_of_philos = p_atoi(av[1]);
	p->time_to_die = p_atoi(av[2]);
	p->time_to_eat = p_atoi(av[3]);
	p->time_to_sleep = p_atoi(av[4]);
	if (ac == 6)
		p->wanted_meals = p_atoi(av[5]);
	else
		p->wanted_meals = -1;
	if (!init_philos(p))
		return (0);
	if (!init_forks(p))
		return (0);
	return (1);
}
