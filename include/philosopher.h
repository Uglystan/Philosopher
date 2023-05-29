/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 16:38:42 by lgirault          #+#    #+#             */
/*   Updated: 2023/05/29 17:46:00 by lgirault         ###   ########.fr       */
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
	int				stop_eat;
	long int		start_eat;
	long int		time_start;
	pthread_mutex_t	*fork_right;
	pthread_mutex_t	*fork_left;
	pthread_t		death;
	struct s_philo	*philo;
}t_each_philo;

typedef struct s_philo
{
	int				nbr_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nbr_of_lunch;
	int				dead;
	struct timeval	time_start;
	pthread_mutex_t	*fork_tab;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	eat_mutex;
	pthread_mutex_t	dead_mutex;
	pthread_mutex_t	lunch_mutex;
	pthread_t		*thread_philo;
	t_each_philo	*tab_each_philo;
}t_philo;

int			ft_atoi(char *str);
int			check_arg(int argc, char **argv);
int			init(t_philo *philo, char **argv);
void		*routine(void *argument);
long int	time_now(void);
void		ft_usleep(long int usec);
void		ft_print(t_each_philo *each_philo, int bool);
int			is_dead(t_each_philo *each_philo, int bool);
void		free_mutex(t_philo philo, int bool);
void		free_tab_fork(t_philo philo, int j, int bool);
void		free_init_thread(t_philo philo, int j, int bool);
void		free_end(t_philo philo);
void		take_fork(t_each_philo *each_philo);
void		init_each_philo_suite(t_philo *philo, int i);

#endif