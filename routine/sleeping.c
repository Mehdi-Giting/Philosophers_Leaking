/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleeping.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 17:53:27 by marvin            #+#    #+#             */
/*   Updated: 2025/10/27 18:16:10 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	sub_routine_sleeping(t_philo *philo)
{
	long	time;

	time = get_time_in_ms() - philo->rules->start_time;
	if (philo->rules->stop_sim == 1)
		return ;
	pthread_mutex_lock(&philo->rules->print_lock);
	printf("%lo Philosopher %i is sleeping\n", time, philo->id);
	pthread_mutex_unlock(&philo->rules->print_lock);
	usleep(philo->rules->time_to_sleep * 1000);
}
