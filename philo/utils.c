/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 01:09:39 by hboudar           #+#    #+#             */
/*   Updated: 2024/07/30 18:01:58 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_args(int argc, char *argv[])
{
	int	num;
	int	i;
	int	j;

	if (argc != 5 && argc != 6)
		ft_error("Invalid number of arguments");
	(1) && (i = 0, num = 0);
	while (argv[++i])
	{
		j = 0;
		num = ft_atoi(argv[i], &j);
		if (i == 1 && (num < 1 || num > 200 || argv[i][j] != '\0'))
			ft_error("Invalid argument(s)");
		else if (num < 1 || argv[i][j] != '\0')
			ft_error("Invalid argument(s)");
	}
}

void	ft_usleep(long long time)
{
	long long	start_time;

	start_time = time_in_ms();
	while (time_in_ms() - start_time < time)
		usleep(100);
}

long	time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	print_status(t_table *table, int id, const char *status)
{
	if (!table->simulation_running)
		return ;
	pthread_mutex_lock(&table->print_lock);
	printf("%ld %d %s\n", time_in_ms() - table->start_time, id, status);
	pthread_mutex_unlock(&table->print_lock);
}

void	cleanup_table(t_table *table)
{
	int	i;

	pthread_mutex_lock(&table->print_lock);
	i = 0;
	pthread_mutex_destroy(&table->print_lock);
	free(table->forks);
	free(table->philos);
}
