/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 12:48:25 by hboudar           #+#    #+#             */
/*   Updated: 2024/06/28 18:03:20 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
    t_table table;

    if (check_args(argc, argv))
    {
        ft_putstr_fd("Error: Invalid arguments\n", 2);
        return (1);
    }
    initialize_table(&table, argc, argv);

    while (table.simulation_running)
    {
        for (int i = 0; i < table.num_philosophers; i++)
        {
            if (get_time_in_ms() - table.philosophers[i].last_meal_time > table.time_to_die)
            {
                print_status(&table, table.philosophers[i].id, "died");
                table.simulation_running = 0;
                break;
            }
        }
        usleep(1000); // check every 1ms
    }
    cleanup_table(&table);
    return 0;
}
