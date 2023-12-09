/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tasks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 18:02:36 by drenassi          #+#    #+#             */
/*   Updated: 2023/12/09 19:03:06 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/************************ Print a task in the terminal ************************/
void	print_task(t_philo *philo, char *msg)
{
	t_data			*data;
	long long	time;

	data = philo->data;
	pthread_mutex_lock(&data->printing);
	time = get_time_from(data->start_time);
	pthread_mutex_lock(&data->is_dead);
	if (data->is_a_philo_dead)
	{
		pthread_mutex_unlock(&data->printing);
		pthread_mutex_unlock(&data->is_dead);
		return ;
	}
	pthread_mutex_unlock(&data->is_dead);
	printf("%lld\t%d %s\n", time, philo->id, msg);
	pthread_mutex_unlock(&data->printing);
}

/***************************** Eat task (part 2) ******************************/
static int	p_eat2(t_philo *philo, t_data *data, int left, int right)
{
	if (data->is_a_philo_dead)
	{
		pthread_mutex_unlock(&data->fork[left]);
		pthread_mutex_unlock(&data->fork[right]);
		return (0);
	}
	print_task(philo, "has taken a fork");
	pthread_mutex_lock(&data->eating);
	pthread_mutex_lock(&data->time);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&data->time);
	if (philo->meals == data->wanted_meals)
	{
		pthread_mutex_unlock(&data->fork[left]);
		pthread_mutex_unlock(&data->fork[right]);
		pthread_mutex_unlock(&data->eating);
		return (0);
	}
	print_task(philo, "is eating");
	philo->meals++;
	pthread_mutex_unlock(&data->eating);
	wait_time(data, data->time_to_eat);
	pthread_mutex_unlock(&data->fork[left]);
	pthread_mutex_unlock(&data->fork[right]);
	return (1);
}

/********************************** Eat task **********************************/
int	p_eat(t_philo *philo)
{
	t_data	*data;
	int	left;
	int	right;

	data = philo->data;
	left = philo->left_fork;
	right = philo->right_fork;
	pthread_mutex_lock(&data->fork[left]);
	pthread_mutex_lock(&data->is_dead);
	if (data->is_a_philo_dead)
	{
		pthread_mutex_unlock(&data->fork[left]);
		pthread_mutex_unlock(&data->is_dead);
		return (0);
	}
	pthread_mutex_unlock(&data->is_dead);
	print_task(philo, "has taken a fork");
	pthread_mutex_lock(&data->fork[right]);
	if (!p_eat2(philo, data, left, right))
		return (0);
	return (1);
}

/********************************* Sleep task *********************************/
void	p_sleep(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	print_task(philo, "is sleeping");
	wait_time(data, data->time_to_sleep);
}
