/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 10:27:15 by hboudar           #+#    #+#             */
/*   Updated: 2024/08/05 11:23:51 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void    initialize_table(t_table *table, int argc, char **argv)
{
	table->num_philos = ft_atoi(argv[1], 0);
	table->time_to_die = ft_atoi(argv[2], 0);
	table->time_to_eat = ft_atoi(argv[3], 0);
	table->time_to_sleep = ft_atoi(argv[4], 0);
	table->meals_required = -1;
	if (argc == 6)
		table->meals_required = ft_atoi(argv[5], 0);
	check_args(argc, table);
	table->simulation_running = 1;
}
