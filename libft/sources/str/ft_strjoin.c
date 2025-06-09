/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 19:54:32 by abaryshe          #+#    #+#             */
/*   Updated: 2025/04/17 05:23:15 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*merge;
	size_t	index;

	len = ft_strlen(s1) + ft_strlen(s2);
	merge = (char *)malloc(sizeof(char) * (len + 1));
	if (!merge)
		return (NULL);
	index = 0;
	while (*s1 != '\0')
	{
		merge[index] = *s1;
		if (*s1 != '\0')
			index++;
		s1++;
	}
	while (*s2 != '\0')
	{
		merge[index] = *s2;
		index++;
		s2++;
	}
	merge[index] = '\0';
	return (merge);
}
/*
#include <stdio.h>

int	main(void)
{
	char	*str1;
	char	*str2;
	char	*merge;

	str1 = "Wow. I CAN ";
	str2 = "COMBINE DA STRINGS!";
	printf("%lu\n", (ft_strlen(str1) + ft_strlen(str2)));
	merge = ft_strjoin(str1, str2);
	printf("%s\n", merge);
	free(merge);
	return (0);
}*/
