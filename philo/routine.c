/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 01:25:54 by hboudar           #+#    #+#             */
/*   Updated: 2024/08/07 11:40:10 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_meals_eaten(t_table *table)
{
	int	i;

	i = 0;
	if (table->meals_required == -1)
		return (0);
	while (i < table->num_philos)
	{
		if (table->philos[i].meals_eaten < table->meals_required)
			return (0);
		i++;
	}
	return (1);
}

void	sleep_and_think(t_philosopher *philo)
{
	t_table	*table;

	table = philo->table;
	print_status(table, philo->id, "is sleeping");
	ft_usleep(table->time_to_sleep);
	print_status(table, philo->id, "is thinking");
}

void	eat(t_philosopher *philo)
{
	t_table	*table;

	table = philo->table;
	philo->left_fork = philo->id - 1;
	philo->right_fork = (philo->id) % table->num_philos;
	pthread_mutex_lock(&table->forks[philo->left_fork]);
	print_status(table, philo->id, "has taken a fork");
	pthread_mutex_lock(&table->forks[philo->right_fork]);
	print_status(table, philo->id, "has taken a fork");
	print_status(table, philo->id, "is eating");
	philo->last_meal = time_in_ms();
	ft_usleep(table->time_to_eat);
	philo->meals_eaten++;
	pthread_mutex_unlock(&table->forks[philo->right_fork]);
	pthread_mutex_unlock(&table->forks[philo->left_fork]);
}

void	*philosopher_routine(void *arg)
{
	t_philosopher	*philo;
	t_table			*table;

	philo = (t_philosopher *)arg;
	table = philo->table;
	if (philo->id % 2 == 0)
		usleep(table->time_to_eat);
	while (table->simulation_running)
	{
		eat(philo);
		sleep_and_think(philo);
	}
	return (NULL);
}
