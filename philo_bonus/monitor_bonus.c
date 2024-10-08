/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 10:42:22 by hboudar           #+#    #+#             */
/*   Updated: 2024/08/28 14:24:05 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*monitor_routine(void *arg)
{
	t_philo	*philo;
	t_table	*table;

	(1) && (philo = (t_philo *)arg, table = philo->table);
	while (1)
	{
		sem_wait(table->meals_lock);
		if (time_in_ms() - philo->last_meal >= table->time_to_die)
		{
			sem_post(table->meals_lock);
			sem_wait(table->print_lock);
			printf("%llu %i died\n",
				time_in_ms() - philo->start_time, philo->id);
			exit(EXIT_FAILURE);
		}
		sem_post(table->meals_lock);
	}
	return (NULL);
}
