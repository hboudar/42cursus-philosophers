/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 12:48:25 by hboudar           #+#    #+#             */
/*   Updated: 2024/07/10 17:07:25 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *monitor_routine(void *arg)
{
    t_table *table = (t_table *)arg;

    while (table->simulation_running)
    {
        for (int i = 0; i < table->num_philosophers; i++)
        {
            pthread_mutex_lock(&table->print_lock);
            long long current_time = get_time_in_ms();
            if (current_time - table->philosophers[i].last_meal_time > table->time_to_die)
            {
                print_status(table, table->philosophers[i].id, "died");
                table->simulation_running = 0;
            }
            pthread_mutex_unlock(&table->print_lock);
            if (!table->simulation_running)
                break ;
        }
        usleep(1000);
    }
    for (int i = 0; i < table->num_philosophers; i++)
        pthread_join(table->philosophers[i].thread, NULL);
    cleanup_table(table);
    return NULL;
}

int main(int argc, char **argv)
{
    t_table table;

    if (check_args(argc, argv) == 1)
    {
        perror("Error: invalid arguments\n");
        return 1;
    }
    initialize_table(&table, argc, argv);
    monitor_routine(&table);
    return 0;
}
