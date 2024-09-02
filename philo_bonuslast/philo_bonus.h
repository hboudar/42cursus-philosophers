/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 01:08:27 by hboudar           #+#    #+#             */
/*   Updated: 2024/08/29 13:18:59 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <fcntl.h>

typedef struct s_philo
{
	int				id;
	int				running;
	long long		start_time;
	long long		last_meal;
	int				meals_to_eat;
	struct s_table	*table;
}	t_philo;

typedef struct s_table
{
	int			num_philos;
	int			meals_to_eat;
	int			time_to_eat;
	int			time_to_die;
	int			time_to_sleep;
	t_philo		*philo;
	sem_t		*forks;
	sem_t		*print_lock;
	sem_t		*death_lock;
	sem_t		*meals_lock;
}	t_table;

void		ft_error(char *msg);
void		ft_putstr_fd(char *s, int fd);
int			ft_atoi(const char *str, int i);

void		start_simulation(t_table *table, int i);
void		initialize_table(t_table *table, int argc, char **argv);

long long	time_in_ms(void);
void		ft_usleep(long long time);
void		*monitor(void *arg);
void		wait_pids(pid_t *pid, int n_philos);
void		print_status(t_philo *philo, t_table *table, const char *status);

#endif
