/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 11:44:35 by hboudar           #+#    #+#             */
/*   Updated: 2024/09/02 19:56:34 by hboudar          ###   ########.fr       */
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
	int				running;
}	t_table;

int			monitor(void *arg);
void		*philo_routine(void *arg);
int			init_args(t_table *table, int argc, char *argv[]);
int			init_forks(t_table *table, int i);
int			init_philos(t_table *table, int i);

long long	time_in_ms(void);
void		ft_usleep(long long time);
void		print_status(t_table *table, int id, const char *status);

void		cleanup_table(t_table *table);
int			ft_putstr_fd(char *s, int fd);
int			ft_atoi(const char *str, int i);
int			detaching_philos(t_table *table);
int			destroy_resources(t_table *table, int mode);

#endif
