/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 18:10:42 by lgirault          #+#    #+#             */
/*   Updated: 2023/05/29 17:24:44 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

/*Ici on creer le tab de mutex et on attribut pour chaque case
donc chaque philo un mutex (fourchette dans le sujet)*/
static int	init_fork_tab(t_philo *philo)
{
	int	i;

	i = 1;
	philo->fork_tab = malloc(sizeof(pthread_mutex_t) * philo->nbr_philo);
	if (philo->fork_tab == NULL)
	{
		free_tab_fork(*philo, i - 1, 0);
		return (1);
	}
	while (i <= philo->nbr_philo)
	{
		if (pthread_mutex_init(&philo->fork_tab[i - 1], NULL) != 0)
		{
			free_tab_fork(*philo, i - 1, 1);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	init_each_philo(t_philo *philo)
{
	int	i;

	i = 1;
	philo->tab_each_philo = malloc(sizeof(t_each_philo) * philo->nbr_philo);
	if (philo->tab_each_philo == NULL)
	{
		free_tab_fork(*philo, philo->nbr_philo, 1);
		return (1);
	}
	while (i <= philo->nbr_philo)
	{
		init_each_philo_suite(philo, i);
		if (philo->nbr_philo != 1)
		{
			if (i == philo->nbr_philo)
				philo->tab_each_philo[i - 1].fork_right = &philo->fork_tab[0];
			else
				philo->tab_each_philo[i - 1].fork_right = &philo->fork_tab[i];
		}
		philo->tab_each_philo[i - 1].philo = philo;
		i++;
	}
	return (0);
}

/*Ici creer chaque thread dans un tableau un pour chaque philo.
un thread represent un philo il existe une fonction par thread qui est
passe en argument de pthread_create ici routine
et on envoie a routne une variable la structure de chaque philo*/
static int	init_thread(t_philo *philo)
{
	int	i;

	i = 1;
	philo->thread_philo = malloc(sizeof(pthread_t) * philo->nbr_philo);
	if (philo->thread_philo == NULL)
	{
		free_init_thread(*philo, 0, 0);
		return (1);
	}
	gettimeofday(&philo->time_start, NULL);
	while (i <= philo->nbr_philo)
	{
		if (pthread_create(&philo->thread_philo[i - 1], NULL, routine,
				&philo->tab_each_philo[i - 1]) != 0)
		{
			free_init_thread(*philo, i - 1, 1);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	init_print_mutex(t_philo *philo)
{
	if (pthread_mutex_init(&philo->dead_mutex, NULL) != 0)
	{
		free_mutex(*philo, 0);
		return (1);
	}
	if (pthread_mutex_init(&philo->eat_mutex, NULL) != 0)
	{
		free_mutex(*philo, 1);
		return (1);
	}
	if (pthread_mutex_init(&philo->print_mutex, NULL) != 0)
	{
		free_mutex(*philo, 2);
		return (1);
	}
	if (pthread_mutex_init(&philo->lunch_mutex, NULL) != 0)
	{
		free_mutex(*philo, 3);
		return (1);
	}
	return (0);
}

int	init(t_philo *philo, char **argv)
{
	philo->nbr_philo = ft_atoi(argv[1]);
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5] != NULL)
		philo->nbr_of_lunch = ft_atoi(argv[5]);
	else
		philo->nbr_of_lunch = -1;
	philo->dead = 0;
	if (init_print_mutex(philo) != 0 || init_fork_tab(philo) != 0
		|| init_each_philo(philo) != 0 || init_thread(philo) != 0)
		return (1);
	return (0);
}
