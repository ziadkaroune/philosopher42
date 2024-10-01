/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkaroune <zkaroune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 13:31:36 by zkaroune          #+#    #+#             */
/*   Updated: 2024/09/17 11:08:15 by zkaroune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define FORK_MSG "\033[1;33mhas taken a fork\033[0m"
# define EAT "\033[1;32m is eating\033[0m"
# define SLEEP "\033[1;34m is sleeping\033[0m"
# define THINK "\033[1;35m is thinking\033[0m"
# define DEAD "\033[1;31m died\033[0m"
# define MUTEX_ERROR " \033[1;31m Error mutex innitialisation\033[0m]"
# define ARGS_ERROR "Error\n[nb_philo] [msdeath] [ms_eat] [ms_sleep] [nb eat]\n"

typedef struct s_philo
{
	int					philo_id;
	int					is_ate;
	int					left_fork_id;
	int					right_fork_id;
	long long			t_last_meal;
	struct s_reglement	*loi;
	pthread_t			thread_id;
}						t_philo_info;

typedef struct s_reglement
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
	t_philo_info		*philosophers;
}						t_reglement;

int	clean_exit(t_reglement *loi, t_philo_info *philos, int exit_code);
int						alloc_philo(t_reglement *loi);
int						initalisation(t_reglement *rules, char **av);
int						ft_atoi(const char *str);
void					write_status(t_reglement *rules, int id, char *string);
long long				timestamp(void);
void					ft_sleep(long long time, t_reglement *rules);
int						philo_algo(t_reglement *rules);
int						parsing(t_reglement *loi, char **av);
void free_exit(t_reglement *loi, t_philo_info *philos);
void free_resources(t_reglement *loi);
int error_exit(char *s);
#endif
