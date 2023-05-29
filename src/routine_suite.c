/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_suite.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 16:29:16 by lgirault          #+#    #+#             */
/*   Updated: 2023/05/29 17:13:02 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

static int	take_fork_one_philo(t_each_philo *each_philo)
{
	if (each_philo->philo->nbr_philo == 1)
	{
		pthread_mutex_lock(each_philo->fork_left);
		pthread_mutex_lock(&each_philo->philo->print_mutex);
		ft_print(each_philo, 1);
		pthread_mutex_unlock(&each_philo->philo->print_mutex);
		ft_usleep(each_philo->time_to_die);
		pthread_mutex_lock(&each_philo->philo->print_mutex);
		ft_print(each_philo, 5);
		pthread_mutex_unlock(&each_philo->philo->print_mutex);
		is_dead(each_philo, 1);
		pthread_mutex_unlock(each_philo->fork_left);
		return (1);
	}
	return (0);
}

void	take_fork(t_each_philo *each_philo)
{
	if (take_fork_one_philo(each_philo) == 1)
		return ;
	if (each_philo->num_philo % 2 != 0)
	{
		pthread_mutex_lock(each_philo->fork_left);
		pthread_mutex_lock(each_philo->fork_right);
	}
	else
	{
		pthread_mutex_lock(each_philo->fork_right);
		pthread_mutex_lock(each_philo->fork_left);
	}
	pthread_mutex_lock(&each_philo->philo->print_mutex);
	ft_print(each_philo, 1);
	ft_print(each_philo, 1);
	ft_print(each_philo, 2);
	pthread_mutex_unlock(&each_philo->philo->print_mutex);
	if (is_dead(each_philo, 0) != 0)
	{
		pthread_mutex_unlock(each_philo->fork_left);
		pthread_mutex_unlock(each_philo->fork_right);
	}
}

void	init_each_philo_suite(t_philo *philo, int i)
{
	philo->tab_each_philo[i - 1].num_philo = i;
	philo->tab_each_philo[i - 1].time_to_die = philo->time_to_die;
	philo->tab_each_philo[i - 1].time_to_eat = philo->time_to_eat;
	philo->tab_each_philo[i - 1].time_to_sleep = philo->time_to_sleep;
	philo->tab_each_philo[i - 1].nbr_of_lunch = philo->nbr_of_lunch;
	philo->tab_each_philo[i - 1].time_start = time_now();
	philo->tab_each_philo[i - 1].dead = 0;
	philo->tab_each_philo[i - 1].stop_eat = 0;
	philo->tab_each_philo[i - 1].start_eat = time_now();
	philo->tab_each_philo[i - 1].fork_left = &philo->fork_tab[i - 1];
}
