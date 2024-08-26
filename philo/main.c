/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 12:48:25 by hboudar           #+#    #+#             */
/*   Updated: 2024/08/24 17:05:45 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table		table;

	if (argc < 5 || argc > 6)
		return (ft_putstr_fd("Error: wrong number of arguments\n", 2));
	if (init_args(&table, argc, argv))
		return (1);
	if (init_forks(&table, 0) || init_philos(&table, -1))
		return (1);
	monitor(&table);
	cleanup_table(&table);
	return (0);
}
