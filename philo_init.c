/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 01:22:45 by hboudar           #+#    #+#             */
/*   Updated: 2024/06/28 15:24:02 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void initialize_philosophers(t_table *table)
{
    int i;

    i = 0;
    while (i < table->num_philosophers)
    {
        table->philosophers[i].id = i;
        table->philosophers[i].last_meal_time = get_time_in_ms();
        table->philosophers[i].meals_eaten = 0;
        table->philosophers[i].table = table;
        pthread_create(&table->philosophers[i].thread, NULL, philosopher_routine, &table->philosophers[i]);
        i++;
    }
}

void initialize_forks(t_table *table)
{
    int i;
    
    i = 0;
    table->forks = malloc(sizeof(pthread_mutex_t) * table->num_philosophers);
    while (i < table->num_philosophers)
    {
        pthread_mutex_init(&table->forks[i], NULL);
        i++;
    }
}

void initialize_table(t_table *table, int argc, char **argv)
{
    table->num_philosophers = ft_atoi(argv[1]);
    table->time_to_die = ft_atoi(argv[2]);
    table->time_to_eat = ft_atoi(argv[3]);
    table->time_to_sleep = ft_atoi(argv[4]);
    table->meals_required = (argc == 6) * ft_atoi(argv[5]);
    table->simulation_running = 1;
    table->philosophers = malloc(sizeof(t_philosopher) * table->num_philosophers);
    pthread_mutex_init(&table->print_lock, NULL);
    table->start_time = get_time_in_ms();
    initialize_forks(table);
    initialize_philosophers(table);
}
