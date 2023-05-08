/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 18:18:07 by lgirault          #+#    #+#             */
/*   Updated: 2023/05/08 20:28:49 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

/*Boucle infini avec un if(pthread_mutex_lock) (si il arrive a acceder a la variable) et a l'interieur du if l'action de manger
ensuite l'action de dormir et aprs il pense tant que mutex pas dispo pour manger*/
static void	eat_routine(t_each_philo *each_philo)
{
	pthread_mutex_lock(each_philo->fork_left);
	pthread_mutex_lock(each_philo->fork_right);//Normalement si mutex pas accessible pthread_mutex_lock bloque l'execution et attend que celui ci soit acesible
	pthread_mutex_lock(&each_philo->print_mutex);
	printf("%ld %d has taken a fork\n", time_passed(each_philo->time_start), each_philo->num_philo);
	printf("%ld %d is eating\n", time_passed(each_philo->time_start), each_philo->num_philo);
	pthread_mutex_unlock(&each_philo->print_mutex);
	usleep(each_philo->time_to_eat * 1000);
	pthread_mutex_unlock(each_philo->fork_left);
	pthread_mutex_unlock(each_philo->fork_right);
}

static void	sleep_routine(t_each_philo *each_philo)
{
	pthread_mutex_lock(&each_philo->print_mutex);
	printf("%ld %d is sleeping\n", time_passed(each_philo->time_start), each_philo->num_philo);
	pthread_mutex_unlock(&each_philo->print_mutex);
	usleep(each_philo->time_to_sleep * 1000);
}

static void	think_routine(t_each_philo *each_philo)
{
	pthread_mutex_lock(&each_philo->print_mutex);
	printf("%ld %d is thinking\n", time_passed(each_philo->time_start), each_philo->num_philo);
	pthread_mutex_unlock(&each_philo->print_mutex);
}	

void	*routine(void *argument)
{
	t_each_philo	*each_philo;

	each_philo = (t_each_philo *) argument;
	while (1)
	{
		if (each_philo->num_philo % 2 == 0)
			usleep(each_philo->time_to_eat / 2);//Forcement il y'en a qui devront attendre
		eat_routine(each_philo);
		sleep_routine(each_philo);
		think_routine(each_philo);
		//UNLOCK et debut de decompte avant mort (start_time)
		//dormir
	}
	return (NULL);
}