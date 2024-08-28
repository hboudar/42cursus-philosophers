/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 01:25:54 by hboudar           #+#    #+#             */
/*   Updated: 2024/08/26 16:44:37 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	detaching_philos(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->num_philos)
	{
		if (pthread_detach(table->philo[i].thread))
		{
			pthread_mutex_lock(&table->print_lock);
			ft_putstr_fd("Error detaching philosopher thread\n", 2);
			free(table->philo);
			return (destroy_resources(table, 3));
		}
	}
	return (0);
}

static void	ft_sleep(t_table *table, t_philo *philo)
{
	print_status(table, philo->id, "is sleeping");
	ft_usleep(table->time_to_sleep);
}

static void	eat(t_philo *philo)
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
	pthread_mutex_unlock(&table->eat_lock);
	ft_usleep(table->time_to_eat);
	pthread_mutex_lock(&table->eat_lock);
	philo->meals_eaten++;
	pthread_mutex_unlock(&table->eat_lock);
	pthread_mutex_unlock(&table->forks[philo->right_fork]);
	pthread_mutex_unlock(&table->forks[philo->left_fork]);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)arg;
	table = philo->table;
	if (philo->id % 2 == 0)
		ft_usleep(table->time_to_eat / 2);
	while (1)
	{
		eat(philo);
		ft_sleep(table, philo);
		print_status(table, philo->id, "is thinking");
	}
	return (NULL);
}
