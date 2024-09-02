/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 01:07:43 by hboudar           #+#    #+#             */
/*   Updated: 2024/08/29 12:22:56 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_error(char *msg)
{
	ft_putstr_fd(msg, 2);
	exit (EXIT_FAILURE);
}

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc < 5 || argc > 6)
		ft_error("Error: wrong number of arguments\n");
	initialize_table(&table, argc, argv);
	start_simulation(&table, -1);
	(1) && (sem_close(table.forks), sem_unlink("forks"));
	(1) && (sem_close(table.meals_lock), sem_unlink("meals"));
	(1) && (sem_close(table.print_lock), sem_unlink("print"));
	(1) && (sem_close(table.death_lock), sem_unlink("death"));
	usleep(50000);
	exit (EXIT_SUCCESS);
}
