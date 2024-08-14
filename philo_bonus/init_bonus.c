/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 10:27:15 by hboudar           #+#    #+#             */
/*   Updated: 2024/08/14 10:57:04 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	initialize_semaphores(t_table *table)
{
	table->forks = sem_open("forks", O_CREAT, 0644, table->num_philos);
	if (table->forks == SEM_FAILED)
		ft_error("Error: sem_open failed\n");
	table->meals_lock = sem_open("meals", O_CREAT, 0644, 1);
	if (table->meals_lock == SEM_FAILED)
	{
		(1) && (sem_close(table->meals_lock), sem_unlink("forks"));
		ft_error("Error: sem_open failed\n");
	}
	table->print_lock = sem_open("print", O_CREAT, 0644, 1);
	if (table->print_lock == SEM_FAILED)
	{
		(1) && (sem_close(table->forks), sem_unlink("forks"));
		(1) && (sem_close(table->meals_lock), sem_unlink("meals"));
		ft_error("Error: sem_open failed\n");
	}
	table->death_lock = sem_open("death", O_CREAT, 0644, 1);
	if (table->death_lock == SEM_FAILED)
	{
		(1) && (sem_close(table->forks), sem_unlink("forks"));
		(1) && (sem_close(table->print_lock), sem_unlink("print"));
		(1) && (sem_close(table->meals_lock), sem_unlink("meals"));
		ft_error("Error: sem_open failed\n");
	}
}

void	initialize_table(t_table *table, int argc, char **argv)
{
	table->num_philos = ft_atoi(argv[1], 0);
	if (table->num_philos < 1)
		ft_error("Error: invalid number of philosophers\n");
	table->time_to_die = ft_atoi(argv[2], 0);
	if (table->time_to_die < 1)
		ft_error("Error: time to die must be at least 60ms\n");
	table->time_to_eat = ft_atoi(argv[3], 0);
	if (table->time_to_eat < 1)
		ft_error("Error: time to eat must be at least 60ms\n");
	table->time_to_sleep = ft_atoi(argv[4], 0);
	if (table->time_to_sleep < 1)
		ft_error("Error: time to sleep must be at least 60ms\n");
	table->meals_to_eat = -1;
	if (argc == 6)
		table->meals_to_eat = ft_atoi(argv[5], 0);
	if (table->meals_to_eat < 1 && argc == 6)
		ft_error("Error: invalid number of meals\n");
	sem_unlink("forks");
	sem_unlink("meals");
	sem_unlink("print");
	sem_unlink("death");
	initialize_semaphores(table);
}
