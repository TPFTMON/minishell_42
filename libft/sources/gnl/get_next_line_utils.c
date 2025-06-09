/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 10:28:01 by abaryshe          #+#    #+#             */
/*   Updated: 2025/04/17 05:54:14 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen_gnl(char *string)
{
	size_t	i;

	i = 0;
	if (!string)
		return (0);
	while (string[i])
		i++;
	return (i);
}

char	*ft_strchr_gnl(char *string, int occurance)
{
	char	ch;

	if (!string)
		return (NULL);
	ch = occurance;
	while (*string)
	{
		if (*string == ch)
			return ((char *)string);
		string++;
	}
	if (ch == '\0')
		return ((char *)string);
	return (NULL);
}

char	*ft_strjoin_gnl(char *rest, char *buff)
{
	size_t	i;
	size_t	j;
	char	*merge;

	if (!rest)
	{
		rest = (char *)malloc(1 * sizeof(char));
		rest[0] = '\0';
	}
	if (!rest || !buff)
		return (NULL);
	merge = malloc(sizeof(char) * ((ft_strlen_gnl(rest) + ft_strlen_gnl(buff))
				+ 1));
	if (merge == NULL)
		return (NULL);
	i = -1;
	j = 0;
	if (rest)
		while (rest[++i] != '\0')
			merge[i] = rest[i];
	while (buff[j] != '\0')
		merge[i++] = buff[j++];
	merge[ft_strlen_gnl(rest) + ft_strlen_gnl(buff)] = '\0';
	ft_free_rest_gnl(&rest);
	return (merge);
}
