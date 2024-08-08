/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 10:42:22 by hboudar           #+#    #+#             */
/*   Updated: 2024/08/08 10:52:12 by hboudar          ###   ########.fr       */
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
	while (1)
	{
		sem_wait(table->death_lock);
		if (table->meals_required != -1 && check_meals_eaten(philo))
		{
			sem_post(table->death_lock);
			break ;
		}
		sem_post(table->death_lock);
		if (time_in_ms() - philo->last_meal >= table->time_to_die)
		{
			sem_wait(table->print_lock);
			printf("%llu %i died\n",
				time_in_ms() - table->start_time, philo->id);
			exit(EXIT_FAILURE);
		}
	}
	return (NULL);
}
