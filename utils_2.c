/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 10:51:05 by marvin            #+#    #+#             */
/*   Updated: 2025/10/30 17:27:40 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	now_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ms_sleep(long ms)
{
	long	start;

	start = now_ms();
	while ((now_ms() - start) < ms)
		usleep(500);
}

bool	get_stop(t_rules *rules)
{
	bool	value;

	pthread_mutex_lock(&rules->stop_mutex);
	value = rules->stop;
	pthread_mutex_unlock(&rules->stop_mutex);
	return (value);
}

void	set_stop(t_rules *rules, bool value)
{
	pthread_mutex_lock(&rules->stop_mutex);
	rules->stop = value;
	pthread_mutex_unlock(&rules->stop_mutex);
}

void	print_status(t_philo *p, const char *msg)
{
	long	timestamp;

	pthread_mutex_lock(&p->rules->print_mutex);
	if (!get_stop(p->rules))
	{
		timestamp = now_ms() - p->rules->start_time_ms;
		printf("%ld %d %s\n", timestamp, p->id, msg);
	}
	pthread_mutex_unlock(&p->rules->print_mutex);
}
