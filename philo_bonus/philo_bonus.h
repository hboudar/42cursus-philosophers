/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 01:08:27 by hboudar           #+#    #+#             */
/*   Updated: 2024/07/30 18:07:07 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
#include <sys/_types/_pid_t.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/types.h>


typedef struct s_table
{
    int				num_philos;
    int				time_to_die;
    int				time_to_eat;
    int				time_to_sleep;
    int				meals_required;
    int				simulation_running;
    sem_t			*forks;
    sem_t			*print_lock;
    pid_t           *philos;
    long			start_time;
}	t_table;

void    init_table(t_table *table, int argc, char **argv);


void    check_args(int argc, char *argv[]);
int     ft_atoi(const char *str, int *i);
void	ft_putstr_fd(char *s, int fd);
void    ft_error(char *msg);

#endif
