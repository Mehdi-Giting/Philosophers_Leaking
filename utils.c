/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 03:17:36 by marvin            #+#    #+#             */
/*   Updated: 2025/10/27 18:07:33 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	thread_creation(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->rules->philo_count)
	{
		pthread_create(&philo[i].thread, NULL, routine, &philo[i]);
		i++;
	}
}

void	thread_join(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->rules->philo_count)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
}

int	is_space(int c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

int	ft_atol(const char *str)
{
	int			i;
	long long	sign;
	long long	res;

	i = 0;
	sign = 1;
	res = 0;
	while (is_space(str[i]) == 1)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res * sign);
}

long	get_time_in_ms(void)
{
	struct timeval	tv;
	long			res;

	gettimeofday(&tv, NULL);
	res = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (res);
}
