/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkaroune <zkaroune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 13:31:01 by zkaroune          #+#    #+#             */
/*   Updated: 2024/09/15 16:18:19 by zkaroune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int error_exit(char *s)
{
    printf("%s" , s);
    return -1;
} 
void free_resources(t_reglement *loi)
{
    if (loi->philosophers)
    {
        free(loi->philosophers);
        loi->philosophers = NULL; 
    }

    if (loi->forks)
    {
        free(loi->forks);
        loi->forks = NULL;
    }
}

void free_exit(t_reglement *loi, t_philo_info *philos)
{
    int i;

    i = 0;
    while (i < loi->nphilo)
    {
        pthread_join(philos[i].thread_id, NULL); 
        i++;
    }

    i = 0;
    while (i < loi->nphilo)
    {
        pthread_mutex_destroy(&(loi->forks[i]));
        i++;
    }

    pthread_mutex_destroy(&(loi->status));
    pthread_mutex_destroy(&(loi->meal_check));
}

int clean_exit(t_reglement *loi, t_philo_info *philos, int return_code)
{
    free_exit(loi, philos);
    free_resources(loi);    
    return return_code;    
}


int	ft_atoi(const char *str)
{
	long int	n;
	int			sign;

	n = 0;
	sign = 1;
	while ((*str <= 13 && *str >= 9) || *str == 32)
		str++;
	if (*str == '-')
		return (-1);
	else if (*str == '+')
		str++;
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
			n = n * 10 + (*str++ - '0');
		else
			return (-1);
	}
	return ((int)(n * sign));
}

void	write_status(t_reglement *rules, int philo_id, char *status)
{
	pthread_mutex_lock(&(rules->status));
	if (!(rules->mort))
	{
		printf("%lli ", timestamp() - rules->first_timestamp);
		printf("%i %s \n", philo_id + 1, status);
	}
	pthread_mutex_unlock(&(rules->status));
	return ;
}
