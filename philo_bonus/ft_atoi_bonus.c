/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 19:40:38 by hboudar           #+#    #+#             */
/*   Updated: 2024/07/30 18:05:37 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_atoi(const char *str, int *i)
{
	unsigned long	n;
	unsigned long	n_ll;
	int				sign;

	if (!str)
		return (0);
	while (str[*i] == 32 || (str[*i] >= 9 && str[*i] <= 13))
		*i += 1;
	sign = (str[*i] == '-') * -1 + (str[*i] != '-');
	*i += (str[*i] == '-' || str[*i] == '+');
	(1) && (n_ll = 0, n = 0);
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		n = n * 10 + str[*i] - 48;
		if (n / 10 != n_ll && sign == 1)
			return (-1);
		else if (n / 10 != n_ll)
			return (0);
		n_ll = n;
		*i += 1;
	}
	return (n * sign);
}
