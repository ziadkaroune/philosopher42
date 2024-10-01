/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkaroune <zkaroune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 13:31:22 by zkaroune          #+#    #+#             */
/*   Updated: 2024/09/17 11:09:37 by zkaroune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	alloc_philo(t_reglement *loi)
{
	loi->philosophers = (t_philo_info *)malloc(sizeof(t_philo_info)
			* loi->nphilo);
	loi->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* loi->nphilo);
	if (!loi->forks || !loi->philosophers)
		return (-1);
	return (0);
}

int	mutex_intialisation(t_reglement *loi)
{
	int	i;

	i = loi->nphilo;
	if (pthread_mutex_init(&(loi->status), NULL))
		return (-1);
	if (pthread_mutex_init(&(loi->meal_check), NULL))
		return (-1);
	while (--i >= 0)
	{
		if (pthread_mutex_init(&(loi->forks[i]), NULL))
			return (-1);
	}
	return (0);
}

int	init_philosophers(t_reglement *loi)
{
	int	i;

	i = loi->nphilo - 1;
	while (i >= 0)
	{
		loi->philosophers[i].philo_id = i;
		loi->philosophers[i].is_ate = 0;
		loi->philosophers[i].left_fork_id = i;
		loi->philosophers[i].right_fork_id = (i + 1) % loi->nphilo;
		loi->philosophers[i].t_last_meal = 0;
		loi->philosophers[i].loi = loi;
		i--;
	}
	loi->all_full = 0;
	loi->mort = 0;
	return (0);
}

int parsing(t_reglement *loi, char **av)
{
    loi->nphilo = ft_atoi(av[1]);
    loi->tm_death = ft_atoi(av[2]);
    loi->tm_eat = ft_atoi(av[3]);
    loi->time_sleep = ft_atoi(av[4]);

    if (loi->nphilo < 1 || loi->tm_death < 0 || loi->tm_eat < 0 || loi->time_sleep < 0 || loi->nphilo > 250)
    {
        error_exit(ARGS_ERROR);
        return -1;
    }

    if (av[5])
    {
        loi->nb_eat = ft_atoi(av[5]);
        if (loi->nb_eat <= 0)
        {
            error_exit(ARGS_ERROR);
            return -1;
        }
    }
    else
        loi->nb_eat = -1;

    return 0;
}


int initalisation(t_reglement *loi, char **av)
{
    if (parsing(loi, av) != 0)
        return -1;
    if (alloc_philo(loi) != 0)
    {
        free_resources(loi); 
        return -1;
    }
    if (mutex_intialisation(loi) != 0)
    {
        free_resources(loi); 
        return -1;
    }
    init_philosophers(loi); 
    return 0;
}