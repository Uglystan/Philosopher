/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 18:04:16 by lgirault          #+#    #+#             */
/*   Updated: 2023/05/07 19:08:17 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

int	check_number_argv(char **argv)
{
	int	i;
	int	j;

	j = 1;
	while (argv[j] != NULL)
	{
		i = 0;
		while (argv[j][i] != '\0')
		{
			if (argv[j][i] < 48 || argv[j][i] > 57)
				return (ERR);
			i++;
		}
		j++;
	}
	return (SUC);
}

int	check_number(char **argv)
{
	int	j;

	j = 1;
	while (argv[j] != NULL)
	{
		if (ft_atoi(argv[j]) <= 0)
			return (1);
		j++;
	}
	return (SUC);
}

int	check_arg(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (printf("Number of arguments invalid\n"), ERR);
	if (check_number_argv(argv) == 1)
		return (printf("Argument not number or not only positif \n"), ERR);
	if (check_number(argv) == 1)
		return (printf("Argument not valid\n"), ERR);
	if (ft_atoi(argv[1]) > 1024) //PTHREAD_THREAD_MAX
		return (printf("Too many Philosophe for this system\n"), ERR);
	return (SUC);
}
