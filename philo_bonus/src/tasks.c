/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tasks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 18:02:36 by drenassi          #+#    #+#             */
/*   Updated: 2023/12/21 20:25:54 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

static void	set_color(t_philo *philo)
{
	if (philo->id % 7 == 1)
		printf("\033[0;31m");
	else if (philo->id % 7 == 2)
		printf("\033[0;32m");
	else if (philo->id % 7 == 3)
		printf("\033[0;33m");
	else if (philo->id % 7 == 4)
		printf("\033[0;34m");
	else if (philo->id % 7 == 5)
		printf("\033[0;35m");
	else if (philo->id % 7 == 6)
		printf("\033[0;36m");
	else if (philo->id % 7 == 0)
		printf("\033[0;37m");
}

/************************ Print a task in the terminal ************************/
void	print_task(t_philo *philo, char *msg)
{
	t_data			*data;
	long long		time;

	data = philo->data;
	sem_wait(data->print);
	time = get_time_from(data->start_time);
	printf("%lld\t", time);
	set_color(philo);
	printf("%d %s", philo->id, msg);
	printf("\033[0;37m\n\033[0m");
	sem_post(data->print);
}

/********************************** Eat task **********************************/
void	p_eat(t_philo *philo, t_data *data)
{
	sem_wait(data->forks);
	print_task(philo, "has taken a fork");
	sem_wait(data->forks);
	print_task(philo, "has taken a fork");
	print_task(philo, "is eating");
	sem_wait(data->death);
	philo->meals++;
	philo->last_meal = get_time();
	sem_post(data->death);
	wait_time(data->time_to_eat);
	sem_post(data->forks);
	sem_post(data->forks);
}

/********************************* Sleep task *********************************/
void	p_sleep(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	print_task(philo, "is sleeping");
	wait_time(data->time_to_sleep);
}
