/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 01:07:43 by hboudar           #+#    #+#             */
/*   Updated: 2024/07/30 18:06:40 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void    ft_error(char *msg)
{
    ft_putstr_fd(msg, 2);
    exit(EXIT_FAILURE);
}

int main(int argc, char **argv)
{
    t_table table;

    check_args(argc, argv);
    init_table(&table, argc, argv);
    return (0);
}