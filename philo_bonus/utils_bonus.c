/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 01:12:42 by hboudar           #+#    #+#             */
/*   Updated: 2024/08/07 13:26:39 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	check_args(int argc, t_table *table)
{
	if (table->num_philos < 1 || table->num_philos > 200)
		ft_error("Invalid number of philosophers\n");
	if (table->time_to_die < 60 || table->time_to_eat < 60
		|| table->time_to_sleep < 60)
		ft_error("Time must be at least 60ms\n");
	if (table->meals_required < 1 && argc == 6)
		ft_error("Invalid number of meals\n");
}

long	time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(long long time)
{
	long long	start_time;

	start_time = time_in_ms();
	while (time_in_ms() - start_time < time)
		usleep(100);
}

void	print_status(t_philo *philo, char *status)
{
	sem_wait(philo->table->print_lock);
	printf("%ld %i %s\n", time_in_ms() - philo->table->start_time,
		philo->id, status);
	sem_post(philo->table->print_lock);
}

void	wait_pids(pid_t *pid, int n_philos)
{
	int	i;
	int	status;

	waitpid(-1, &status, 0);
	if (status != 0)
	{
		i = -1;
		while (++i < n_philos)
			kill(pid[i], SIGKILL);
	}
	else
	{
		i = -1;
		while (++i < n_philos)
			waitpid(pid[i], &status, 0);
	}
}
