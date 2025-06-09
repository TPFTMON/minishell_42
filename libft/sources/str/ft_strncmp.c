/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 16:35:23 by abaryshe          #+#    #+#             */
/*   Updated: 2024/11/18 19:50:51 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (s1 == NULL || s2 == NULL)
		return ((unsigned char)(s1[i]) - (unsigned char)(s2[i]));
	while (i < n && s1 && n > 0)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)(s1[i]) - (unsigned char)(s2[i]));
		if (s1[i] == '\0')
			return ((unsigned char)(s1[i]) - (unsigned char)(s2[i]));
		i++;
	}
	return (0);
}
/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char	s2[] = {99, 65, 42, 88};
	char	s3[] = {99, 65, 42, 88};

	printf("%d\n", ft_strncmp(NULL, s3, 4));
	printf("%d\n", strncmp(NULL, s3, 4));
	return (0);
}*/
