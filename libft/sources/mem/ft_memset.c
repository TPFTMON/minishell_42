/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:07:50 by abaryshe          #+#    #+#             */
/*   Updated: 2024/11/16 22:31:51 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	char	*ptr;

	ptr = (char *)s;
	while (n > 0)
	{
		ptr[n - 1] = c;
		n--;
	}
	return (s);
}
/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char *ptr_miaou;
	char str[] = "miaou waf";
	ptr_miaou = malloc(10);
	if (ptr_miaou == NULL)
		return (-1);
	strncpy(ptr_miaou, str, 10);
	printf("%s\n", ptr_miaou);
	ft_memset(ptr_miaou, 0, 1);
	printf("%s\n", ptr_miaou);
	free(ptr_miaou);
	return (0);
}*/