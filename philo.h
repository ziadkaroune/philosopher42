/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmets <gsmets@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 18:30:58 by gsmets            #+#    #+#             */
/*   Updated: 2021/02/22 10:14:00 by gsmets           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
#include <stdbool.h>
# include <string.h>
# include <pthread.h>

#define FORK_MSG "\033[1;33mhas taken a fork\033[0m"    // Yellow
#define EAT "\033[1;32m is eating\033[0m"               // Green
#define SLEEP "\033[1;34m is sleeping\033[0m"           // Blue
#define THINK "\033[1;35m is thinking\033[0m"           // Magenta
#define DEAD "\033[1;31m is dead\033[0m"
#define MUTEX_ERROR " \033[1;31m Error mutex innitialisation\033[0m]"
#define ARGS_ERROR	"Error arguments  \n[nb_philo] [ms death] [ms_eat] [ms_sleep] [nb eat : optional]\n"


struct reglement_s;

typedef	struct			philo
{
	int					philo_id;
	int					is_ate;
	int					left_fork_id;
	int					right_fork_id;
	long long			t_last_meal;
	struct reglement_s		*loi; 
	pthread_t			thread_id;
}						philo_info;

typedef struct			reglement_s
{
	int					nphilo;
	int					tm_death;
	int					tm_eat;
	int					time_sleep;
	int					nb_eat;
	int					mort;
	int					all_full;
	long long			first_timestamp;
	pthread_mutex_t		meal_check;
	pthread_mutex_t		*forks;
	pthread_mutex_t		status;
	philo_info		*philosophers;
}						reglement_t;

int		error_exit(char  *s);
int						initalisation(reglement_t *rules, char **av);
int						ft_atoi(const char *str);
void					write_status(reglement_t *rules, int id, char *string);
long long				timestamp(void);
void					ft_sleep(long long time, reglement_t *rules);
int						philo_algo(reglement_t *rules);
void					free_exit(reglement_t *rules, philo_info *philos);

#endif
