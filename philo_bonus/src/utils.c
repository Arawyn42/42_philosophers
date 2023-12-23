/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 21:10:39 by drenassi          #+#    #+#             */
/*   Updated: 2023/12/23 02:26:32 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

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
void	wait_time(long long time)
{
	long long	start_time;

	start_time = get_time();
	while (get_time() - start_time < time)
		usleep(50);
}

/*********************** Destoy mutex and free pointers ***********************/
void	destroy_semaphores(t_data *data, t_philo *philo)
{
	int	i;
	int	status;

	i = 0;
	while (i < data->num_of_philos)
	{
		waitpid(philo[i].pid, &status, 0);
		i++;
	}
	sem_close(data->forks);
	sem_unlink("/forks");
	sem_close(data->print);
	sem_unlink("/print");
	sem_close(data->death);
	sem_unlink("/death");
	sem_close(data->all_eat);
	sem_unlink("/all_eat");
	sem_close(data->finished);
	sem_unlink("/finished");
}
