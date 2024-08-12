/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 01:12:42 by hboudar           #+#    #+#             */
/*   Updated: 2024/08/12 11:56:36 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long long	time_in_ms(void)
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

void	print_status(t_philo *philo, const char *status)
{
	sem_wait(philo->table->print_lock);
	printf("%lld %d %s\n", time_in_ms() - philo->table->start_time,
		philo->id, status);
	sem_post(philo->table->print_lock);
}

void	wait_pids(pid_t *pid, int n_philos)
{
	int	status;
	int	i;

	while (n_philos--)
	{
		waitpid(-1, &status, 0);
		if (status != 0)
		{
			i = -1;
			while (++i < n_philos)
				kill(pid[i], SIGKILL);
			return ;
		}
	}
}
