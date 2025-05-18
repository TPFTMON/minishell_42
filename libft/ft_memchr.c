/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 14:33:39 by abaryshe          #+#    #+#             */
/*   Updated: 2024/11/21 14:15:54 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*str;

	i = 0;
	str = (unsigned char *)s;
	while (i < n)
	{
		if (str[i] == ((unsigned char)c))
			return ((void *)(s + i));
		i++;
	}
	return (NULL);
}
/*
#include <stdio.h>

int	main(void)
{
	char	s[] = {0, 1, 2, 3, 4, 5};

	printf("%p\n", ft_memchr(s, 0, 0));
	printf("%p\n", ft_memchr(s, 0, 1));
	printf("%p\n", ft_memchr(s, 2, 3));
	printf("%p\n", ft_memchr(s, 6, 6));
	printf("%p\n", ft_memchr(s, 2 + 256, 3));
	return (0);
}*/
