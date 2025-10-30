/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 11:19:50 by marvin            #+#    #+#             */
/*   Updated: 2025/10/30 21:39:51 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	take_forks(t_philo *p)
{
	if (p->id % 2 == 0)
	{
		pthread_mutex_lock(&p->rules->forks[p->right_fork]);
		print_status(p, "has taken a fork");
		pthread_mutex_lock(&p->rules->forks[p->left_fork]);
		print_status(p, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&p->rules->forks[p->left_fork]);
		print_status(p, "has taken a fork");
		pthread_mutex_lock(&p->rules->forks[p->right_fork]);
		print_status(p, "has taken a fork");
	}
}

static void	release_forks(t_philo *p)
{
	pthread_mutex_unlock(&p->rules->forks[p->left_fork]);
	pthread_mutex_unlock(&p->rules->forks[p->right_fork]);
}

void	*philo_routine(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	while (now_ms() < p->rules->start_time_ms)
		;
	if (p->id % 2 == 0)
		usleep(42);
	pthread_mutex_lock(&p->meal_mutex);
	p->last_meal_ms = now_ms();
	pthread_mutex_unlock(&p->meal_mutex);
	while (!get_stop(p->rules))
	{
		take_forks(p);
		pthread_mutex_lock(&p->meal_mutex);
		p->last_meal_ms = now_ms();
		p->meals_eaten++;
		pthread_mutex_unlock(&p->meal_mutex);
		print_status(p, "is eating");
		ms_sleep(p->rules->time_to_eat);
		release_forks(p);
		print_status(p, "is sleeping");
		ms_sleep(p->rules->time_to_sleep);
		print_status(p, "is thinking");
	}
	return (NULL);
}

int	start_simulation(t_rules *rules)
{
	int			i;
	pthread_t	monitor;

	rules->start_time_ms = now_ms();
	i = 0;
	while (i < rules->nb_philo)
	{
		rules->philos[i].last_meal_ms = rules->start_time_ms;
		if (pthread_create(&rules->philos[i].thread, NULL,
				philo_routine, &rules->philos[i]))
			return (1);
		i++;
	}
	if (pthread_create(&monitor, NULL, monitor_routine, rules))
		return (1);
	i = 0;
	while (i < rules->nb_philo)
	{
		pthread_join(rules->philos[i].thread, NULL);
		i++;
	}
	pthread_join(monitor, NULL);
	return (0);
}
