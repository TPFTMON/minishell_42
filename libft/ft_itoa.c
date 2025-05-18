/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 14:41:16 by abaryshe          #+#    #+#             */
/*   Updated: 2024/11/15 18:34:01 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_int_len(int n)
{
	int		len;
	long	number;

	len = 0;
	number = n;
	if (number <= 0)
	{
		len++;
		number = -number;
	}
	while (number != 0)
	{
		number /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*str_n;
	int		len;
	long	number;

	len = ft_count_int_len(n);
	str_n = (char *)malloc(sizeof(char) * (len + 1));
	if (str_n == NULL)
		return (NULL);
	str_n[len] = '\0';
	number = n;
	if (number == 0)
		str_n[0] = '0';
	if (number < 0)
	{
		str_n[0] = '-';
		number = -number;
	}
	while (number != 0)
	{
		str_n[len - 1] = (number % 10) + '0';
		number /= 10;
		len--;
	}
	return (str_n);
}

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	int		num;
// 	char	*str;

// 	num = -2147483648;
// 	str = ft_itoa(num);
// 	printf("%d\n", ft_count_int_len(num));
// 	printf("%s\n", str);
// 	// printf("%lu\n", strlen(ft_itoa(num)));
// 	free(str);
// 	return (0);
// }
