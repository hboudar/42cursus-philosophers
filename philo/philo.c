/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 12:48:25 by hboudar           #+#    #+#             */
/*   Updated: 2024/06/26 14:51:26 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int check_args(int argc, char *argv[])
{
    int i;

    i = 0;
    if (argc != 5 && argc != 6)
        return (1);
    while (argv[++i])
    {
        if (argv[i][0] == '-')
            return (1);
        else if (argv[i][0] == '+')
            argv[i]++;
        while (argv[i][0] == '0')
            argv[i]++;
        while (argv[i][0] >= '0' && argv[i][0] <= '9')
            argv[i]++;
        if (argv[i][0] != '\0')
            return (1);
    }
    return (0);
}

int main(int argc, char *argv[])
{
    if (check_args(argc, argv))
    {
        ft_putchar_fd("Error : wrong input\n", 2);
        return (1);
    }
    return 0;
}

//data race
//lock orde violation
//deadlock
//starvation

// pthread_mutex_t    mutex;
// int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *mutexattr);
// int pthread_mutex_lock(pthread_mutex_t *mutex);
// int pthread_mutex_unlock(pthread_mutex_t *mutex);
// int pthread_mutex_destroy(pthread_mutex_t *mutex);