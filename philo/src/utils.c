/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 21:10:39 by drenassi          #+#    #+#             */
/*   Updated: 2023/12/12 21:41:20 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/*************** Convert a string of characters into an integer ***************/
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

/**************** Get time since EPOCH (1970) in milliseconds *****************/
long long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

/************* Get the time passed since 'time' (in milliseconds) *************/
long long	get_time_from(long long time)
{
	if (time > 0)
		return (get_time() - time);
	return (0);
}

/************* Wait for 'time' milliseconds (checks every 0.5 ms) *************/
void	wait_time(t_data *data, long long time)
{
	long long	start_time;
	int			is_dead;

	start_time = get_time();
	pthread_mutex_lock(&data->is_dead);
	is_dead = data->is_a_philo_dead;
	pthread_mutex_unlock(&data->is_dead);
	while (!is_dead && get_time() - start_time < time)
	{
		pthread_mutex_lock(&data->is_dead);
		is_dead = data->is_a_philo_dead;
		pthread_mutex_unlock(&data->is_dead);
		usleep(50);
	}
}

/*********************** Destoy mutex and free pointers ***********************/
void	destroy_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		pthread_mutex_destroy(&data->fork[i]);
		i++;
	}
	pthread_mutex_destroy(&data->printing);
	pthread_mutex_destroy(&data->ate_enough);
	pthread_mutex_destroy(&data->time);
	pthread_mutex_destroy(&data->is_dead);
	free(data->fork);
}
