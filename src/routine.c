/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 18:18:07 by lgirault          #+#    #+#             */
/*   Updated: 2023/05/29 17:41:16 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

int	is_dead(t_each_philo *each_philo, int bool)
{
	pthread_mutex_lock(&each_philo->philo->dead_mutex);
	if (bool != 0)
		each_philo->philo->dead = bool;
	if (each_philo->philo->dead != 0)
	{
		pthread_mutex_unlock(&each_philo->philo->dead_mutex);
		return (1);
	}
	pthread_mutex_unlock(&each_philo->philo->dead_mutex);
	return (0);
}

static int	eat_routine(t_each_philo *each_philo)
{
	pthread_mutex_lock(&each_philo->philo->eat_mutex);
	each_philo->start_eat = time_now();
	pthread_mutex_unlock(&each_philo->philo->eat_mutex);
	ft_usleep(each_philo->time_to_eat);
	pthread_mutex_unlock(each_philo->fork_left);
	pthread_mutex_unlock(each_philo->fork_right);
	pthread_mutex_lock(&each_philo->philo->lunch_mutex);
	each_philo->nbr_of_lunch--;
	if (each_philo->nbr_of_lunch == 0)
	{
		each_philo->stop_eat++;
		pthread_mutex_unlock(&each_philo->philo->lunch_mutex);
		return (1);
	}
	pthread_mutex_unlock(&each_philo->philo->lunch_mutex);
	return (0);
}

static void	sleep_routine(t_each_philo *each_philo)
{
	pthread_mutex_lock(&each_philo->philo->print_mutex);
	ft_print(each_philo, 3);
	pthread_mutex_unlock(&each_philo->philo->print_mutex);
	ft_usleep(each_philo->time_to_sleep);
}

static void	think_routine(t_each_philo *each_philo)
{
	pthread_mutex_lock(&each_philo->philo->print_mutex);
	ft_print(each_philo, 4);
	pthread_mutex_unlock(&each_philo->philo->print_mutex);
}

void	*routine(void *argument)
{
	t_each_philo	*each_philo;

	each_philo = (t_each_philo *) argument;
	if (each_philo->num_philo % 2 == 0)
		ft_usleep(each_philo->time_to_eat / 2);
	while (is_dead(each_philo, 0) == 0)
	{
		if (is_dead(each_philo, 0) != 0)
			return (NULL);
		take_fork(each_philo);
		if (is_dead(each_philo, 0) != 0)
			return (NULL);
		if (eat_routine(each_philo) == 1)
			return (NULL);
		if (is_dead(each_philo, 0) != 0)
			return (NULL);
		sleep_routine(each_philo);
		if (is_dead(each_philo, 0) != 0)
			return (NULL);
		think_routine(each_philo);
		if (is_dead(each_philo, 0) != 0)
			return (NULL);
	}
	return (NULL);
}
