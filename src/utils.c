/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 16:43:14 by lgirault          #+#    #+#             */
/*   Updated: 2023/05/29 17:27:33 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

int	ft_atoi(char *str)
{
	int	i;
	int	res;
	int	old_res;

	i = 0;
	res = 0;
	while (str[i] >= 48 && str[i] <= 57)
	{
		old_res = res;
		res = res * 10 + (str[i] - 48);
		if (res < old_res)
		{
			printf("Error: number too big\n");
			return (-1);
		}
		i++;
	}
	return (res);
}

long int	time_now(void)
{
	struct timeval	time_now;
	long int		time;

	gettimeofday(&time_now, NULL);
	time = (time_now.tv_sec * 1000) + (time_now.tv_usec / 1000);
	return (time);
}

void	ft_usleep(long int usec)
{
	long	time_action_start;

	time_action_start = time_now();
	usleep(usec * 850);
	while (time_now() - time_action_start < usec)
		usleep(usec / 10);
}

void	ft_print(t_each_philo *each_philo, int bool)
{
	if (is_dead(each_philo, 0) == 0)
	{
		if (bool == 1)
			printf("\033[34;01m%ld %d has taken a fork\033[00m\n",
				time_now() - each_philo->time_start, each_philo->num_philo);
		if (bool == 2)
			printf("\033[35;01m%ld %d is eating\033[35;0m\n",
				time_now() - each_philo->time_start, each_philo->num_philo);
		if (bool == 3)
			printf("\033[33;01m%ld %d is sleeping\033[33;0m\n",
				time_now() - each_philo->time_start, each_philo->num_philo);
		if (bool == 4)
			printf("\033[32;01m%ld %d is thinking\033[32;0m\n",
				time_now() - each_philo->time_start, each_philo->num_philo);
		if (bool == 5)
			printf("\033[33;01m%ld %d died\033[33;0m\n",
				time_now() - each_philo->time_start, each_philo->num_philo);
	}
}
