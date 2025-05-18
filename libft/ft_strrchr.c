/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 17:37:28 by abaryshe          #+#    #+#             */
/*   Updated: 2024/11/15 10:39:19 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	ch;

	ch = c;
	i = ft_strlen(s);
	if (ch == '\0')
		return ((char *)s + i);
	while (i >= 0)
	{
		if (s[i] == ch)
			return ((char *)s + i);
		i--;
	}
	return (NULL);
}
/*
#include <stdio.h>

int	main(void)
{
	char	*str;
	char	s[] = "tripouille";
	char	c;

	str = "We are looking for a character here";
	c = 'r';
	printf("%s\n", ft_strrchr(str, c));
	printf("%s\n", ft_strrchr(s, 'z'));
	return (0);
}*/
