/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 08:32:58 by abaryshe          #+#    #+#             */
/*   Updated: 2025/06/24 16:05:01 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token_list(t_token *tokens)
{
	if (!tokens)
		return ;
	t_token	*current;
	t_token	*next;

	current = tokens;
	while (current)
	{
		next = current->next;
		free(current->content);
		free(current);
		current = next;
	}
}

// void	free_parsing(t_token *tokens, t_command *commands)
// {
// 	if (tokens)
// 		free_token_list(tokens);
// 	if (commands)
// 		free_command_list(commands);
// }


/*
 * Free the t_str_buffer and its contents entirely.
 */
void	free_str_buffer(t_str_buffer *buf)
{
	if (!buf)
		return ;
	if (buf->str)
		free(buf->str);
	free(buf);
}
