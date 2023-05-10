/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 18:18:07 by lgirault          #+#    #+#             */
/*   Updated: 2023/05/10 21:57:09 by lgirault         ###   ########.fr       */
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
	each_philo->start_eat = time_now();
	printf("\033[34;01m%ld %d has taken a fork\033[00m\n", time_now() - each_philo->time_start, each_philo->num_philo);
	printf("\033[35;01m%ld %d is eating\033[35;0m\n", time_now() - each_philo->time_start, each_philo->num_philo);
	pthread_mutex_unlock(&each_philo->print_mutex);
	usleep(each_philo->time_to_eat * 1000);
	pthread_mutex_unlock(each_philo->fork_left);
	pthread_mutex_unlock(each_philo->fork_right);
}

static void	sleep_routine(t_each_philo *each_philo)
{
	pthread_mutex_lock(&each_philo->print_mutex);
	printf("\033[33;01m%ld %d is sleeping\033[33;0m\n", time_now() - each_philo->time_start, each_philo->num_philo);
	pthread_mutex_unlock(&each_philo->print_mutex);
	usleep(each_philo->time_to_sleep * 1000);
}

static void	think_routine(t_each_philo *each_philo)
{
	pthread_mutex_lock(&each_philo->print_mutex);
	printf("\033[32;01m%ld %d is thinking\033[32;0m\n", time_now() - each_philo->time_start, each_philo->num_philo);
	pthread_mutex_unlock(&each_philo->print_mutex);
}	

void	*check_death(void *argument)
{
	t_each_philo	*each_philo;

	each_philo = (t_each_philo *) argument;
	usleep(each_philo->time_to_die * 1000);
	if (time_now() - each_philo->start_eat < each_philo->time_to_eat)
	{
		each_philo->dead = 1;
		pthread_mutex_lock(&each_philo->print_mutex);
		printf("\033[33;01m%ld %d is dead\033[33;0m\n", time_now() - each_philo->time_start, each_philo->num_philo);
		pthread_mutex_unlock(&each_philo->print_mutex);
	}
	return (NULL);
}

void	*routine(void *argument)
{
	t_each_philo	*each_philo;
	pthread_t	death;

	each_philo = (t_each_philo *) argument;
	each_philo->start_eat = time_now();
	while (each_philo->dead != 1)//tant qu'on a pas pthread_join(le thread qui supervise la mort)
	{
		pthread_create(&death, NULL, check_death, &each_philo);
		if (each_philo->num_philo % 2 == 0)
			usleep(each_philo->time_to_eat / 2);//Forcement il y'en a qui devront attendre
		eat_routine(each_philo);
		sleep_routine(each_philo);
		think_routine(each_philo);
		//UNLOCK et debut de decompte avant mort (start_time)// POur compter mort un thread en plus par philo on lance le debut du decompte qu'on ennvoie au thread dans le thread boucle inf ade gettime et si un moment le resutat de gettime mois debut et > au time to dead on stop et return
		//Compteur qui se lance des le debut et remis a 0 chaque debut de repas
		//si compteur > que sleep + eat - sleep alors mort
		//dormir
		pthread_detach(death);
	}
	return (NULL);
}