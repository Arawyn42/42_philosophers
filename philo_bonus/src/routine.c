/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 18:56:44 by drenassi          #+#    #+#             */
/*   Updated: 2023/12/23 02:01:00 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

/********************** Routine to check if a philo died **********************/
static void	*check_dead(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	while (1)
	{
		sem_wait(data->death);
		if (philo->last_meal + data->time_to_die < get_time())
		{
			print_task(philo, "is dead");
			sem_post(data->finished);
			return (NULL);
		}
		if (data->wanted_meals != -1 && philo->meals >= data->wanted_meals)
		{
			sem_post(data->all_eat);
			sem_post(data->death);
			return (NULL);
		}
		sem_post(data->death);
		usleep(10);
	}
	return (NULL);
}

/************************* Routine for philos threads *************************/
void	routine(t_philo *philo)
{
	if (philo->id % 2 == 0)
		usleep(25000);
	pthread_create(&philo->is_dead, NULL, check_dead, philo);
	while (1)
	{
		p_eat(philo, philo->data);
		p_sleep(philo);
		print_task(philo, "is thinking");
	}
}
