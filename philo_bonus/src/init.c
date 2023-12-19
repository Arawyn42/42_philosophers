/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 21:30:04 by drenassi          #+#    #+#             */
/*   Updated: 2023/12/20 00:07:40 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

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
}

/************************ Initialize philos structure *************************/
void	init_philos(t_data *data, t_philo *philo)
{
	int	i;

	data->start_time = get_time();
	i = 0;
	while (i < data->num_of_philos)
	{
		memset(&philo[i], 0, sizeof(t_philo));
		philo[i].data = data;
		philo[i].id = i + 1;
		philo[i].meals = 0;
		philo[i].last_meal = data->start_time;
		philo[i].pid = -2;
		i++;
	}
}

void	init_semaphores(t_data *data)
{
	data->forks = NULL;
	data->print = NULL;
	data->death = NULL;
	data->finished = NULL;
	sem_unlink("/forks");
	sem_unlink("/print");
	sem_unlink("/death");
	sem_unlink("/finished");
	data->forks = sem_open("/forks", O_CREAT, 0600, data->num_of_philos);
	data->print = sem_open("/print", O_CREAT, 0600, 1);
	data->death = sem_open("/death", O_CREAT, 0600, 1);
	data->finished = sem_open("/finished", O_CREAT, 0600, 1);
}

void	init_processes(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		philo[i].pid = fork();
		if (!philo[i].pid)
		{
			routine(&philo[i]);
			exit(EXIT_SUCCESS);
		}
		i++;
		usleep(50);
	}
}
