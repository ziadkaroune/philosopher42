
#include "philo.h"

int	mutex_intialisation(reglement_t *loi)
{
	int i;

	i = loi->nphilo - 1;
	if (pthread_mutex_init(&(loi->status), NULL))
		return (-1);
	if (pthread_mutex_init(&(loi->meal_check), NULL))
		return (-1);
	while (i >= 0)
	{
		if (pthread_mutex_init(&(loi->forks[i]), NULL))
			return (-1);
		i--;
	}

	return (0);
}

int	init_philosophers(reglement_t *loi)
{
	int i;

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
	return (0);
}

int	initalisation(reglement_t *loi, char **av )
{
	loi->nphilo = ft_atoi(av[1]);
	loi->tm_death = ft_atoi(av[2]);
	loi->tm_eat = ft_atoi(av[3]);
	loi->time_sleep = ft_atoi(av[4]);
	loi->all_full = 0;
	loi->mort = 0;
	if (loi->nphilo < 1 || loi->tm_death < 0 || loi->tm_eat < 0
		|| loi->time_sleep < 0 || loi->nphilo > 250)
		{
			error_exit(ARGS_ERROR);
			return -1;
		}
			
	if (av[5])
	{
		loi->nb_eat = ft_atoi(av[5]);
		if (loi->nb_eat <= 0)
			error_exit(ARGS_ERROR);
			return (-1);
	}
	else
		loi->nb_eat = -1;
    loi -> philosophers = (philo_info *)malloc(sizeof(philo_info) * (loi->nphilo));
    loi ->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * (loi->nphilo));
    if(!(loi->philosophers)  || !loi->forks )
        return (-1);
	if (mutex_intialisation(loi))
			error_exit(MUTEX_ERROR);
		
	init_philosophers(loi);
	return (0);
}
