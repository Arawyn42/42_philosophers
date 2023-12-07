/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 18:56:44 by drenassi          #+#    #+#             */
/*   Updated: 2023/12/07 23:09:29 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	*rout(void *arg)
{
	t_p	*p;
	int	i;

	p = (t_p *)arg;
	i = p->thread_id;
	while (((p->wanted_meals > 0 && p->philo[i].meals < p->wanted_meals)
		|| p->wanted_meals < 0))
	{
		if (p->is_a_philo_dead || !p_eat(p, i))
			break ;
		if (p->wanted_meals != p->philo[i].meals)
			if (p->is_a_philo_dead || !p_sleep(p, i) || !p_think(p, i))
				break ;
	}
	return (NULL);
}

static void	*check_dead(void *arg)
{
	t_p	*p;
	int	i;

	p = (t_p *)arg;
	i = 0;
	while (((p->wanted_meals > 0 && p->philo[i].meals < p->wanted_meals)
		|| p->wanted_meals < 0) && !p->is_a_philo_dead)
		if (p_is_dead(p, &i))
			break ;
	return (NULL);
}

static int	join_threads(t_p *p)
{
	int	i;

	i = 0;
	while (i < p->num_of_philos)
	{
		if (pthread_join(p->philo[i].thread, NULL))
			return (print_error("Error: join_threads: pthread_join\n"));
		i++;
	}
	if (pthread_join(p->check, NULL))
		return (print_error("Error: join_threads: pthread_join\n"));
	return (1);
}

/* ??????????????????????????????????????????????????????????????? */
int	init_threads(t_p *p)
{
	int	i;

	i = 0;
	while (i < p->num_of_philos)
	{
		p->thread_id = i;
		if (pthread_create(&p->philo[i].thread, NULL, &rout, (void *) p))
			return (print_error("Error: init_threads: pthread_create\n"));
		usleep(1000);
		i++;
	}
	if (pthread_create(&p->check, NULL, &check_dead, (void *) p))
		return (print_error("Error: init_threads: pthread_create\n"));
	if (!join_threads(p))
		return (0);
	return (1);
}
