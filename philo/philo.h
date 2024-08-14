/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 11:44:35 by hboudar           #+#    #+#             */
/*   Updated: 2024/08/13 12:01:14 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	long long		last_meal;
	int				meals_eaten;
	int				left_fork;
	int				right_fork;
	int				full;
	struct s_table	*table;
}	t_philo;

typedef struct s_table
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_required;
	int				philos_full;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	eat_lock;
	t_philo			*philo;
	long long		start_time;
}	t_table;

int			monitor_routine(void *arg);
void		*philosopher_routine(void *arg);
void		check_args(t_table *table, int argc);
void		initialize_table(t_table *table, int argc, char **argv);

long long	time_in_ms(void);
void		ft_usleep(long long time);
void		print_status(t_table *table, int id, const char *status);

void		ft_error(char *str);
void		cleanup_table(t_table *table);
void		ft_putstr_fd(char *s, int fd);
int			ft_atoi(const char *str, int i);
void		detaching_philos(t_table *table);

#endif
