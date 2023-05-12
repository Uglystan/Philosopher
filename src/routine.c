/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 18:18:07 by lgirault          #+#    #+#             */
/*   Updated: 2023/05/12 12:21:55 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

static void	take_fork(t_each_philo *each_philo)
{
	if (each_philo->num_philo % 2 != 0)//POur evite les violation de l'ordre de verrouillage entre different philo
	{
		pthread_mutex_lock(each_philo->fork_left);
		pthread_mutex_lock(each_philo->fork_right);
	}
	else
	{
		pthread_mutex_lock(each_philo->fork_right);//Normalement si mutex pas accessible pthread_mutex_lock bloque l'execution et attend que celui ci soit acesible	
		pthread_mutex_lock(each_philo->fork_left);
	}
	pthread_mutex_lock(&each_philo->philo->print_mutex);
	ft_print(each_philo, 1);
	ft_print(each_philo, 1);
	pthread_mutex_unlock(&each_philo->philo->print_mutex);
}

static void	eat_routine(t_each_philo *each_philo)
{
	pthread_mutex_lock(&each_philo->philo->print_mutex);
	ft_print(each_philo, 2);
	pthread_mutex_unlock(&each_philo->philo->print_mutex);
	pthread_mutex_lock(&each_philo->philo->eat_mutex);
	each_philo->start_eat = time_now();
	pthread_mutex_unlock(&each_philo->philo->eat_mutex);
	pthread_mutex_lock(&each_philo->philo->eat_mutex);
	each_philo->start_eat = time_now();
	pthread_mutex_unlock(&each_philo->philo->eat_mutex);
	ft_usleep(each_philo->time_to_eat);
	pthread_mutex_unlock(each_philo->fork_left);
	pthread_mutex_unlock(each_philo->fork_right);
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

void	*check_death(void *argument)
{
	t_each_philo	*each_philo;

	each_philo = (t_each_philo *) argument;
	ft_usleep((each_philo->time_to_die + 2));
	pthread_mutex_lock(&each_philo->philo->eat_mutex);
	if (each_philo->philo->dead != 0)
	{
		pthread_mutex_unlock(&each_philo->philo->eat_mutex);
		return (NULL);
	}
	if (time_now() - each_philo->start_eat >= each_philo->time_to_die)
	{
		pthread_mutex_lock(&each_philo->philo->print_mutex);
		ft_print(each_philo, 5);
		pthread_mutex_unlock(&each_philo->philo->print_mutex);
		test(each_philo, 1);
	}
	pthread_mutex_unlock(&each_philo->philo->eat_mutex);
	return (NULL);
}

int	test(t_each_philo *each_philo, int bool)
{
	pthread_mutex_lock(&each_philo->philo->test);
    if (bool != 0)
        each_philo->philo->dead = bool;
    if (each_philo->philo->dead != 0)
    {
        pthread_mutex_unlock(&each_philo->philo->test);
        return (1);
    }
    pthread_mutex_unlock(&each_philo->philo->test);
    return (0);
	// if (bool == 1)
	// {
	// 	pthread_mutex_lock(&each_philo->philo->test);
	// 	if (each_philo->philo->dead == 0)
	// 	{
	// 		pthread_mutex_unlock(&each_philo->philo->test);
	// 		return (0);
	// 	}
	// 	pthread_mutex_unlock(&each_philo->philo->test);
	// 	return (1);
	// }
	// else
	// {
	// 	pthread_mutex_lock(&each_philo->philo->test);
	// 	each_philo->philo->dead = 1;
	// 	pthread_mutex_unlock(&each_philo->philo->test);
	// 	return (0);
	// }
}

void	*routine(void *argument)
{
	t_each_philo	*each_philo;

	each_philo = (t_each_philo *) argument;
	if (each_philo->num_philo % 2 != 0)
		ft_usleep(each_philo->time_to_eat / 10);//Forcement il y'en a qui devront attendre
	each_philo->start_eat = time_now();
	while (test(each_philo, 0) == 0)//tant qu'on a pas pthread_join(le thread qui supervise la mort)
	{
		pthread_create(&each_philo->death, NULL, check_death, each_philo);
		if (test(each_philo, 0) != 0)
			return (NULL);
		take_fork(each_philo);
		if (test(each_philo, 0) != 0)
			return (NULL);
		eat_routine(each_philo);
		if (test(each_philo, 0) != 0)
			return (NULL);
		sleep_routine(each_philo);
		if (test(each_philo, 0) != 0)
			return (NULL);
		think_routine(each_philo);
		if (test(each_philo, 0) != 0)
			return (NULL);
		pthread_join(each_philo->death, NULL);
		pthread_detach(each_philo->death);
	}
	return (NULL);
}