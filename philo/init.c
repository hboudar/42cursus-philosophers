/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 01:22:45 by hboudar           #+#    #+#             */
/*   Updated: 2024/08/26 11:53:25 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philos(t_table *table, int i)
{
	table->philo = malloc(sizeof(t_philo) * table->num_philos);
	if (!table->philo)
	{
		ft_putstr_fd("Failed to allocate memory for philosophers\n", 2);
		return (destroy_resources(table, 3));
	}
	table->start_time = time_in_ms();
	while (++i < table->num_philos)
	{
		(1) && (table->philo[i].full = 0, table->philo[i].meals_eaten = 0);
		(1) && (table->philo[i].id = i + 1, table->philo[i].table = table);
		table->philo[i].last_meal = time_in_ms();
		table->philo[i].left_fork = table->philo[i].id - 1;
		table->philo[i].right_fork = table->philo[i].id % table->num_philos;
		if (pthread_create(&table->philo[i].thread, NULL,
				philo_routine, &table->philo[i]))
		{
			(1) && (free(table->philo), pthread_mutex_lock(&table->print_lock));
			ft_putstr_fd("Error creating philosopher thread\n", 2);
			return (destroy_resources(table, 3));
		}
	}
	if (detaching_philos(table))
		return (1);
	return (0);
}

int	init_forks(t_table *table, int i)
{
	if (pthread_mutex_init(&table->print_lock, NULL))
		return (ft_putstr_fd("Failed to initialize mutex\n", 2));
	if (pthread_mutex_init(&table->eat_lock, NULL))
		return (destroy_resources(table, 0));
	table->forks = malloc(sizeof(pthread_mutex_t) * table->num_philos);
	if (!table->forks)
		return (destroy_resources(table, 1));
	while (i < table->num_philos)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
		{
			while (i > 0)
			{
				pthread_mutex_destroy(&table->forks[i - 1]);
				i--;
			}
			return (destroy_resources(table, 2));
		}
		i++;
	}
	return (0);
}

int	init_args(t_table *table, int argc, char *argv[])
{
	table->philos_full = 0;
	table->num_philos = ft_atoi(argv[1], 0);
	if (table->num_philos < 1)
		return (ft_putstr_fd("Invalid number of philosophers\n", 2));
	table->time_to_die = ft_atoi(argv[2], 0);
	if (table->time_to_die < 1)
		return (ft_putstr_fd("Invalid time values\n", 2));
	table->time_to_eat = ft_atoi(argv[3], 0);
	if (table->time_to_eat < 1)
		return (ft_putstr_fd("Invalid time values\n", 2));
	table->time_to_sleep = ft_atoi(argv[4], 0);
	if (table->time_to_sleep < 1)
		return (ft_putstr_fd("Invalid time values\n", 2));
	table->meals_required = -2;
	if (argc == 6)
		table->meals_required = ft_atoi(argv[5], 0);
	if (table->meals_required < 1 && table->meals_required != -2)
		return (ft_putstr_fd("Invalid number of meals\n", 2));
	return (0);
}
