/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 01:25:54 by hboudar           #+#    #+#             */
/*   Updated: 2024/06/28 01:37:56 by hboudar          ###   ########.fr       */
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

    pthread_mutex_lock(&table->forks[philo->id]);
    print_status(table, philo->id, "has taken a fork");
    pthread_mutex_lock(&table->forks[(philo->id + 1) % table->num_philosophers]);
    print_status(table, philo->id, "has taken a fork");

    print_status(table, philo->id, "is eating");
    philo->last_meal_time = get_time_in_ms();
    usleep(table->time_to_eat * 1000);
    philo->meals_eaten++;

    pthread_mutex_unlock(&table->forks[philo->id]);
    pthread_mutex_unlock(&table->forks[(philo->id + 1) % table->num_philosophers]);
}

void *philosopher_routine(void *arg)
{
    t_philosopher *philo = (t_philosopher *)arg;
    t_table *table = philo->table;

    while (table->simulation_running)
    {
        eat(philo);
        if (table->meals_required && philo->meals_eaten >= table->meals_required)
            break;
        sleep_and_think(philo);
    }
    return NULL;
}