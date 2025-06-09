/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 19:15:25 by abaryshe          #+#    #+#             */
/*   Updated: 2024/11/17 21:33:16 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	s_length;
	char	*little;

	if (!s)
		return (NULL);
	s_length = ft_strlen(s);
	if (start >= s_length)
		return (ft_strdup(""));
	if (start + len > s_length)
		len = s_length - start;
	little = (char *)malloc(sizeof(char) * (len + 1));
	if (!little)
		return (NULL);
	ft_strlcpy(little, &s[start], (len + 1));
	return (little);
}
/*
#include <stdio.h>

int	main(void)
{
	char	*str;
	char	*little;

	str = "THIS IS EPIC<3. I NEED IT";
	little = ft_substr(str, 0, 7);
	printf("%s\n", little);
	free(little);
	return (0);
}*/
