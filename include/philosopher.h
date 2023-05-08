/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 16:38:42 by lgirault          #+#    #+#             */
/*   Updated: 2023/05/08 20:28:59 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <unistd.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

# define ERR 1
# define SUC 0

typedef struct s_each_philo
{
	int				num_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nbr_of_lunch;
	int				dead;
	struct timeval			time_start;
	pthread_mutex_t			*fork_right;
	pthread_mutex_t			*fork_left;
	pthread_mutex_t			print_mutex;
}t_each_philo;

typedef struct s_philo
{
	int				nbr_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nbr_of_lunch;
	struct timeval			time_start;
	pthread_mutex_t			*fork_tab;
	pthread_mutex_t			print_mutex;
	pthread_t			*thread_philo;
	t_each_philo			*tab_each_philo;
}t_philo;

int	ft_atoi(char *str);
int	check_arg(int argc, char **argv);
int	init(t_philo *philo, char **argv);
void	*routine(void *argument);
long int	time_passed(struct timeval time_start);

#endif