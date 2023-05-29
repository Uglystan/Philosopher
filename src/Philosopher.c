/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 16:38:02 by lgirault          #+#    #+#             */
/*   Updated: 2023/05/29 17:13:06 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

int	check_all_eat(t_philo *philo)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&philo->lunch_mutex);
	while (i != philo->nbr_philo && philo->tab_each_philo[i].stop_eat != 0)
	{
		i++;
	}
	pthread_mutex_unlock(&philo->lunch_mutex);
	if (i == philo->nbr_philo)
		return (1);
	return (0);
}

int	check_death(t_philo *philo)
{
	int	i;

	i = 0;
	while (1)
	{
		ft_usleep((philo->time_to_die + 1));
		if (i + 1 == philo->nbr_philo)
			i = 0;
		if (check_all_eat(philo) == 1)
			return (1);
		pthread_mutex_lock(&philo->eat_mutex);
		if (time_now() - philo->tab_each_philo->start_eat
			>= philo->tab_each_philo->time_to_die)
		{
			pthread_mutex_lock(&philo->print_mutex);
			ft_print(&philo->tab_each_philo[i], 5);
			pthread_mutex_unlock(&philo->print_mutex);
			is_dead(&philo->tab_each_philo[i], 1);
			pthread_mutex_unlock(&philo->eat_mutex);
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
	int		i;

	i = 1;
	if (check_arg(argc, argv) == 1)
		return (ERR);
	if (init(&philo, argv) == 1)
		return (1);
	check_death(&philo);
	while (i <= philo.nbr_philo)
	{
		pthread_join(philo.thread_philo[i - 1], NULL);
		i++;
	}
	free_end(philo);
}
