/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 01:25:54 by hboudar           #+#    #+#             */
/*   Updated: 2024/09/05 10:36:15 by hboudar          ###   ########.fr       */
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

void	print_status(t_table *table, int id, const char *status)
{
	pthread_mutex_lock(&table->print_lock);
	printf("%lld %d %s\n", time_in_ms() - table->start_time, id, status);
	pthread_mutex_unlock(&table->print_lock);
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
	pthread_mutex_lock(&table->lock);
	philo->last_meal = time_in_ms();
	philo->meals_eaten++;
	pthread_mutex_unlock(&table->lock);
	ft_usleep(table->time_to_eat);
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
		pthread_mutex_lock(&table->lock);
		if (!table->running)
		{
			pthread_mutex_unlock(&table->lock);
			break ;
		}
		pthread_mutex_unlock(&table->lock);
		eat(philo);
		ft_sleep(table, philo);
		print_status(table, philo->id, "is thinking");
	}
	return (NULL);
}
