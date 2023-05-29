/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 15:05:48 by lgirault          #+#    #+#             */
/*   Updated: 2023/05/29 17:11:50 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

void	free_mutex(t_philo philo, int bool)
{
	if (bool == 1)
		pthread_mutex_destroy(&philo.dead_mutex);
	if (bool == 2)
	{
		pthread_mutex_destroy(&philo.dead_mutex);
		pthread_mutex_destroy(&philo.eat_mutex);
	}
	if (bool == 3)
	{
		pthread_mutex_destroy(&philo.dead_mutex);
		pthread_mutex_destroy(&philo.eat_mutex);
		pthread_mutex_destroy(&philo.print_mutex);
	}
	if (bool == 4)
	{
		pthread_mutex_destroy(&philo.dead_mutex);
		pthread_mutex_destroy(&philo.eat_mutex);
		pthread_mutex_destroy(&philo.print_mutex);
		pthread_mutex_destroy(&philo.lunch_mutex);
	}
}

void	free_tab_fork(t_philo philo, int j, int bool)
{
	int	i;

	i = 0;
	free_mutex(philo, 4);
	if (bool == 1)
	{
		while (i < j)
		{
			pthread_mutex_destroy(&philo.fork_tab[i]);
			i++;
		}
		free (philo.fork_tab);
	}
}

void	free_init_thread(t_philo philo, int j, int bool)
{
	int	i;

	i = 0;
	free_tab_fork(philo, philo.nbr_philo - 1, 1);
	free(philo.tab_each_philo);
	if (bool == 1)
	{
		while (i < j)
		{
			pthread_detach(philo.thread_philo[i]);
			i++;
		}
		free(philo.thread_philo);
	}
}

void	free_end(t_philo philo)
{
	free_tab_fork(philo, philo.nbr_philo - 1, 1);
	free(philo.tab_each_philo);
	free(philo.thread_philo);
}
