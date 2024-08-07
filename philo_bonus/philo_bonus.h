/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 01:08:27 by hboudar           #+#    #+#             */
/*   Updated: 2024/08/08 10:53:04 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>

typedef struct s_philo
{
	int							id;
	int							meals;
	int							is_dead;
	unsigned long long			last_meal;
	struct s_table				*table;
}	t_philo;

typedef struct s_table
{
	int					num_philos;
	int					meals_required;
	int					simulation_running;
	unsigned long long	start_time;
	unsigned long long	time_to_eat;
	unsigned long long	time_to_die;
	unsigned long long	time_to_sleep;
	sem_t				*forks;
	sem_t				*print_lock;
	sem_t				*death_lock;
	t_philo				*philos;
}	t_table;

void				ft_error(char *msg);
void				ft_putstr_fd(char *s, int fd);
int					ft_atoi(const char *str, int i);

void				initialize_table(t_table *table, int argc, char **argv);
void				start_simulation(t_table *table);

void				ft_usleep(unsigned long long time);
unsigned long long	time_in_ms(void);
void				print_status(t_philo *philo, char *status);
void				*monitor_routine(void *arg);
void				wait_pids(pid_t *pid, int n_philos);

#endif
