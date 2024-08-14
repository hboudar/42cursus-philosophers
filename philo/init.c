/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 01:22:45 by hboudar           #+#    #+#             */
/*   Updated: 2024/08/14 10:30:17 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	initialize_philos(t_table *table)
{
	int	i;

	i = -1;
	table->start_time = time_in_ms();
	while (++i < table->num_philos)
	{
		table->philo[i].full = 0;
		table->philo[i].id = i + 1;
		table->philo[i].table = table;
		table->philo[i].meals_eaten = 0;
		table->philo[i].last_meal = time_in_ms();
		table->philo[i].left_fork = table->philo[i].id - 1;
		table->philo[i].right_fork = table->philo[i].id % table->num_philos;
		if (pthread_create(&table->philo[i].thread, NULL,
				philosopher_routine, &table->philo[i]) != 0)
		{
			pthread_mutex_lock(&table->print_lock);
			ft_error("Error creating philoopher thread\n");
		}
	}
}

static void	initialize_forks(t_table *table)
{
	int	i;

	i = 0;
	table->forks = malloc(sizeof(pthread_mutex_t) * table->num_philos);
	if (!table->forks)
		ft_error("Failed to allocate memory for forks\n");
	while (i < table->num_philos)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
		{
			pthread_mutex_lock(&table->print_lock);
			ft_error("Failed to initialize mutex\n");
		}
		i++;
	}
}

void	initialize_table(t_table *table, int argc, char **argv)
{
	table->num_philos = ft_atoi(argv[1], 0);
	table->time_to_die = ft_atoi(argv[2], 0);
	table->time_to_eat = ft_atoi(argv[3], 0);
	table->time_to_sleep = ft_atoi(argv[4], 0);
	table->meals_required = -1;
	if (argc == 6)
		table->meals_required = ft_atoi(argv[5], 0);
	check_args(table, argc);
	table->philos_full = 0;
	table->philo = malloc(sizeof(t_philo) * table->num_philos);
	if (!table->philo)
		ft_error("Failed to allocate memory for philosophers\n");
	if (pthread_mutex_init(&table->print_lock, NULL) != 0)
		ft_error("Failed to initialize mutex\n");
	if (pthread_mutex_init(&table->eat_lock, NULL) != 0)
		ft_error("Failed to initialize mutex\n");
	initialize_forks(table);
	initialize_philos(table);
	detaching_philos(table);
}
