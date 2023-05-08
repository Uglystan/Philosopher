/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 16:38:02 by lgirault          #+#    #+#             */
/*   Updated: 2023/05/08 18:26:20 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

/*POur verifier mort d'un philo mutex pour chaque philo autre aue les fourchette si un philo meurt il le lock.
En paralelle un thread autre que les philos lock et delock tout les mutex de mort et si a moment il arrive pas a en lock un c'est que un philo est mort*/

int	main(int argc, char **argv)
{
	t_philo	philo;
	int	i;
	
	i = 1;
	if (check_arg(argc, argv) == 1)
		return (ERR);
	init(&philo, argv);
	while (i <= philo.nbr_philo)
	{
		pthread_join(philo.thread_philo[i - 1], NULL);
		i++;
	}
	printf("FIN\n");
	// creat_thread(&philo);
	// while ()
}