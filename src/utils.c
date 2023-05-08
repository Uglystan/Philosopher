/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 16:43:14 by lgirault          #+#    #+#             */
/*   Updated: 2023/05/08 20:28:54 by lgirault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

int	ft_atoi(char *str)
{
	int	i;
	int	res;
	int	old_res;

	i = 0;
	res = 0;
	while (str[i] >= 48 && str[i] <= 57)
	{
		old_res = res;
		res = res * 10 + (str[i] - 48);
		if (res < old_res)
			return (printf("Error: number too big\n") ,-1);
		i++;
	}
	return (res);
}

long int	time_passed(struct timeval time_start)
{
	struct timeval	time_now;

	gettimeofday(&time_now, NULL);
	return((time_now.tv_sec - time_start.tv_sec) * 1000 + (time_now.tv_usec - time_start.tv_usec) / 1000);
}
