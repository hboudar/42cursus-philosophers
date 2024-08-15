/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 10:27:03 by hboudar           #+#    #+#             */
/*   Updated: 2024/08/15 11:20:29 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_died(t_table *table, int id)
{
	pthread_mutex_unlock(&table->eat_lock);
	pthread_mutex_lock(&table->print_lock);
	printf("%lld %d %s\n", time_in_ms() - table->start_time, id, "died");
}

int	check_time_to_die(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philos)
	{
		pthread_mutex_lock(&table->eat_lock);
		if (time_in_ms() - table->philo[i].last_meal >= table->time_to_die)
		{
			philo_died(table, table->philo[i].id);
			return (1);
		}
		pthread_mutex_unlock(&table->eat_lock);
		i++;
	}
	return (0);
}

int	check_meals_eaten(t_table *table)
{
	int	i;

	i = 0;
	if (table->meals_required == -1)
		return (0);
	while (i < table->num_philos)
	{
		if (table->philo[i].meals_eaten >= table->meals_required
			&& !table->philo[i].full)
		{
			table->philo[i].full = 1;
			table->philos_full++;
		}
		if (table->philos_full == table->num_philos)
		{
			pthread_mutex_lock(&table->print_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

int	monitor_routine(void *arg)
{
	t_table	*table;

	table = (t_table *)arg;
	while (1)
	{
		if (check_time_to_die(table))
			return (1);
		else if (check_meals_eaten(table))
			return (1);
	}
}
