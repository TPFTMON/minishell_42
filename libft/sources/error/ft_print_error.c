/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:52:42 by abaryshe          #+#    #+#             */
/*   Updated: 2025/05/31 09:47:17 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Prints an error message to STDERR.
 * If msg is NULL,
	uses perror to print the system error associated with 'object'.
 * If object is NULL, prints only msg.
 * Otherwise, prints "object: msg".
 */
void	ft_print_error(char *object, char *msg)
{
	char	*msg_with_colon;
	char	*full_msg;

	if (!object && !msg)
		return ;
	if (object == NULL)
		write(STDERR_FD, msg, ft_strlen(msg));
	else if (msg == NULL)
		perror(object);
	else
	{
		msg_with_colon = ft_strjoin(object, ": ");
		if (!msg_with_colon)
			return (perror("ft_strjoin in ft_print_error"));
		full_msg = ft_strjoin(msg_with_colon, msg);
		free(msg_with_colon);
		if (!full_msg)
			return (perror("ft_strjoin in ft_print_error"));
		write(STDERR_FD, full_msg, ft_strlen(full_msg));
		free(full_msg);
	}
}
