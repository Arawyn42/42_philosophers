/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 18:56:44 by drenassi          #+#    #+#             */
/*   Updated: 2023/12/09 19:01:18 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/********************* Second part of check_dead function *********************/
static int	check_dead_2(t_data *data, t_philo *philo, int i)
{
	int	time_from_last_meal;

	pthread_mutex_lock(&data->time);
	time_from_last_meal = get_time_from(philo[i].last_meal);
	pthread_mutex_unlock(&data->time);
	if (time_from_last_meal > data->time_to_die)
	{
		print_task(&philo[i], "has died");
		pthread_mutex_lock(&data->is_dead);
		data->is_a_philo_dead++;
		pthread_mutex_unlock(&data->is_dead);
		pthread_mutex_unlock(&data->eating);
		return (1);
	}
	return (0);
}

/********************** Routine to check if a philo died **********************/
void	check_dead(t_data *data, t_philo *philo)
{
	int	i;
	int	done_philos;

	i = 0;
	done_philos = 0;
	while(done_philos < data->num_of_philos)
	{
		usleep(50);
		if (i >= data->num_of_philos)
			i = 0;
		pthread_mutex_lock(&data->eating);
		if (check_dead_2(data, philo, i))
			break ;
		if (philo[i].ate_enough)
		{
			done_philos++;
			philo[i].ate_enough = 0;
		}
		pthread_mutex_unlock(&data->eating);
		i++;
	}
}

/************************* Routine for philos threads *************************/
static void	*rout(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo->meals != philo->data->wanted_meals)
	{
		pthread_mutex_lock(&philo->data->is_dead);
		if (philo->data->is_a_philo_dead)
			return (pthread_mutex_unlock(&philo->data->is_dead), NULL) ;
		pthread_mutex_unlock(&philo->data->is_dead);
		if (!p_eat(philo))
			break ;
		if (philo->data->wanted_meals != philo->meals)
		{
			pthread_mutex_lock(&philo->data->is_dead);
			if (philo->data->is_a_philo_dead)
				return (pthread_mutex_unlock(&philo->data->is_dead), NULL) ;
			pthread_mutex_unlock(&philo->data->is_dead);
			p_sleep(philo);
			print_task(philo, "is thinking");
		}
	}
	pthread_mutex_lock(&philo->data->eating);
	philo->ate_enough = 1;
	pthread_mutex_unlock(&philo->data->eating);
	return (NULL);
}

/************************* Initialize philos threads **************************/
int	init_threads(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		if (pthread_create(&philo[i].thread, NULL, &rout, &philo[i]))
			return (0);
		usleep(50);
		i++;
	}
	check_dead(data, philo);
	i = 0;
	while (i < data->num_of_philos)
	{
		if (pthread_join(philo[i].thread, NULL))
			return (0);
		usleep(50);
		i++;
	}
	return (1);
}
