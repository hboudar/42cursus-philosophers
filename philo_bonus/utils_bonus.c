/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 01:12:42 by hboudar           #+#    #+#             */
/*   Updated: 2024/07/30 18:07:38 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	check_args(int argc, char *argv[])
{
	int	num;
	int	i;
	int	j;

	if (argc != 5 && argc != 6)
		ft_error("Invalid number of arguments");
	(1) && (i = 0, num = 0);
	while (argv[++i])
	{
		j = 0;
		num = ft_atoi(argv[i], &j);
		if (i == 1 && (num < 1 || num > 200 || argv[i][j] != '\0'))
			ft_error("Invalid argument(s)");
		else if (num < 1 || argv[i][j] != '\0')
			ft_error("Invalid argument(s)");
	}
}