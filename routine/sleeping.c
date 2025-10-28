/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleeping.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 17:53:27 by marvin            #+#    #+#             */
/*   Updated: 2025/10/28 05:50:03 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	sub_routine_sleeping(t_philo *philo)
{
	long long	time;

	time = get_time_in_ms() - philo->rules->start_time;
	pthread_mutex_lock(&philo->rules->print_lock);
	printf("%llo %i is sleeping\n", time, philo->id);
	pthread_mutex_unlock(&philo->rules->print_lock);
	usleep(philo->rules->time_to_sleep * 1000);
}
