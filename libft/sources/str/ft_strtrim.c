/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 20:34:54 by abaryshe          #+#    #+#             */
/*   Updated: 2024/11/19 13:35:19 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	index;
	size_t	len;
	size_t	trim_len;
	char	*trim_str;

	if (s1 != 0 && set != 0)
	{
		index = 0;
		while (s1[index] && ft_strchr(set, s1[index]))
			index++;
		len = ft_strlen(s1);
		while (s1[len - 1] && ft_strchr(set, s1[len - 1]) && len > index)
			len--;
		trim_len = len - index;
		trim_str = (char *)malloc(sizeof(char) * (trim_len + 1));
		if (!trim_str)
			return (NULL);
		ft_strlcpy(trim_str, &s1[index], (trim_len + 1));
		return (trim_str);
	}
	return (NULL);
}
/*
#include <stdio.h>

int	main(void)
{
	char	*s1;
	char	*set;
	char	*trimmed;

	s1 = "# 7 9 8 ## ";
	set = " #798";
	printf("%s\n", s1);
	trimmed = ft_strtrim(s1, set);
	printf("%s\n", trimmed);
	free(trimmed);
	return (0);
}*/
