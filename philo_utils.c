/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 01:09:39 by hboudar           #+#    #+#             */
/*   Updated: 2024/06/29 14:28:27 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int check_args(int argc, char *argv[])
{
    int i;
    int j;

    i = 0;
    if (argc != 5 && argc != 6)
        return (1);
    while (argv[++i])
    {
        j = 0;
        if (argv[i][j] == '-')
            return (1);
        else if (argv[i][j] == '+')
            j++;
        while (argv[i][j] == '0')
            j++;
        while (argv[i][j])
        {
            if (argv[i][j] < '0' || argv[i][j] > '9')
                return (1);
            j++;
        }
        if (argv[i][j] != '\0')
            return (1);
    }
    return (0);
}

long get_time_in_ms(void)
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

void print_status(t_table *table, int id, const char *status)
{
    pthread_mutex_lock(&table->print_lock);
    printf("%ld %d %s\n", get_time_in_ms() - table->start_time, id, status);
    pthread_mutex_unlock(&table->print_lock);
}

void cleanup_table(t_table *table) //clean up the table
{
    for (int i = 0; i < table->num_philosophers; i++)
    {
        pthread_join(table->philosophers[i].thread, NULL);
    }

    for (int i = 0; i < table->num_philosophers; i++)
    {
        pthread_mutex_destroy(&table->forks[i]);
    }
    pthread_mutex_destroy(&table->print_lock);
    free(table->forks);
    free(table->philosophers);
}