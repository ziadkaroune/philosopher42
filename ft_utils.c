
#include "philo.h"

int error_exit(char  *s)
{
	printf("%s" , s);
	return  (-1);
}
int			ft_atoi(const char *str)
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

void		write_status(reglement_t *rules, int philo_id, char *status)
{
	pthread_mutex_lock(&(rules->status));
	if (!(rules->mort))
	{
		printf("%lli ", timestamp() - rules->first_timestamp);
		printf("%i %s \n",  philo_id + 1 , status);
	}
	pthread_mutex_unlock(&(rules->status));
	return ;
}

