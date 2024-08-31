/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 10:27:03 by hboudar           #+#    #+#             */
/*   Updated: 2024/08/31 19:25:40 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_died(t_table *table, int id)
{
	pthread_mutex_lock(&table->print_lock);
	printf("%lld %d %s\n", time_in_ms() - table->start_time, id, "died");
	pthread_mutex_unlock(&table->print_lock);
}

int	check_time_to_die(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philos)
	{
		pthread_mutex_lock(&table->lock);
		if (time_in_ms() - table->philo[i].last_meal >= table->time_to_die)
		{
			table->running = 0;
			pthread_mutex_unlock(&table->lock);
			philo_died(table, table->philo[i].id);
			return (1);
		}
		pthread_mutex_unlock(&table->lock);
		i++;
	}
	return (0);
}

int	check_meals_eaten(t_table *table)
{
	int	i;

	i = 0;
	if (table->meals_required == -2)
		return (0);
	while (i < table->num_philos)
	{
		pthread_mutex_lock(&table->lock);
		if (table->philo[i].meals_eaten >= table->meals_required
			&& !table->philo[i].full)
		{
			table->philo[i].full = 1;
			table->philos_full++;
		}
		pthread_mutex_unlock(&table->lock);
		if (table->philos_full == table->num_philos)
		{
			pthread_mutex_lock(&table->print_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

void	monitor(void *arg)
{
	t_table	*table;

	table = (t_table *)arg;
	while (1)
	{
		if (check_time_to_die(table) || check_meals_eaten(table))
			break ;
	}
	cleanup_table(table);
}
