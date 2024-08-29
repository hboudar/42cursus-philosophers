/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 10:00:23 by hboudar           #+#    #+#             */
/*   Updated: 2024/08/29 11:08:34 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	ft_routine(t_table *table, t_philo *philo)
{
	sem_wait(table->forks);
	sem_wait(table->forks);
	print_status(philo, "has taken a fork");
	print_status(philo, "has taken a fork");
	print_status(philo, "is eating");
	sem_wait(table->meals_lock);
	philo->last_meal = time_in_ms();
	philo->meals_eaten++;
	sem_post(table->meals_lock);
	ft_usleep(table->time_to_eat);
	sem_post(table->forks);
	sem_post(table->forks);
	print_status(philo, "is sleeping");
	ft_usleep(table->time_to_sleep);
	print_status(philo, "is thinking");
}

static void	philo_life(t_table *table, t_philo *philo)
{
	pthread_t	monitor;

	if (pthread_create(&monitor, NULL, monitor_routine, philo))
		ft_error("Error: pthread_create failed\n");
	if (pthread_detach(monitor))
		ft_error("Error: pthread_detach failed\n");
	while (table->meals_to_eat == -1
		|| philo->meals_eaten < table->meals_to_eat)
		ft_routine(table, philo);
	exit(EXIT_SUCCESS);
}

void	start_simulation(t_table *table)
{
	pid_t	*pid;
	int		i;

	(1) && (i = -1, pid = malloc(sizeof(pid_t) * table->num_philos));
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
			(1) && (table->philo[i].id = i + 1, table->philo[i].table = table);
			table->philo[i].start_time = time_in_ms();
			table->philo[i].last_meal = time_in_ms();
			table->philo[i].meals_eaten = 0;
			philo_life(table, &table->philo[i]);
		}
	}
	wait_pids(pid, table->num_philos);
	free(pid);
}
