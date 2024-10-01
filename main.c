
#include "philo.h"

int		main(int ac, char **av)
{
	reglement_t	loi;

	if (ac == 5 || ac == 6)
	{
					
		if ((initalisation(&loi, av)))
			return (-1);
		if (philo_algo(&loi))
			return (-1);
	}
	else
	{
		error_exit(ARGS_ERROR);
		return -1;
	}
		

	return (0);
}


