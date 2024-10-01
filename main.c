/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkaroune <zkaroune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 13:32:06 by zkaroune          #+#    #+#             */
/*   Updated: 2024/09/15 16:19:24 by zkaroune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int ac, char **av)
{
    t_reglement loi;

    if (ac == 5 || ac == 6)
    {
        if (initalisation(&loi, av) != 0)
                return -1;

        if (philo_algo(&loi) != 0)
                return -1;
    }
    else
       error_exit(ARGS_ERROR);

    return 0; 
}
