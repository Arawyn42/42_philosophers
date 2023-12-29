/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 18:56:44 by drenassi          #+#    #+#             */
/*   Updated: 2023/12/29 21:45:21 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/********************* Second part of check_dead function *********************/
static int	check_dead_2(t_data *data, t_philo *philo, int i)
{
	int	time_from_last_meal;

	pthread_mutex_lock(&data->time);
	time_from_last_meal = get_time_from(philo[i].last_meal);
	if (philo[i].meals >= data->wanted_meals && data->wanted_meals != -1)
	{
		pthread_mutex_unlock(&data->time);
		return (0);
	}
	pthread_mutex_unlock(&data->time);
	if (time_from_last_meal > data->time_to_die)
	{
		print_task(&philo[i], "has died");
		pthread_mutex_lock(&data->is_dead);
		data->is_a_philo_dead++;
		pthread_mutex_unlock(&data->is_dead);
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
	while (done_philos < data->num_of_philos)
	{
		usleep(50);
		if (i >= data->num_of_philos)
			i = 0;
		if (check_dead_2(data, philo, i))
			break ;
		pthread_mutex_lock(&data->ate_enough);
		if (philo[i].ate_enough)
		{
			done_philos++;
			philo[i].ate_enough = 0;
		}
		pthread_mutex_unlock(&data->ate_enough);
		i++;
	}
}

/********************* Routine for philos threads (part 2) ********************/
static void	ate(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->ate_enough);
	philo->ate_enough = 1;
	pthread_mutex_unlock(&philo->data->ate_enough);
}

/************************* Routine for philos threads *************************/
static void	*rout(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(25000);
	while (philo->meals != philo->data->wanted_meals)
	{
		pthread_mutex_lock(&philo->data->is_dead);
		if (philo->data->is_a_philo_dead)
			return (pthread_mutex_unlock(&philo->data->is_dead), NULL);
		pthread_mutex_unlock(&philo->data->is_dead);
		if (!p_eat(philo, philo->data))
			break ;
		if (philo->data->wanted_meals != philo->meals)
		{
			pthread_mutex_lock(&philo->data->is_dead);
			if (philo->data->is_a_philo_dead)
				return (pthread_mutex_unlock(&philo->data->is_dead), NULL);
			pthread_mutex_unlock(&philo->data->is_dead);
			p_sleep(philo);
			print_task(philo, "is thinking");
		}
	}
	ate(philo);
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
		usleep(10);
		i++;
	}
	check_dead(data, philo);
	i = 0;
	while (i < data->num_of_philos)
	{
		if (pthread_join(philo[i].thread, NULL))
			return (0);
		usleep(10);
		i++;
	}
	return (1);
}
