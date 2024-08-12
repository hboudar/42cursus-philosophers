/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 01:25:54 by hboudar           #+#    #+#             */
/*   Updated: 2024/08/12 10:05:58 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	sleep_and_think(t_philosopher *philo)
{
	t_table	*table;

	table = philo->table;
	print_status(table, philo->id, "is sleeping");
	ft_usleep(table->time_to_sleep);
	print_status(table, philo->id, "is thinking");
}

static void	eat(t_philosopher *philo)
{
	t_table	*table;

	table = philo->table;
	pthread_mutex_lock(&table->forks[philo->left_fork]);
	print_status(table, philo->id, "has taken a fork");
	pthread_mutex_lock(&table->forks[philo->right_fork]);
	print_status(table, philo->id, "has taken a fork");
	print_status(table, philo->id, "is eating");
	pthread_mutex_lock(&table->eat_lock);
	philo->last_meal = time_in_ms();
	philo->meals_eaten++;
	pthread_mutex_unlock(&table->eat_lock);
	ft_usleep(table->time_to_eat);
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
		ft_usleep(table->time_to_eat / 2);
	while (1)
	{
		eat(philo);
		sleep_and_think(philo);
	}
	return (NULL);
}
