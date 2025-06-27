/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_buffer_funcs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 08:33:01 by abaryshe          #+#    #+#             */
/*   Updated: 2025/06/24 15:57:51 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_str_buffer	*init_str_buffer(size_t initial_capacity)
{
	t_str_buffer	*buf;

	if (initial_capacity <= 0)
		initial_capacity = 16;
	buf = (t_str_buffer *)malloc(sizeof(t_str_buffer));
	if (!buf)
		return (NULL);
	buf->str = (char *)malloc(sizeof(char) * (initial_capacity));
	if (!buf->str)
	{
		free(buf);
		return (NULL);
	}
	buf->str[0] = '\0';
	buf->len = 0;
	buf->capacity = initial_capacity;
	return (buf);
}

/*
 * Ensures the buffer has enough space for additional_len of characters.
 * Duplicates the buffer's capacity until there is enough space.
 * And reallocates memory for new capacity.
 */
static int	ensure_capacity_buffer(t_str_buffer *buf, size_t additional_len)
{
	size_t	new_capacity;
	char	*new_str;

	if (buf->len + additional_len < buf->capacity)
		return (SUCCESS);
	new_capacity = buf->capacity;
	while (buf->len + additional_len >= new_capacity)
		new_capacity *= 2;
	new_str = (char *)malloc(sizeof(char) * new_capacity);
	if (!new_str)
		return (FAIL);
	ft_strcpy(new_str, buf->str);
	free(buf->str);
	buf->str = new_str;
	buf->capacity = new_capacity;
	return (SUCCESS);
}

int	append_char_buffer(t_str_buffer *buf, char c)
{
	if (ensure_capacity_buffer(buf, 1) != SUCCESS)
		return (FAIL);
	buf->str[buf->len] = c;
	buf->len++;
	buf->str[buf->len] = '\0';
	return (SUCCESS);
}

int	append_str_buffer(t_str_buffer *buf, const char *str_to_append)
{
	size_t	len_to_append;

	if (!str_to_append)
		return (SUCCESS);
	len_to_append = ft_strlen(str_to_append);
	if (ensure_capacity_buffer(buf, len_to_append) != SUCCESS)
		return (FAIL);
	ft_strlcat(buf->str, str_to_append, buf->capacity);
	buf->len += len_to_append;
	return (SUCCESS);
}

/*
 * Finalize the buffer by returning the owned string.
 * The buffer struct is freed.
 */
char	*finalize_buffer(t_str_buffer *buf)
{
	char	*final_str;

	if (!buf)
		return (NULL);
	final_str = buf->str;
	free_str_buffer(buf);
	return (final_str);
}

// int main(void)
// {
// 	t_str_buffer	*buf;

// 	buf = init_str_buffer(32);
// 	if (!buf)
// 		printf("crit\n");
// 	ensure_capacity_buffer(buf, )
// }
