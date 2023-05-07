/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 16:38:02 by lgirault          #+#    #+#             */
/*   Updated: 2023/05/07 19:57:25 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

void	*routine(void *argument)
{
	(void)argument;
	printf("SALUT\n");
	return (NULL);
}

void	init(t_philo *philo, char **argv)
{
	int	i;

	i = 1;
	philo->nbr_philo = ft_atoi(argv[1]);
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5] != NULL)
		philo->nbr_of_lunch = ft_atoi(argv[5]);
	philo->fork_tab = malloc(sizeof(pthread_mutex_t) * philo->nbr_philo);// Ici on creer le tab de mutex et on attribut pour chaque case donc chaque philo un mutex (fourchette dans le sujet)
	while (i <= philo->nbr_philo)
	{
		pthread_mutex_init(&philo->fork_tab[i - 1], PTHREAD_MUTEX_ERRORCHECK_NP);//protect
		i++;
	}
	i = 1;
	philo->tab_each_philo = malloc(sizeof(t_each_philo) * philo->nbr_philo);// Ici on creer le tableau de structure dans chaque case du tableau il y'aura la structure d'un philo ensuite on remplit sa structure
	while (i <= philo->nbr_philo)
	{
		philo->tab_each_philo[i - 1].num_philo = i;
		philo->tab_each_philo[i - 1].fork_left = &philo->thread_philo[i - 1];
		philo->tab_each_philo[i - 1].fork_right = &philo->thread_philo[i - 1];
		i++;
	}
	i = 1;
	philo->thread_philo = malloc(sizeof(pthread_t) * philo->nbr_philo);// Ici creer chaque thread dans un tableau un pour chaque philo, un thread represent un philo (il faut lui attribuer sa structure aussi ou peut etre toute la structure pour avoir acces aux autre philo (pas reussi encore))
	while (i <= philo->nbr_philo)
	{
		pthread_create(&philo->thread_philo[i - 1], NULL, routine, NULL);//pprotect
		i++;
	}
}

// int	creat_thread(t_philo *philo)
// {
// 	int	i;

// 	i = 0;
// 	while (i < philo->nbr_philo)
// 	{
// 		pthread_create(philo->id_philo[i], NULL, fct_philo, (void *) i)//creer liste avec chaque philo ?
// 		i++;
// 	}
// }

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
		printf("%lu\n", philo.thread_philo[i - 1]);
		pthread_join(philo.thread_philo[i - 1], NULL);
		i++;
	}
	// creat_thread(&philo);
	// while ()
}