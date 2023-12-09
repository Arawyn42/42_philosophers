/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 21:30:04 by drenassi          #+#    #+#             */
/*   Updated: 2023/12/09 18:58:30 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/************************* Initialize data structure **************************/
void	init_data(int ac, char **av, t_data *data)
{
	data->num_of_philos = p_atoi(av[1]);
	data->time_to_die = p_atoi(av[2]);
	data->time_to_eat = p_atoi(av[3]);
	data->time_to_sleep = p_atoi(av[4]);
	data->wanted_meals = -1;
	if (ac == 6)
		data->wanted_meals = p_atoi(av[5]);
	data->is_a_philo_dead = 0;
}

/************************ Initialize philos structure *************************/
void	init_philos(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		memset(&philo[i], 0, sizeof(t_philo));
		philo[i].data = data;
		philo[i].id = i + 1;
		philo[i].meals = 0;
		philo[i].last_meal = 0;
		philo[i].left_fork = i;
		philo[i].right_fork = i + 1;
		if (i + 1 == data->num_of_philos)
			philo[i].right_fork = 0;
		i++;
	}
	data->start_time = get_time();
}

/**************** Initialize eating, time, and is_dead mutexes ****************/
static int	init_mutex2(t_data *data)
{
	if (pthread_mutex_init(&data->eating, NULL))
	{
		free(data->fork);
		return (print_error("Error: init_mutex: pthread_mutex_init.\n"));
	}
	if (pthread_mutex_init(&data->time, NULL))
	{
		free(data->fork);
		return (print_error("Error: init_mutex: pthread_mutex_init.\n"));
	}
	if (pthread_mutex_init(&data->is_dead, NULL))
	{
		free(data->fork);
		return (print_error("Error: init_mutex: pthread_mutex_init.\n"));
	}
	return (1);
}

/******************* Initializes forks and printing mutexes *******************/
int	init_mutex(t_data *data)
{
	int	i;

	data->fork = malloc(data->num_of_philos * sizeof(pthread_mutex_t));
	if (!data->fork)
		return (print_error("Error: init_mutex: malloc.\n"));
	i = 0;
	while (i < data->num_of_philos)
	{
		if (pthread_mutex_init(&data->fork[i], NULL))
		{
			free(data->fork);
			return (print_error("Error: init_mutex pthread_mutex_init.\n"));
		}
		i++;
	}
	if (pthread_mutex_init(&data->printing, NULL))
	{
		free(data->fork);
		return (print_error("Error: init_mutex: pthread_mutex_init.\n"));
	}
	if (!init_mutex2(data))
		return (0);
	return (1);
}
