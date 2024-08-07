/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 10:27:15 by hboudar           #+#    #+#             */
/*   Updated: 2024/08/07 11:02:43 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	initialize_philosophers(t_table *table)
{
	pid_t	*pid;
	int		i;

	(1) && (i = -1, pid = malloc(sizeof(pid_t) * table->num_philos));
	if (!pid)
		ft_error("Error: malloc failed\n");
	table->philos = malloc(sizeof(t_philo) * table->num_philos);
	if (!table->philos)
		ft_error("Error: malloc failed\n");
	while (++i < table->num_philos)
	{
		philo_init(table, &table->philos[i], i + 1);
		pid[i] = fork();
		if (pid[i] == -1)
			ft_error("Error: fork failed\n");
		if (pid[i] == 0)
		{
			philo_life(&table->philos[i]);
			exit(0);
		}
	}
	i = -1;
	while (++i < table->num_philos)
		waitpid(pid[i], NULL, 0);
}

void	initialize_semaphores(t_table *table)
{
	sem_unlink("forks");
	sem_unlink("print_lock");
	sem_unlink("death_lock");
	table->forks = sem_open("forks", O_CREAT, 0644, table->num_philos);
	if (table->forks == SEM_FAILED)
		ft_error("Error: sem_open failed\n");
	table->print_lock = sem_open("print_lock", O_CREAT, 0644, 1);
	if (table->print_lock == SEM_FAILED)
	{
		sem_close(table->forks);
		sem_unlink("forks");
		ft_error("Error: sem_open failed\n");
	}
	table->death_lock = sem_open("death_lock", O_CREAT, 0644, 1);
	if (table->death_lock == SEM_FAILED)
	{
		sem_close(table->forks);
		sem_close(table->print_lock);
		sem_unlink("forks");
		sem_unlink("print_lock");
		ft_error("Error: sem_open failed\n");
	}
}

void    initialize_table(t_table *table, int argc, char **argv)
{
	table->num_philos = ft_atoi(argv[1], 0);
	table->time_to_die = ft_atoi(argv[2], 0);
	table->time_to_eat = ft_atoi(argv[3], 0);
	table->time_to_sleep = ft_atoi(argv[4], 0);
	table->meals_required = -1;
	if (argc == 6)
		table->meals_required = ft_atoi(argv[5], 0);
	check_args(argc, table);
	table->simulation_running = 1;
	initialize_semaphores(table);
	initialize_philosophers(table);
}
