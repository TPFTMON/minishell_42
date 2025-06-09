/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 14:44:57 by abaryshe          #+#    #+#             */
/*   Updated: 2024/11/18 12:02:32 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_words(char const *s, char c);

static size_t	ft_count_wlen(char const *s, char c, size_t *index);

static void		*ft_free_all(char **strings, size_t word);

static char		**ft_alloc_words(char **strings, char const *s, char c,
					size_t count);

char			**ft_split(char const *s, char c);

static size_t	ft_count_words(char const *s, char c)
{
	size_t	count;
	int		is_word;

	count = 0;
	is_word = 0;
	while (*s)
	{
		if (is_word == 0 && *s != c)
		{
			is_word = 1;
			count++;
		}
		else if (*s == c)
			is_word = 0;
		s++;
	}
	return (count);
}

static size_t	ft_count_wlen(char const *s, char c, size_t *index)
{
	size_t	len;

	len = 0;
	while (s[*index] == c)
		(*index)++;
	while (s[*index] && s[*index] != c)
	{
		len++;
		(*index)++;
	}
	return (len);
}

static void	*ft_free_all(char **strings, size_t word)
{
	while (word > 0)
		free(strings[--word]);
	free(strings);
	return (NULL);
}

static char	**ft_alloc_words(char **strings, char const *s, char c,
		size_t count)
{
	size_t	word;
	size_t	index;
	size_t	len;
	size_t	k;

	word = 0;
	index = 0;
	while (word < count)
	{
		len = ft_count_wlen(s, c, &index);
		strings[word] = (char *)malloc(sizeof(char) * (len + 1));
		if (!strings[word])
			return (ft_free_all(strings, word));
		k = 0;
		while (k < len)
		{
			strings[word][k] = s[index - len + k];
			k++;
		}
		strings[word][k] = '\0';
		word++;
	}
	strings[count] = NULL;
	return (strings);
}

char	**ft_split(char const *s, char c)
{
	size_t	count;
	char	**strings;

	if (!s)
		return (NULL);
	count = ft_count_words(s, c);
	strings = (char **)malloc(sizeof(char *) * (count + 1));
	if (!strings)
		return (NULL);
	return (ft_alloc_words(strings, s, c, count));
}
/*
#include <stdio.h>

int	main(void)
{
	char	*epic_string;
	char	separator;
	size_t	place_hold;
	size_t	*index;
	char	**mega_array;
	size_t	i;
	size_t	words;

	epic_string = "iEPICiTESTimouiI_LOVE_FOODiwafwaf";
	separator = 'i';
	place_hold = 0;
	index = &place_hold;
	words = ft_count_words(epic_string, separator);
	printf("%zu\n", words);
	printf("%zu\n", ft_count_wlen(epic_string, separator, index));
	mega_array = ft_split(epic_string, separator);
	i = 0;
	while (i < words)
	{
		printf("%s\n", mega_array[i]);
		i++;
	}
	free(mega_array);
	return (0);
}*/
