/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 19:39:16 by abaryshe          #+#    #+#             */
/*   Updated: 2024/11/22 18:09:03 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size > 0)
	{
		while (src[i] && i < (size - 1))
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = 0;
	}
	return (ft_strlen(src));
}
/*
#include <stdio.h>
#include <string.h>
#include <bsd/string.h>

int	main(void)
{
	const char	*str;
	char dest[] = "asdfghgdkqwwyuyisdfbfg";

	// char	*dest1;
	str = "I need to copy that.";
	// dest1 = NULL;
	ft_strlcpy(dest, str, 21);
	// strlcpy(dest1, str, 21);
	printf("%s\n", dest);
	// printf("%s\n", dest1);
	return (0);
}*/
