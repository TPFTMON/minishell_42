/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 21:03:20 by abaryshe          #+#    #+#             */
/*   Updated: 2024/11/19 21:32:52 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	len;
	char	*str;
	size_t	index;

	len = ft_strlen(s);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	index = 0;
	while (s[index] != 0)
	{
		str[index] = f(index, s[index]);
		index++;
	}
	str[index] = 0;
	return (str);
}
/*
char	ft_toup(unsigned int index, char c)
{
	(void)index;
	if (c > 96 && c < 123)
		return (c -= 32);
	return (c);
}

#include <stdio.h>

int	main(void)
{
	char	str[] = "I like you!";
	char	*mod_str;

	mod_str = ft_strmapi(str, &ft_toup);
	printf("%s\n", mod_str);
	free(mod_str);
	return (0);
}*/
