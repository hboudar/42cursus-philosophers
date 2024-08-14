/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 10:27:03 by hboudar           #+#    #+#             */
/*   Updated: 2024/08/13 11:39:03 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_died(t_table *table, int id)
{
	pthread_mutex_unlock(&table->eat_lock);
	pthread_mutex_lock(&table->print_lock);
	printf("%lld %d %s\n", time_in_ms() - table->start_time, id, "died");
}

static int	check_meals_eaten(t_philo *philo)
{
	if (philo->table->meals_required == -1)
		return (0);
	else if (philo->meals_eaten >= philo->table->meals_required && !philo->full)
	{
		philo->full = 1;
		philo->table->philos_full++;
	}
	if (philo->table->philos_full == philo->table->num_philos)
	{
		pthread_mutex_unlock(&philo->table->eat_lock);
		pthread_mutex_lock(&philo->table->print_lock);
		return (1);
	}
	return (0);
}

int	monitor_routine(void *arg)
{
	t_table	*table;
	int		i;

	(1) && (table = (t_table *)arg);
	while (1)
	{
		i = 0;
		while (i < table->num_philos)
		{
			pthread_mutex_lock(&table->eat_lock);
			if (time_in_ms() - table->philo[i].last_meal >= table->time_to_die)
			{
				philo_died(table, i + 1);
				return (1);
			}
			else if (check_meals_eaten(&table->philo[i]))
				return (1);
			pthread_mutex_unlock(&table->eat_lock);
			i++;
		}
	}
	return (0);
}
