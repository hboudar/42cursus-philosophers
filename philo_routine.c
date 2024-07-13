/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 01:25:54 by hboudar           #+#    #+#             */
/*   Updated: 2024/07/10 17:07:14 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void sleep_and_think(t_philosopher *philo)
{
    t_table *table = philo->table;

    print_status(table, philo->id, "is sleeping");
    usleep(table->time_to_sleep * 1000);
    print_status(table, philo->id, "is thinking");
}

void eat(t_philosopher *philo)
{
    t_table *table = philo->table;
    int left_fork = philo->id;
    int right_fork = (philo->id + 1) % table->num_philosophers;

    if (philo->id % 2 == 0)
        usleep(table->time_to_eat / 2);
    pthread_mutex_lock(&table->forks[left_fork]);
    print_status(table, philo->id, "has taken a fork");
    pthread_mutex_lock(&table->forks[right_fork]);
    print_status(table, philo->id, "has taken a fork");
    print_status(table, philo->id, "is eating");
    philo->last_meal_time = get_time_in_ms();
    usleep(table->time_to_eat * 1000);
    philo->meals_eaten++;

    pthread_mutex_unlock(&table->forks[left_fork]);
    pthread_mutex_unlock(&table->forks[right_fork]);
}

void *philosopher_routine(void *arg)
{
    t_philosopher *philo = (t_philosopher *)arg;
    t_table *table = philo->table;

    while (1)
    {
        if (table->simulation_running)
            eat(philo);
        else if (!table->simulation_running)
            return NULL;
        sleep_and_think(philo);
    }
    return (NULL);
}