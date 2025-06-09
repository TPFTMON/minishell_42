/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 19:40:26 by abaryshe          #+#    #+#             */
/*   Updated: 2024/11/18 12:22:07 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (!dest && !src)
		return (NULL);
	if (src < dest)
	{
		i = n;
		while (i > 0)
		{
			i--;
			((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
		}
	}
	else
	{
		i = 0;
		while (i < n)
		{
			((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
			i++;
		}
	}
	return (dest);
}
/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char	s[] = {65, 66, 67, 68, 69, 33, 45};
	char	s0[] = {0, 0, 0, 0, 0, 0, 0};
	char	s_1[] = {65, 66, 67, 68, 69, 33, 45};
	char	s0_1[] = {0, 0, 0, 0, 0, 0, 0};

	printf("%s\n", s0);
	printf("%p\n", ft_memmove(s0, s, 7));
	printf("%s\n", s0);
	printf("---------------------------------------\n");
	printf("%s\n", s0_1);
	printf("%p\n", memmove(s0_1, s_1, 7));
	printf("%s\n", s0_1);
}*/
