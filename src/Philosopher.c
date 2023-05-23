/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 16:38:02 by lgirault          #+#    #+#             */
/*   Updated: 2023/05/23 15:42:25 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

/*POur verifier mort d'un philo mutex pour chaque philo autre aue les fourchette si un philo meurt il le lock.
En paralelle un thread autre que les philos lock et delock tout les mutex de mort et si a moment il arrive pas a en lock un c'est que un philo est mort*/

int	check_death(t_philo philo)
{
	int	i;

	i = 1;
	ft_usleep((philo.time_to_die + 2));
	pthread_mutex_lock(&philo.eat_mutex);
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

int	main(int argc, char **argv)
{
	t_philo	philo;
	int	i;
	
	i = 1;
	if (check_arg(argc, argv) == 1)
		return (ERR);
	init(&philo, argv);
	//check dead
	while (i <= philo.nbr_philo)
	{
		pthread_join(philo.thread_philo[i - 1], NULL);
		i++;
	}
	//printf("FIN\n");
	// creat_thread(&philo);
	// while ()
}