/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 03:17:36 by marvin            #+#    #+#             */
/*   Updated: 2025/10/30 17:27:48 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_space(int c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

long long	ft_atol(const char *str)
{
	long long	i;
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

int	parse_args(int ac, char **av, t_rules *rules)
{
	rules->nb_philo = (int)ft_atol(av[1]);
	rules->time_to_die = ft_atol(av[2]);
	rules->time_to_eat = ft_atol(av[3]);
	rules->time_to_sleep = ft_atol(av[4]);
	if (ac == 6)
		rules->must_eat = (int)ft_atol(av[5]);
	else
		rules->must_eat = -1;
	return (0);
}

int	one_philo(char **argv)
{
	if (ft_atol(argv[1]) == 1)
	{
		printf("%d 1 has taken a fork\n", 0);
		usleep(ft_atol(argv[2]) * 1000);
		printf("%lld 1 died\n", ft_atol(argv[2]));
		return (1);
	}
	return (0);
}
