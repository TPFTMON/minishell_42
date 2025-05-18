/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 18:50:27 by abaryshe          #+#    #+#             */
/*   Updated: 2025/04/17 06:09:57 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	index;
	int	sign;
	int	result;

	index = 0;
	while ((str[index] == 32) || (str[index] > 8 && str[index] < 14))
		index++;
	sign = 1;
	if (str[index] == '-' || str[index] == '+')
	{
		if (str[index] == '-')
			sign = -sign;
		(index)++;
	}
	result = 0;
	while (str[index] >= '0' && str[index] <= '9')
		result = result * 10 + (str[index++] - '0');
	return (result * sign);
}
/*
#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	char	str[] = " \n\f\n\r \v\n\t\n\n+967230ab5432";
	int		num_1;
	int		num_2;

	num_1 = ft_atoi(str);
	num_2 = atoi(str);
	printf("%d\n", num_1);
	printf("%d\n", num_2);
	return (0);
}*/
