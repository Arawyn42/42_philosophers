/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 20:04:13 by drenassi          #+#    #+#             */
/*   Updated: 2023/12/24 13:31:57 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

/********************** If there is only one philosopher **********************/
static void	only_one_philo(t_data *data)
{
	printf("%lld\t%d has taken a fork\n", get_time_from(data->start_time), 1);
	usleep(data->time_to_die * 1000);
	printf("%lld\t%d has died\n", get_time_from(data->start_time), 1);
}

static void	*wait_for_death(void *arg)
{
	t_philo	*philo;
	t_data	*data;
	int		i;

	philo = (t_philo *)arg;
	data = philo->data;
	i = -1;
	sem_wait(data->finished);
	if (data->wanted_meals != -1)
	{
		while (++i < philo->data->num_of_philos)
			sem_post(data->all_eat);
		i = -1;
	}
	while (++i < philo->data->num_of_philos)
		kill(philo[i].pid, SIGKILL);
	return (NULL);
}

static void	*wait_all_ate(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	i = 0;
	while (i < data->num_of_philos)
	{
		sem_wait(data->all_eat);
		i++;
	}
	sem_post(data->finished);
	return (NULL);
}

/******************************* Main function ********************************/
int	main(int ac, char **av)
{
	t_data		data;
	t_philo		*philo;
	pthread_t	thread1;
	pthread_t	thread2;

	if (!check_args(ac, av))
		return (-1);
	init_data(ac, av, &data);
	philo = malloc(data.num_of_philos * sizeof(t_philo));
	if (!philo)
		return (-1);
	init_philos(&data, philo);
	if (data.num_of_philos == 1)
		return (only_one_philo(&data), free(philo), 0);
	init_semaphores(&data);
	init_processes(&data, philo);
	if (data.wanted_meals != -1)
		pthread_create(&thread1, NULL, wait_all_ate, &data);
	pthread_create(&thread2, NULL, wait_for_death, philo);
	if (data.wanted_meals != -1)
		pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	destroy_semaphores(&data, philo);
	free(philo);
	return (0);
}
