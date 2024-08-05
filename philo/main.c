/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 12:48:25 by hboudar           #+#    #+#             */
/*   Updated: 2024/08/05 11:23:08 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_error(char *str)
{
	ft_putstr_fd(str, 2);
	exit(EXIT_FAILURE);
}

int	main(int argc, char **argv)
{
	pthread_t	monitor_thread;
	t_table		table;

	if (argc < 5 || argc > 6)
		ft_error("Error: wrong number of arguments\n");
	initialize_table(&table, argc, argv);
	if (pthread_create(&monitor_thread, NULL,
			(void *)monitor_routine, &table) != 0)
	{
		ft_putstr_fd("Error creating monitor thread\n", 2);
		cleanup_table(&table);
		return (1);
	}
	if (pthread_join(monitor_thread, NULL) != 0)
	{
		ft_putstr_fd("Error joining monitor thread\n", 2);
		cleanup_table(&table);
		return (1);
	}
	cleanup_table(&table);
	return (0);
}
