/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timephilo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkaroune <zkaroune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 13:31:59 by zkaroune          #+#    #+#             */
/*   Updated: 2024/09/15 16:20:55 by zkaroune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	timestamp(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	ft_sleep(long long time_in_ms, t_reglement *loi)
{
	long long	start_time;
	long long	current_time;

	start_time = timestamp();
	while (!(loi->mort))
	{
		current_time = timestamp();
		if (current_time - start_time >= time_in_ms)
			break ;
		usleep(100);
	}
}
