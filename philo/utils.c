/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 01:09:39 by hboudar           #+#    #+#             */
/*   Updated: 2024/08/14 10:17:45 by hboudar          ###   ########.fr       */
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
	pthread_mutex_lock(&table->print_lock);
	printf("%lld %d %s\n", time_in_ms() - table->start_time, id, status);
	pthread_mutex_unlock(&table->print_lock);
}

void	cleanup_table(t_table *table)
{
	int	i;

	i = 0;
	usleep(500000);
	while (i < table->num_philos)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&table->print_lock);
	pthread_mutex_destroy(&table->eat_lock);
	free(table->forks);
	free(table->philo);
}

void	check_args(t_table *table, int argc)
{
	if (table->num_philos < 1)
		ft_error("Invalid number of philosophers\n");
	else if (table->time_to_die < 1 || table->time_to_eat < 1
		|| table->time_to_sleep < 1)
		ft_error("Invalid time\n");
	else if (argc == 6 && table->meals_required < 1)
		ft_error("Invalid number of meals\n");
}
