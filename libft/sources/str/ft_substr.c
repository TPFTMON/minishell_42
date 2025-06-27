/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 19:15:25 by abaryshe          #+#    #+#             */
/*   Updated: 2025/06/27 00:50:44 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include "../../includes/libft.h"

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

	str = "THIS IS EPIC<3 HELL I NEED IT";
	little = ft_substr(str, 12, 7);
	printf("%s\n", little);
	free(little);
	return (0);
}*/
