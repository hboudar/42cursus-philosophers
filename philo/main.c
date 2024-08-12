/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 12:48:25 by hboudar           #+#    #+#             */
/*   Updated: 2024/08/12 10:07:54 by hboudar          ###   ########.fr       */
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
	t_table		table;

	if (argc < 5 || argc > 6)
		ft_error("Error: wrong number of arguments\n");
	initialize_table(&table, argc, argv);
	monitor_routine(&table);
	cleanup_table(&table);
	return (0);
}
