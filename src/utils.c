/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirault <lgirault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 16:43:14 by lgirault          #+#    #+#             */
/*   Updated: 2023/05/07 19:01:33 by lgirault         ###   ########.fr       */
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