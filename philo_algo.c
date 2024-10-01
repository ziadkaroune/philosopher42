/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_algo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkaroune <zkaroune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 13:31:51 by zkaroune          #+#    #+#             */
/*   Updated: 2024/09/17 11:24:41 by zkaroune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"
void philo_eats(t_philo_info *philo)
{
    t_reglement *loi = philo->loi;

    if (loi->nphilo == 1)
    {
        pthread_mutex_lock(&(loi->forks[philo->left_fork_id]));
        write_status(loi, philo->philo_id, FORK_MSG);
        ft_sleep(loi->tm_death, loi); // Philosopher sleeps until death (only one fork)
        write_status(loi, philo->philo_id, DEAD);
        pthread_mutex_unlock(&(loi->forks[philo->left_fork_id]));
        loi->mort = 1; // Mark as dead
        return;
    }

    // Lock the forks
    pthread_mutex_lock(&(loi->forks[philo->left_fork_id]));
    write_status(loi, philo->philo_id, FORK_MSG);
    pthread_mutex_lock(&(loi->forks[philo->right_fork_id]));
    write_status(loi, philo->philo_id, FORK_MSG);

    // Eating
    pthread_mutex_lock(&(loi->meal_check));
    write_status(loi, philo->philo_id, EAT);
    philo->t_last_meal = timestamp();
    pthread_mutex_unlock(&(loi->meal_check));
    ft_sleep(loi->tm_eat, loi);
    philo->is_ate += 1;

    // Unlock the forks
    pthread_mutex_unlock(&(loi->forks[philo->left_fork_id]));
    pthread_mutex_unlock(&(loi->forks[philo->right_fork_id]));
}

// Thread function for each philosopher
void *p_thread(void *void_philosopher)
{
    t_philo_info *philo = (t_philo_info *)void_philosopher;
    t_reglement *loi = philo->loi;

    if (philo->philo_id % 2)
        usleep(0.4 * loi->tm_eat);

    while (!(loi->mort))
    {
        philo_eats(philo);
        if (loi->all_full)
            break;
        write_status(loi, philo->philo_id, SLEEP);
        ft_sleep(loi->time_sleep, loi);
        write_status(loi, philo->philo_id, THINK);
    }
    return NULL;
}

void is_mort(t_reglement *r, t_philo_info *p)
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
            break;
        i = 0;
        while (r->nb_eat != -1 && i < r->nphilo && p[i].is_ate >= r->nb_eat)
            i++;
        if (i == r->nphilo)
            r->all_full = 1;
    }
}

int philo_algo(t_reglement *loi)
{
    int i;
    t_philo_info *phi;

    i = 0;
    phi = loi->philosophers;
    loi->first_timestamp = timestamp();

    // Create philosopher threads
    while (i < loi->nphilo)
    {
        if (pthread_create(&(phi[i].thread_id), NULL, p_thread, &(phi[i])))
            return clean_exit(loi, phi, 1); 
        phi[i].t_last_meal = timestamp();
        i++;
    }

    is_mort(loi, loi->philosophers);
    return clean_exit(loi, phi, 0);  
}