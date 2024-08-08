/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 10:00:23 by hboudar           #+#    #+#             */
/*   Updated: 2024/08/08 10:40:14 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	ft_sleep(t_philo *philo)
{
	print_status(philo, "is sleeping");
	ft_usleep(philo->table->time_to_sleep);
}

static void	ft_eat(t_philo *philo)
{
	sem_wait(philo->table->forks);
	sem_wait(philo->table->forks);
	print_status(philo, "has taken a fork");
	print_status(philo, "has taken a fork");
	print_status(philo, "is eating");
	ft_usleep(philo->table->time_to_eat);
	philo->last_meal = time_in_ms();
	philo->meals++;
	sem_post(philo->table->forks);
	sem_post(philo->table->forks);
}

static int	philo_life(void *arg)
{
	t_table		*table;
	t_philo		*philo;
	pthread_t	monitor;

	philo = (t_philo *)arg;
	table = philo->table;
	if (pthread_create(&monitor, NULL, monitor_routine, philo))
		ft_error("Error: pthread_create failed\n");
	if (pthread_detach(monitor))
		ft_error("Error: pthread_detach failed\n");
	while (1)
	{
		if (philo->meals == table->meals_required)
			return (EXIT_SUCCESS);
		ft_eat(philo);
		ft_sleep(philo);
		print_status(philo, "is thinking");
	}
	return (EXIT_FAILURE);
}

static void	philo_init(t_table *table, t_philo *philo, int i)
{
	philo->id = i;
	philo->meals = 0;
	philo->is_dead = 0;
	philo->table = table;
	philo->last_meal = time_in_ms();
	table->start_time = time_in_ms();
}

void	start_simulation(t_table *table)
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
		pid[i] = fork();
		if (pid[i] == -1)
			ft_error("Error: fork failed\n");
		if (!pid[i])
		{
			philo_init(table, &table->philos[i], i + 1);
			philo_life(&table->philos[i]);
			exit (EXIT_SUCCESS);
		}
	}
	wait_pids(pid, table->num_philos);
}
