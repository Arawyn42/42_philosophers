/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tasks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 18:02:36 by drenassi          #+#    #+#             */
/*   Updated: 2023/12/07 21:23:17 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	print_task(t_p *p, int i, char task)
{
	long long	time;

	time = get_time_since(p->start_time);
	pthread_mutex_lock(&p->printing);
	if (p->is_a_philo_dead)
	{
		pthread_mutex_unlock(&p->printing);
		return (0);
	}
	else
	{
		if (task == 'f')
			printf("%lld\t%d has taken a fork\n", time, p->philo[i].id);
		else if (task == 'e')
			printf("%lld\t%d is eating\n", time, p->philo[i].id);
		else if (task == 's')
			printf("%lld\t%d is sleeping\n", time, p->philo[i].id);
		else if (task == 't')
			printf("%lld\t%d is thinking\n", time, p->philo[i].id);
		else if (task == 'd')
			printf("%lld\t%d has died\n", time, p->philo[i].id);
	}
	pthread_mutex_unlock(&p->printing);
	return (1);
}

int	p_eat(t_p *p, int i)
{
	int	left;
	int	right;

	left = p->philo[i].left_fork;
	right = p->philo[i].right_fork;
	if (pthread_mutex_lock(&p->fork[left]) || !print_task(p, i, 'f'))
		return (0);
	if (pthread_mutex_lock(&p->fork[right]) || !print_task(p, i, 'f'))
		return (0);
	if (!print_task(p, i, 'e'))
		return (0);
	p->philo[i].time_to_die = get_time();
	wait_time(p, p->time_to_eat);
	if (pthread_mutex_unlock(&p->fork[left])
		|| pthread_mutex_unlock(&p->fork[right]))
		return (0);
	p->philo[i].meals++;
	return (1);
}

int	p_sleep(t_p *p, int i)
{
	if (!print_task(p, i, 's'))
		return (0);
	wait_time(p, p->time_to_sleep);
	return (1);
}

int	p_think(t_p *p, int i)
{
	return (print_task(p, i, 't'));
}

int	p_is_dead(t_p *p, int *i)
{
	int	timetodie;

	if (*i >= p->num_of_philos)
		*i = 0;
	timetodie = get_time_since(p->philo[*i].time_to_die);
	if (timetodie > p->time_to_die)
	{
		print_task(p, *i, 'd');
		p->is_a_philo_dead = 1;
		return (1);
	}
	(*i)++;
	return (0);
}
