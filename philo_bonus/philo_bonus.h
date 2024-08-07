/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 01:08:27 by hboudar           #+#    #+#             */
/*   Updated: 2024/08/07 11:42:49 by hboudar          ###   ########.fr       */
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
	int			    id;
	int	    		meals;
	int				is_dead;
	long			last_meal;
	struct s_table  *table;
}   t_philo;

typedef struct s_table
{
    int		num_philos;
    int		meals_required;
    int		simulation_running;
    long	start_time;
    long	time_to_eat;
    long	time_to_die;
    long	time_to_sleep;
    sem_t	*forks;
    sem_t	*print_lock;
    sem_t   *death_lock;
    t_philo *philos;
}	t_table;

void    ft_error(char *msg);

void    check_args(int argc, t_table *table);
void    initialize_table(t_table *table, int argc, char **argv);

void    philo_init(t_table *table, t_philo *philo, int i);
int     philo_life(void *philo);

int     ft_atoi(const char *str, int i);
void	ft_putstr_fd(char *s, int fd);
void	ft_usleep(long ms);
long	time_in_ms(void);
void	print_status(t_philo *philo, char *status);
int     monitor_routine(t_philo *philo);

#endif
