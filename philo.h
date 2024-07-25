/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 11:44:35 by hboudar           #+#    #+#             */
/*   Updated: 2024/07/25 07:50:46 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_philosopher
{
    int             id;
    pthread_t       thread;
    long            last_meal_time;
    int             meals_eaten;
    int             left_fork;
    int             right_fork;
    struct s_table  *table;
} t_philosopher;

typedef struct s_table
{
    int             num_philos;
    int             time_to_die;
    int             time_to_eat;
    int             time_to_sleep;
    int             meals_required;
    int             simulation_running;
    pthread_mutex_t *forks;
    pthread_mutex_t print_lock;
    t_philosopher   *philos;
    long            start_time;
} t_table;

void    eat(t_philosopher *philo);
void    sleep_and_think(t_philosopher *philo);
void    *philosopher_routine(void *arg);
void    initialize_philosophers(t_table *table);
void    initialize_forks(t_table *table);
void    initialize_table(t_table *table, int argc, char **argv);
void    cleanup_table(t_table *table);
void    print_status(t_table *table, int id, const char *status);
long    get_time_in_ms(void);
int     check_args(int argc, char *argv[]);
void    ft_usleep(long long time);
  
int     ft_atoi(const char *str);
void    ft_putstr_fd(char *s, int fd);

#endif
