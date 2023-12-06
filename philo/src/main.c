/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 20:04:13 by drenassi          #+#    #+#             */
/*   Updated: 2023/12/05 22:24:09 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	unlock_forks(t_p *p)
{
	int	i;

	i = 0;
	while (i < p->num_of_philos)
	{
		pthread_mutex_unlock(&p->fork[i]);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_p	p;

	if (!init(ac, av, &p))
		return (1);
	
	
	return (0);
}
