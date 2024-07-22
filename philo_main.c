/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 12:48:25 by hboudar           #+#    #+#             */
/*   Updated: 2024/07/22 14:52:32 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int monitor_routine(void *arg)
{
    t_table *table = (t_table *)arg;

    while (table->simulation_running)
    {
        for (int i = 0; i < table->num_philosophers; i++)
        {
            if (get_time_in_ms() - table->philosophers[i].last_meal_time >= table->time_to_die)
            {
                table->simulation_running = 0;
                pthread_mutex_lock(&table->print_lock);
                printf("%ld %d %s\n", get_time_in_ms() - table->start_time, table->philosophers[i].id, "died");
                pthread_mutex_unlock(&table->print_lock);
                return (1);
            }
        }
    }
    return (0);
}

int main(int argc, char **argv)
{
    pthread_t monitor_thread;
    t_table table;

    if (check_args(argc, argv) == 1)
    {
        perror("Error: invalid arguments\n");
        exit(EXIT_FAILURE);
    }
    initialize_table(&table, argc, argv);
    if (pthread_create(&monitor_thread, NULL, (void *)monitor_routine, &table) != 0)
    {
        perror("Error creating monitor thread");
        cleanup_table(&table);
        return 1;
    }
    if (pthread_join(monitor_thread, NULL) != 0)
    {
        perror("Error joining monitor thread");
        cleanup_table(&table);
        return (1);
    }
    cleanup_table(&table);
    return (0);
}
