/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucasgirault <lucasgirault@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 16:38:02 by lgirault          #+#    #+#             */
/*   Updated: 2023/05/25 22:58:52 by lucasgiraul      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

/*POur verifier mort d'un philo mutex pour chaque philo autre aue les fourchette si un philo meurt il le lock.
En paralelle un thread autre que les philos lock et delock tout les mutex de mort et si a moment il arrive pas a en lock un c'est que un philo est mort*/

int	check_death(t_philo *philo)
{
	int	i;

	i = 0;
	ft_usleep((philo->time_to_die + 2));
	while (1)
	{
		if (i + 1 == philo->nbr_philo)
			i = 0;
		pthread_mutex_lock(&philo->eat_mutex);
		if (philo->dead != 0)
		{
			pthread_mutex_unlock(&philo->eat_mutex);
			return (1);
		}
		if (time_now() - philo->tab_each_philo->start_eat >= philo->tab_each_philo->time_to_die)
		{
			pthread_mutex_lock(&philo->print_mutex);
			ft_print(&philo->tab_each_philo[i], 5);
			pthread_mutex_unlock(&philo->print_mutex);
			test(&philo->tab_each_philo[i], 1);
			return (1);
		}
		pthread_mutex_unlock(&philo->eat_mutex);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo	philo;
	int	i;
	
	i = 1;
	if (check_arg(argc, argv) == 1)
		return (ERR);
	init(&philo, argv);
	check_death(&philo);
	while (i <= philo.nbr_philo)
	{
		pthread_join(philo.thread_philo[i - 1], NULL);
		i++;
	}
	//printf("FIN\n");
	// creat_thread(&philo);
	// while ()
}