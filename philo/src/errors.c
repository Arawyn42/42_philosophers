/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 22:10:48 by drenassi          #+#    #+#             */
/*   Updated: 2023/12/07 19:40:04 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/***************** Print an error message on the error output *****************/
int	print_error(char *msg)
{
	int	i;

	i = 0;
	while (msg[i])
	{
		write(STDERR_FILENO, &msg[i], 1);
		i++;
	}
	return (0);
}

/************ Prints an error message in case of invalid arguments ************/
static int	print_args_error()
{
	print_error("Error: Invalid arguments.\n\nUsage: ./philo ");
	print_error("number_of_philosophers time_to_die time_to_eat time_to");
	print_error("_sleep [number_of_times_each_philosopher_must_eat]\n\n");
	print_error("(Time in milliseconds)\n");
	return (0);
}

/** Checks if there is a correct number of arguments and if they are valids ***/
int	check_args(int ac, char **av)
{
	int	i;
	int	j;

	if (ac != 5 && ac != 6)
		return (print_args_error());
	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				return (print_args_error());
			j++;
		}
		i++;
	}
	return (1);
}
