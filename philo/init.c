/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 01:22:45 by hboudar           #+#    #+#             */
/*   Updated: 2024/08/05 10:32:59 by hboudar          ###   ########.fr       */
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
			ft_error("Error creating philosopher thread\n");
		i++;
	}
}

void	initialize_forks(t_table *table)
{
	int	i;

	i = 0;
	table->forks = malloc(sizeof(pthread_mutex_t) * table->num_philos);
	if (!table->forks)
		ft_error("Failed to allocate memory for forks\n");
	while (i < table->num_philos)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
			ft_error("Failed to initialize mutex\n");
		i++;
	}
}

void	initialize_table(t_table *table, int argc, char **argv)
{
	table->simulation_running = 1;
	table->num_philos = ft_atoi(argv[1], 0);
	table->time_to_die = ft_atoi(argv[2], 0);
	table->time_to_eat = ft_atoi(argv[3], 0);
	table->time_to_sleep = ft_atoi(argv[4], 0);
	table->meals_required = -1;
	if (argc == 6)
		table->meals_required = ft_atoi(argv[5], 0);
	check_args(table, argc);
	table->philos = malloc(sizeof(t_philosopher) * table->num_philos);
	if (!table->philos)
		ft_error("Failed to allocate memory for philosophers\n");
	if (pthread_mutex_init(&table->print_lock, NULL) != 0)
		ft_error("Failed to initialize mutex\n");
	table->start_time = time_in_ms();
	initialize_forks(table);
	initialize_philos(table);
}
