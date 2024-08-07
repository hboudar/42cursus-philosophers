/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 10:27:03 by hboudar           #+#    #+#             */
/*   Updated: 2024/08/07 11:39:38 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_died(t_table *table, int id)
{
	table->simulation_running = 0;
	pthread_mutex_lock(&table->print_lock);
	printf("%ld %d %s\n", time_in_ms() - table->start_time, id, "died");
	pthread_mutex_unlock(&table->print_lock);
}

int	monitor_routine(void *arg)
{
	t_table	*table;
	int		i;

	(1) && (table = (t_table *)arg, i = 0);
	while (table->simulation_running)
	{
		while (i < table->num_philos)
		{
			if (time_in_ms() - table->philos[i].last_meal >= table->time_to_die)
			{
				philo_died(table, i + 1);
				return (1);
			}
			else if (check_meals_eaten(table))
			{
				table->simulation_running = 0;
				return (1);
			}
		}
		i++;
	}
	return (0);
}
