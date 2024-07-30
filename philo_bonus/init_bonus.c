/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 10:27:15 by hboudar           #+#    #+#             */
/*   Updated: 2024/07/30 18:07:47 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void    init_table(t_table *table, int argc, char **argv)
{
    table->meals_required = -1;
	if (argc == 6)
		(1) && (argc = 0, table->meals_required = ft_atoi(argv[5], &argc));
	(1) && (argc = 0, table->num_philos = ft_atoi(argv[1], &argc));
	(1) && (argc = 0, table->time_to_die = ft_atoi(argv[2], &argc));
	(1) && (argc = 0, table->time_to_eat = ft_atoi(argv[3], &argc));
	(1) && (argc = 0, table->time_to_sleep = ft_atoi(argv[4], &argc));
	table->simulation_running = 1;
}
