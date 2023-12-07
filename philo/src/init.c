/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 21:30:04 by drenassi          #+#    #+#             */
/*   Updated: 2023/12/07 22:44:08 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/************************ Initializes philos structure ************************/
static int	init_philos(t_p *p)
{
	int	i;

	p->philo = malloc((p->num_of_philos) * sizeof(t_philo));
	if (!p->philo)
		return (print_error("Error: philos malloc.\n"));
	i = 0;
	while (i < p->num_of_philos)
	{
		p->philo[i].id = i + 1;
		p->philo[i].meals = 0;
		p->philo[i].time_to_die = 0;
		p->philo[i].left_fork = i;
		if (i + 1 == p->num_of_philos)
			p->philo[i].right_fork = 0;
		else
			p->philo[i].right_fork = i + 1;
		i++;
	}
	p->is_a_philo_dead = 0;
	p->start_time = get_time();
	return (1);
}

/************************* Initializes forks (mutex) **************************/
static int	init_forks(t_p *p)
{
	int	i;

	p->fork = malloc(p->num_of_philos * sizeof(pthread_mutex_t));
	if (!p->fork)
		return (print_error("Error: forks malloc.\n"));
	i = 0;
	while (i < p->num_of_philos)
	{
		if (pthread_mutex_init(&p->fork[i], NULL))
			return (print_error("Error: forks pthread_mutex_init.\n"));
		i++;
	}
	if (pthread_mutex_init(&p->printing, NULL))
		return (print_error("Error: only_one_philo: pthread_mutex_init\n"));
	return (1);
}

static int	only_one_philo(t_p *p)
{
	p->start_time = get_time();
	printf("%lld\t%d has taken a fork\n", get_time_since(p->start_time), 1);
	usleep(p->time_to_die * 1000);
	printf("%lld\t%d has died\n", get_time_since(p->start_time), 1);
	free(p->philo);
	free(p->fork);
	return (1);
}

/*************** Checks arguments, initializes philos and forks ***************/
int	init(int ac, char **av, t_p *p)
{
	if (!check_args(ac, av))
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
	if (p->num_of_philos == 1)
		return (only_one_philo(p));
	if (!init_threads(p))
		return (0);
	free_all(p);
	return (1);
}
