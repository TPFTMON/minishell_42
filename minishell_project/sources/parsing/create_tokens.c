/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 12:56:03 by abaryshe          #+#    #+#             */
/*   Updated: 2025/06/23 16:55:45 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Creates and returns a new allocated token with the specified type and content.
 * The content is duplicated using malloc.
 * token->next is initialized to NULL.
*/
t_token	*create_token(t_token_type type, char *content)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->type = type;
	new_token->content = ft_strdup(content);
	if (!new_token->content)
	{
		free(new_token);
		return (NULL);
	}
	new_token->next = NULL;
	return (new_token);
}

void add_token_back(t_token **tokens, t_token *new_token)
{
	t_token	*current;

	if (!tokens || !new_token)
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

void create_redir_pipe_token(t_token **token, char *input, int *i)
{
	if (input[*i + 1] && (input[*i] == '<' && input[*i + 1] == '<'))
	{
		*token = create_token(TOKEN_REDIR_HEREDOC, "<<");
		*i += 2;
	}
	else if (input[*i + 1] && (input[*i] == '>' && input[*i + 1] == '>'))
	{
		*token = create_token(TOKEN_REDIR_APPEND, ">>");
		*i += 2;
	}
	else if (is_metacharacter(input[*i], 0))
	{
		if (input[*i] == '<')
			*token = create_token(TOKEN_REDIR_INPUT, "<");
		else if (input[*i] == '>')
			*token = create_token(TOKEN_REDIR_OUTPUT, ">");
		else if (input[*i] == '|')
			*token = create_token(TOKEN_PIPE, "|");
		(*i)++;
	}
	else
		*token = create_token(TOKEN_ERROR, "ERROR");
}
