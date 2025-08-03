/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 12:56:03 by abaryshe          #+#    #+#             */
/*   Updated: 2025/07/01 14:41:59 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Creates and returns a new allocated token with the specified type and content.
 * The content is duplicated using malloc.
 * token->next is initialized to NULL.
 */
t_token	*init_token(t_token_type type, char *content, t_shell_data *shell)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
	{
		shell->internal_code = CRITICAL_ERROR;
		return (NULL);
	}
	new_token->type = type;
	new_token->content = ft_strdup((const char *)content);
	if (!new_token->content)
	{
		shell->internal_code = CRITICAL_ERROR;
		free(new_token);
		return (NULL);
	}
	new_token->next = NULL;
	return (new_token);
}

void	add_token_back(t_token **tokens, t_token *new_token)
{
	t_token	*current;

	if (!new_token)
		return ;
	if (!*tokens)
	{
		*tokens = new_token;
		return ;
	}
	current = *tokens;
	while (current->next)
		current = current->next;
	current->next = new_token;
}
