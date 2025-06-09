/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 16:43:24 by abaryshe          #+#    #+#             */
/*   Updated: 2025/04/17 05:26:33 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	ch;

	ch = c;
	while (*s)
	{
		if (*s == ch)
			return ((char *)s);
		s++;
	}
	if (ch == '\0')
		return ((char *)s);
	return (NULL);
}
/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char	*str;
	char	c;
	char s[] = "tripouille";

	str = "AWe are looking for a character here";
	c = 't';
	printf("%s\n", ft_strchr(str, c + 255));
	printf("%s\n", strchr(str, c + 255));
	printf("%s\n", ft_strchr(s, c + 1024));
	printf("%s\n", strchr(s, c + 1024));
	return (0);
}*/
