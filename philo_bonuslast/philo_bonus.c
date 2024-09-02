/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 10:00:23 by hboudar           #+#    #+#             */
/*   Updated: 2024/08/29 13:20:14 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	ft_routine(t_table *table, t_philo *philo)
{
	sem_wait(table->forks);
	sem_wait(table->forks);
	print_status(philo, table, "has taken a fork");
	print_status(philo, table, "has taken a fork");
	print_status(philo, table, "is eating");
	sem_wait(table->meals_lock);
	philo->last_meal = time_in_ms();
	philo->meals_to_eat--;
	if (!philo->meals_to_eat)
		philo->running = 0;
	sem_post(table->meals_lock);
	ft_usleep(table->time_to_eat);
	sem_post(table->forks);
	sem_post(table->forks);
	print_status(philo, table, "is sleeping");
	ft_usleep(table->time_to_sleep);
	print_status(philo, table, "is thinking");
}

static void	philo_life(t_table *table, t_philo *philo, int i)
{
	pthread_t	thread;

	if (pthread_create(&thread, NULL, monitor, philo))
		ft_error("Error: pthread_create failed\n");
	if (pthread_detach(thread))
		ft_error("Error: pthread_detach failed\n");
	if (i % 2)
		ft_usleep(table->time_to_eat / 2);
	while (philo->running)
		ft_routine(table, philo);
	exit (EXIT_SUCCESS);
}

void	start_simulation(t_table *table, int i)
{
	pid_t	*pid;

	(1) && (pid = malloc(sizeof(pid_t) * table->num_philos));
	if (!pid)
		ft_error("Error: malloc failed\n");
	table->philo = malloc(sizeof(t_philo) * table->num_philos);
	if (!table->philo)
		ft_error("Error: malloc failed\n");
	while (++i < table->num_philos)
	{
		pid[i] = fork();
		if (pid[i] == -1)
			ft_error("Error: fork failed\n");
		else if (!pid[i])
		{
			table->philo[i].meals_to_eat = table->meals_to_eat;
			table->philo[i].start_time = time_in_ms();
			table->philo[i].last_meal = table->philo[i].start_time;
			table->philo[i].table = table;
			(1) && (table->philo[i].id = i + 1, table->philo[i].running = 1);
			philo_life(table, &table->philo[i], i + 1);
		}
	}
	wait_pids(pid, table->num_philos);
	free(pid);
}
