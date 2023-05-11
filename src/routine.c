/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 18:18:07 by lgirault          #+#    #+#             */
/*   Updated: 2023/05/11 16:59:28 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

/*Boucle infini avec un if(pthread_mutex_lock) (si il arrive a acceder a la variable) et a l'interieur du if l'action de manger
ensuite l'action de dormir et aprs il pense tant que mutex pas dispo pour manger*/
static void	eat_routine(t_each_philo *each_philo)
{
	if (each_philo->num_philo % 2 == 0)//POur evite les violation de l'ordre de verrouillage entre different philo
	{
		pthread_mutex_lock(each_philo->fork_right);
		pthread_mutex_lock(each_philo->fork_left);
	}
	else
	{
		pthread_mutex_lock(each_philo->fork_left);
		pthread_mutex_lock(each_philo->fork_right);//Normalement si mutex pas accessible pthread_mutex_lock bloque l'execution et attend que celui ci soit acesible	
	}
	pthread_mutex_lock(&each_philo->eat_mutex);
	pthread_mutex_lock(&each_philo->print_mutex);
	each_philo->start_eat = time_now();
	pthread_mutex_unlock(&each_philo->eat_mutex);
	ft_print(each_philo, 1);
	ft_print(each_philo, 1);
	ft_print(each_philo, 2);
	pthread_mutex_unlock(&each_philo->print_mutex);
	ft_usleep(each_philo->time_to_eat);
	pthread_mutex_unlock(each_philo->fork_left);
	pthread_mutex_unlock(each_philo->fork_right);
}

static void	sleep_routine(t_each_philo *each_philo)
{
	
	pthread_mutex_lock(&each_philo->print_mutex);
	ft_print(each_philo, 3);
	pthread_mutex_unlock(&each_philo->print_mutex);
	ft_usleep(each_philo->time_to_sleep);
}

static void	think_routine(t_each_philo *each_philo)
{
	pthread_mutex_lock(&each_philo->print_mutex);
	ft_print(each_philo, 4);
	pthread_mutex_unlock(&each_philo->print_mutex);
}	

void	*check_death(void *argument)
{
	t_each_philo	*each_philo;

	each_philo = (t_each_philo *) argument;
	ft_usleep((each_philo->time_to_die + 1));
	// if (each_philo->philo->dead != 0)
	// 	return (NULL);
	pthread_mutex_lock(&each_philo->eat_mutex);
	if (time_now() - each_philo->start_eat > each_philo->time_to_die)
	{
		pthread_mutex_lock(&each_philo->print_mutex);
		ft_print(each_philo, 5);
		pthread_mutex_unlock(&each_philo->print_mutex);
		pthread_mutex_lock(&each_philo->dead_mutex);
		each_philo->philo->dead = 1;
		pthread_mutex_unlock(&each_philo->dead_mutex);
	}
	pthread_mutex_unlock(&each_philo->eat_mutex);
	return (NULL);
}

void	*routine(void *argument)
{
	t_each_philo	*each_philo;
	pthread_t	death;

	each_philo = (t_each_philo *) argument;
	each_philo->start_eat = time_now();
	if (each_philo->num_philo % 2 == 0)
		usleep(each_philo->time_to_eat / 10);//Forcement il y'en a qui devront attendre
	while (each_philo->philo->dead != 1)//tant qu'on a pas pthread_join(le thread qui supervise la mort)
	{
		pthread_create(&death, NULL, check_death, each_philo);
		if (each_philo->philo->dead == 0)
			eat_routine(each_philo);
		if (each_philo->philo->dead == 0)
			sleep_routine(each_philo);
		if (each_philo->philo->dead == 0)
			think_routine(each_philo);
		pthread_detach(death);
	}
	return (NULL);
}