/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 10:00:23 by hboudar           #+#    #+#             */
/*   Updated: 2024/08/07 13:19:54 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_init(t_table *table, t_philo *philo, int i)
{
	table->start_time = time_in_ms();
	philo->last_meal = time_in_ms();
	philo->id = i;
	philo->meals = 0;
	philo->is_dead = 0;
	philo->table = table;
}

void	ft_eat(t_philo *philo)
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

void	ft_sleep(t_philo *philo)
{
	print_status(philo, "is sleeping");
	ft_usleep(philo->table->time_to_sleep);
}

int	philo_life(void *arg)
{
	t_table		*table;
	t_philo		*philo;
	pthread_t	death;

	philo = (t_philo *)arg;
	table = philo->table;
	pthread_create(&death, NULL, monitor_routine, philo);
	while (1)
	{
		if (table->meals_required != -1
			&& philo->meals == table->meals_required)
			return (EXIT_SUCCESS);
		ft_eat(philo);
		ft_sleep(philo);
		print_status(philo, "is thinking");
	}
	return (EXIT_FAILURE);
}
