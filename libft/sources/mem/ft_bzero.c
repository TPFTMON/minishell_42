/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 10:29:19 by abaryshe          #+#    #+#             */
/*   Updated: 2024/11/14 14:23:53 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
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
	ft_bzero(ptr_miaou, 5);
	printf("%s\n", ptr_miaou);
	free(ptr_miaou);
	return (0);
}*/