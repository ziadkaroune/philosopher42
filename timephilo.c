#include "philo.h"

long long	timestamp(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}


void ft_sleep(long long time_in_ms, reglement_t *loi)
{
    long long start_time;
    long long current_time;

    start_time = timestamp();  
    while (!(loi->mort)) 
    {
        current_time = timestamp();
        if (current_time - start_time >= time_in_ms)  // Check if sleep time is reached
            break;
        usleep(100);  // Sleep for 500 microseconds to avoid busy waiting
    }
}
