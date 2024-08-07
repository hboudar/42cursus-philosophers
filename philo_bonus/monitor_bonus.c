/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 10:42:22 by hboudar           #+#    #+#             */
/*   Updated: 2024/08/07 18:03:41 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <stdio.h>

static int	check_meals_eaten(t_philo *philo)
{
	if (philo->meals < philo->table->meals_required)
		return (0);
	return (1);
}

void	*monitor_routine(void *arg)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)arg;
	table = philo->table;
	ft_usleep(table->time_to_die);
	while (1)
	{
		sem_wait(table->death_lock);
		if (table->meals_required != -1 && check_meals_eaten(philo))
		{
			sem_post(table->death_lock);
			exit(EXIT_SUCCESS);
		}
		sem_post(table->death_lock);
		if (time_in_ms() - philo->last_meal >= table->time_to_die)
		{
			sem_wait(table->print_lock);
			printf("%ld %i died\n",
				time_in_ms() - table->start_time, philo->id);
			exit(EXIT_FAILURE);
		}
		usleep(100);
	}
	exit (EXIT_SUCCESS);
}
