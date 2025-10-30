/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 16:37:05 by marvin            #+#    #+#             */
/*   Updated: 2025/10/30 17:24:42 by marvin           ###   ########.fr       */
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
# include <stdbool.h>

typedef struct s_rules	t_rules;

typedef struct s_philo
{
	int				id;
	int				left_fork;
	int				right_fork;
	long			last_meal_ms;
	int				meals_eaten;
	pthread_t		thread;
	pthread_mutex_t	meal_mutex;
	t_rules			*rules;
}	t_philo;

typedef struct s_rules
{
	int				nb_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				must_eat;
	long			start_time_ms;
	bool			stop;
	pthread_mutex_t	stop_mutex;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	t_philo			*philos;
}	t_rules;

int			parse_args(int ac, char **av, t_rules *rules);
void		destroy_and_free(t_rules *rules);
int			rules_init(t_rules *rules);
int			philos_init(t_rules *rules);
int			one_philo(char **argv);
int			start_simulation(t_rules *rules);
void		*philo_routine(void *arg);
void		*monitor_routine(void *arg);
long		now_ms(void);
void		ms_sleep(long ms);
void		print_status(t_philo *p, const char *msg);
bool		get_stop(t_rules *rules);
void		set_stop(t_rules *rules, bool value);
int			is_valid_input(int argc, char *argv[]);
int			is_space(int c);
long long	ft_atol(const char *str);

#endif