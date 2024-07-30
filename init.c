/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 01:22:45 by hboudar           #+#    #+#             */
/*   Updated: 2024/07/30 16:27:23 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	initialize_philos(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philos)
	{
		table->philos[i].id = i + 1;
		table->philos[i].last_meal_time = time_in_ms();
		table->philos[i].meals_eaten = 0;
		table->philos[i].table = table;
		if (pthread_create(&table->philos[i].thread, NULL,
				philosopher_routine, &table->philos[i]) != 0)
			perror("Failed to create thread");
		i++;
	}
}

void	initialize_forks(t_table *table)
{
	int	i;

	i = 0;
	table->forks = malloc(sizeof(pthread_mutex_t) * table->num_philos);
	if (!table->forks)
	{
		perror("Failed to allocate memory for forks");
		exit(EXIT_FAILURE);
	}
	while (i < table->num_philos)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
		{
			perror("Failed to initialize mutex");
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void	initialize_table(t_table *table, int argc, char **argv)
{
	table->meals_required = -1;
	if (argc == 6)
		(1) && (argc = 0, table->meals_required = ft_atoi(argv[5], &argc));
	(1) && (argc = 0, table->num_philos = ft_atoi(argv[1], &argc));
	(1) && (argc = 0, table->time_to_die = ft_atoi(argv[2], &argc));
	(1) && (argc = 0, table->time_to_eat = ft_atoi(argv[3], &argc));
	(1) && (argc = 0, table->time_to_sleep = ft_atoi(argv[4], &argc));
	table->simulation_running = 1;
	table->philos = malloc(sizeof(t_philosopher) * table->num_philos);
	if (!table->philos)
	{
		perror("Failed to allocate memory for philos");
		exit(EXIT_FAILURE);
	}
	if (pthread_mutex_init(&table->print_lock, NULL) != 0)
	{
		perror("Failed to initialize print mutex");
		exit(EXIT_FAILURE);
	}
	table->start_time = time_in_ms();
	initialize_forks(table);
	initialize_philos(table);
}
