/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 18:10:42 by lgirault          #+#    #+#             */
/*   Updated: 2023/05/11 14:50:28 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

static int	init_fork_tab(t_philo *philo)
{
	int	i;

	i = 1;
	/*Ici on creer le tab de mutex et on attribut pour chaque case donc chaque philo un mutex (fourchette dans le sujet)*/
	philo->fork_tab = malloc(sizeof(pthread_mutex_t) * philo->nbr_philo);//protect
	while (i <= philo->nbr_philo)
	{
		pthread_mutex_init(&philo->fork_tab[i - 1], NULL);//protect
		i++;
	}
	return (0);
}

static int	init_each_philo(t_philo *philo)
{
	int	i;

	i = 1;
	/*Ici on creer le tableau de structure dans chaque case du tableau il y'aura la structure d'un philo ensuite on remplit sa structure*/
	philo->tab_each_philo = malloc(sizeof(t_each_philo) * philo->nbr_philo);//protect
	while (i <= philo->nbr_philo)
	{
		philo->tab_each_philo[i - 1].num_philo = i;
		philo->tab_each_philo[i - 1].time_to_die = philo->time_to_die;
		philo->tab_each_philo[i - 1].time_to_eat = philo->time_to_eat;
		philo->tab_each_philo[i - 1].time_to_sleep = philo->time_to_sleep;
		philo->tab_each_philo[i - 1].nbr_of_lunch = philo->nbr_of_lunch;
		philo->tab_each_philo[i - 1].time_start = time_now();
		philo->tab_each_philo[i - 1].dead = 0;
		philo->tab_each_philo[i - 1].print_mutex = philo->print_mutex;
		philo->tab_each_philo[i - 1].eat_mutex = philo->eat_mutex;
		philo->tab_each_philo[i - 1].eat_mutex = philo->dead_mutex;
		philo->tab_each_philo[i - 1].start_eat = time_now();
		philo->tab_each_philo[i - 1].fork_left = &philo->fork_tab[i - 1];
		if (i == philo->nbr_philo)
			philo->tab_each_philo[i - 1].fork_right = &philo->fork_tab[0];
		else
			philo->tab_each_philo[i - 1].fork_right = &philo->fork_tab[i];
		philo->tab_each_philo[i - 1].philo = philo;
		i++;
	}
	return (0);
}

static int	init_thread(t_philo *philo)
{
	int	i;
	
	i = 1;
	/*Ici creer chaque thread dans un tableau un pour chaque philo.
	un thread represent un philo il existe une fonction par thread qui est passe en argument de pthread_create ici routine
	et on envoie a routne une variable la structure de chaque philo*/
	philo->thread_philo = malloc(sizeof(pthread_t) * philo->nbr_philo);
	gettimeofday(&philo->time_start, NULL);
	while (i <= philo->nbr_philo)
	{
		pthread_create(&philo->thread_philo[i - 1], NULL, routine, &philo->tab_each_philo[i - 1]);//protect
		i++;
	}
	return (0);
}

static int	init_print_mutex(t_philo *philo)
{
	pthread_mutex_init(&philo->dead_mutex, NULL);
	pthread_mutex_init(&philo->eat_mutex, NULL);
	pthread_mutex_init(&philo->print_mutex, NULL);//protect
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
	philo->dead = 0;
	//gettimeofday(&philo->time_start, NULL);//Ici on gere le temps dans la struct time_start on le temps du debut du programme on utilise la fonction time_passed dans utils pour avoir le temps passe depuis
	if (init_fork_tab(philo) != 0 || init_each_philo(philo) != 0 || init_thread(philo) != 0 || init_print_mutex(philo) != 0)
		return (1);
	return(0);
}