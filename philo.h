/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 16:37:05 by marvin            #+#    #+#             */
/*   Updated: 2025/10/28 18:25:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <time.h>
# include <sys/time.h>

typedef struct s_rules
{
	long long			philo_count;
	long long			time_to_die;
	long long			time_to_eat;
	long long			time_to_sleep;
	long long			must_eat_count;
	long long			start_time;
	pthread_mutex_t		start_lock;
	pthread_mutex_t		*fork;
	pthread_mutex_t		print_lock;
	pthread_mutex_t		meal_lock;
	pthread_mutex_t		meal_eaten_lock;
	pthread_mutex_t		sim_lock;
	int					stop_sim;
}	t_rules;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	int				meals_eaten;
	long long		last_meal_time;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_rules			*rules;
}	t_philo;

int			is_valid_input(int argc, char *argv[]);
int			is_space(int c);
long long	ft_atol(const char *str);
t_rules		*init_rules(char **argv);
t_philo		*init_philo(t_rules *rules);
void		*routine(void *arg);
void		thread_creation(t_philo *philo);
void		thread_join(t_philo *philo);
void		*thread_monitor(void *arg);
long long	get_time_in_ms(void);
void		sub_routine_thinking(t_philo *philo);
void		sub_routine_eating(t_philo *philo);
void		cleanup_all(t_philo *philo, t_rules *rules);
void		sub_routine_sleeping(t_philo *philo);
int			check_for_death(t_philo *philo);
long long	get_time(t_philo *philo);

#endif