/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 11:44:35 by hboudar           #+#    #+#             */
/*   Updated: 2024/06/23 14:52:23 by hboudar          ###   ########.fr       */
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
# include "libft/libft.h"

typedef struct s_philosopher
{
    int             id;
    pthread_t       thread;
    long            last_meal_time;
    int             meals_eaten;
    struct s_table  *table;
} t_philosopher;

typedef struct s_table
{
    int             num_philosophers;
    int             time_to_die;
    int             time_to_eat;
    int             time_to_sleep;
    int             meals_required;
    int             simulation_running;
    pthread_mutex_t *forks;
    pthread_mutex_t print_lock;
    t_philosopher   *philosophers;
    long            start_time;
} t_table;

#endif
