/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 21:10:39 by drenassi          #+#    #+#             */
/*   Updated: 2023/12/07 22:23:13 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/************** Converts a string of characters into an integer ***************/
int	p_atoi(const char *s)
{
	int		i;
	long	res;
	int		sign;

	i = 0;
	res = 0;
	sign = 1;
	while ((s[i] >= 9 && s[i] <= 13) || s[i] == ' ')
		i++;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			sign *= -1;
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9')
	{
		res = res * 10 + s[i] - '0';
		i++;
	}
	return (res * sign);
}

/**************** Gets time since EPOCH (1970) in milliseconds ****************/
long long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

/************ Gets the time passed since 'time' (in milliseconds) *************/
long long	get_time_since(long long time)
{
	if (time > 0)
		return (get_time() - time);
	return (0);
}

/************* Wait for 'time' milliseconds (checks every 0.5 ms) *************/
void	wait_time(t_p *p, long long time)
{
	long long	start_time;

	start_time = get_time();
	while (!p->is_a_philo_dead && get_time() - start_time < time)
		usleep(50);
}

/********************** Destoys mutex and frees pointers **********************/
void	free_all(t_p *p)
{
	int	i;

	i = 0;
	while (i < p->num_of_philos)
	{
		pthread_mutex_destroy(&p->fork[i]);
		i++;
	}
	pthread_mutex_destroy(&p->printing);
	free(p->philo);
	free(p->fork);
}
