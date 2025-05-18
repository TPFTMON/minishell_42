/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 19:22:33 by abaryshe          #+#    #+#             */
/*   Updated: 2024/11/22 18:55:32 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// size_t	ft_strlcat(char *dst, const char *src, size_t size)
// {
// 	size_t	i;
// 	size_t	j;
// 	size_t	dest_length;
// 	size_t	src_length;

// 	src_length = ft_strlen(src);
// 	dest_length = ft_strlen(dst);
// 	j = dest_length;
// 	i = 0;
// 	if (dest_length < size - 1 && size > 0)
// 	{
// 		while (src[i] && dest_length + i < size - 1)
// 		{
// 			dst[j] = src[i];
// 			j++;
// 			i++;
// 		}
// 		dst[j] = 0;
// 	}
// 	if (dest_length >= size)
// 		dest_length = size;
// 	return (dest_length + src_length);
// }

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (dest[i] && i < size)
		i++;
	while (src[j] && (i + j + 1 < size))
	{
		dest[i + j] = src[j];
		j++;
	}
	if (i < size)
		dest[i + j] = '\0';
	return (i + ft_strlen(src));
}
/*
#include <bsd/string.h>
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char	dest[40];
	char	src[18] = " I am in the end.";
	size_t	size;
	size_t	ret_ft;

	size = ft_strlen(dest);
	dest[0] = 'I';
	ret_ft = ft_strlcat(dest, src, size);
	printf("%s\nreturn value: %zu", dest, ret_ft);
	return (0);
}*/
