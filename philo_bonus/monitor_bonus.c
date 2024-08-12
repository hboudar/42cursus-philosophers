/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 10:42:22 by hboudar           #+#    #+#             */
/*   Updated: 2024/08/12 14:27:50 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*monitor_routine(void *arg)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)arg;
	table = philo->table;
	while (1)
	{
		sem_wait(table->death_lock);
		if (table->meals_required != -1
			&& philo->meals_eaten >= table->meals_required)
			break ;
		sem_post(table->death_lock);
		if (time_in_ms() - philo->last_meal >= table->time_to_die)
		{
			sem_wait(table->print_lock);
			printf("%llu %i died\n",
				time_in_ms() - table->start_time, philo->id);
				philo->died = 1;
			exit(EXIT_FAILURE);
		}
	}
	sem_post(table->death_lock);
	return (NULL);
}
