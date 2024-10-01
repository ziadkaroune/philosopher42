/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkaroune <zkaroune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 15:19:34 by gsmets            #+#    #+#             */
/*   Updated: 2024/08/07 23:44:54 by zkaroune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eats(philo_info *philo)
{
	reglement_t *loi;

	loi = philo->loi;
	pthread_mutex_lock(&(loi->forks[philo->left_fork_id]));
	write_status(loi, philo->philo_id, FORK_MSG);
	pthread_mutex_lock(&(loi->forks[philo->right_fork_id]));
	write_status(loi, philo->philo_id, FORK_MSG);
	pthread_mutex_lock(&(loi->meal_check));
	write_status(loi, philo->philo_id, EAT);
	philo->t_last_meal = timestamp();
	pthread_mutex_unlock(&(loi->meal_check));
	ft_sleep(loi->tm_eat, loi);
	philo-> is_ate += 1;
	pthread_mutex_unlock(&(loi->forks[philo->left_fork_id]));
	pthread_mutex_unlock(&(loi->forks[philo->right_fork_id]));
}

void	*p_thread(void *void_philosopher)
{
	philo_info	*philo;
	reglement_t			*loi;

	philo = (philo_info *)void_philosopher;
	loi = philo->loi;
	if (philo->philo_id % 2)
		usleep(15000);
	while (!(loi->mort))
	{
		philo_eats(philo);
		if (loi->all_full)
			break ;
		write_status(loi, philo->philo_id, SLEEP);
		ft_sleep(loi->time_sleep, loi);
		write_status(loi, philo->philo_id, THINK);

	}
	return (NULL);
}


void	is_mort(reglement_t *r, philo_info *p)
{
	int i;

	while (!(r->all_full))
	{
		i = -1;
		while (++i < r->nphilo && !(r->mort))
		{
			pthread_mutex_lock(&(r->meal_check));
			if (timestamp() - p[i].t_last_meal > r->tm_death)
			{
				write_status(r, i, DEAD);
				r->mort = 1;
			}
			pthread_mutex_unlock(&(r->meal_check));
			usleep(100);
		}
		if (r->mort)
			break ;
		i = 0;
		while (r->nb_eat != -1 && i < r->nphilo && p[i].is_ate >= r->nb_eat)
			i++;
		if (i == r->nphilo)
			r->all_full = 1;
	}
}


void	free_exit(reglement_t *loi, philo_info *philos)
{
	int i;

	i = 0;
	while (++i <= loi->nphilo -1)
		pthread_join(philos[i].thread_id, NULL);
	i = 0;
	while (++i < loi->nphilo - 1)
		pthread_mutex_destroy(&(loi->forks[i]));
	pthread_mutex_destroy(&(loi->status));
}

int		philo_algo(reglement_t *loi)
{
	int				i;
	philo_info	*phi;

	i = 0;
	phi = loi->philosophers;
	loi->first_timestamp = timestamp();
	while (i < loi->nphilo)
	{
		if (pthread_create(&(phi[i].thread_id), NULL, p_thread, &(phi[i])))
			return (1);
		phi[i].t_last_meal = timestamp();
		i++;
	}
	is_mort(loi, loi->philosophers);
	free_exit(loi, phi);
	return (0);
}
