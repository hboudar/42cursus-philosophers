/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 01:09:39 by hboudar           #+#    #+#             */
/*   Updated: 2024/09/02 15:58:07 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(long long time)
{
	long long	start_time;

	start_time = time_in_ms();
	while (time_in_ms() - start_time < time)
		usleep(100);
}

long long	time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	print_status(t_table *table, int id, const char *status)
{
	pthread_mutex_lock(&table->lock);
	if (!table->running)
	{
		pthread_mutex_unlock(&table->lock);
		return ;
	}
	pthread_mutex_unlock(&table->lock);
	pthread_mutex_lock(&table->print_lock);
	printf("%lld %d %s\n", time_in_ms() - table->start_time, id, status);
	pthread_mutex_unlock(&table->print_lock);
}

void	cleanup_table(t_table *table)
{
	usleep(250000);
	while (table->num_philos--)
		pthread_mutex_destroy(&table->forks[table->num_philos]);
	pthread_mutex_destroy(&table->lock);
	pthread_mutex_destroy(&table->print_lock);
	free(table->forks);
	free(table->philo);
}

int	destroy_resources(t_table *table, int mode)
{
	int	i;

	i = -1;
	usleep(1000000);
	if (!mode)  (ft_putstr_fd("Failed to initialize mutex\n", 2));
	if (mode == 1)
	{
		pthread_mutex_destroy(&table->lock);
		ft_putstr_fd("Failed to allocate memory for forks\n", 2);
	}
	else if (mode == 2)
	{
		pthread_mutex_destroy(&table->lock);
		free(table->forks);
		ft_putstr_fd("Failed to initialize mutex\n", 2);
	}
	else if (mode == 3)
	{
		while (++i < table->num_philos)
			pthread_mutex_destroy(&table->forks[i]);
		pthread_mutex_destroy(&table->lock);
		free(table->forks);
	}
	pthread_mutex_destroy(&table->print_lock);
	return (1);
}
