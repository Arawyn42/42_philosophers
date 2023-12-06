/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 23:14:58 by drenassi          #+#    #+#             */
/*   Updated: 2023/12/05 23:15:30 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/**************** Gets time since EPOCH (1970) in milliseconds ****************/
long long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

/************ Gets the time passed since 'time' (in milliseconds) *************/
long long	get_time_since(long long time)
{
	if (time > 0)
		return (get_time() - time);
	return (0);
}

/******************** Sleeps for 'time' (in milliseconds) *********************/
void	wait_time(long long time)
{
	usleep(time * 1000);
}
