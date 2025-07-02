/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:37:32 by abaryshe          #+#    #+#             */
/*   Updated: 2025/07/02 03:06:56 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redir_token(t_token_type type)
{
	if ((type == TOKEN_REDIR_INPUT) || (type == TOKEN_REDIR_OUTPUT)
		|| (type == TOKEN_REDIR_APPEND) || (type == TOKEN_REDIR_HEREDOC))
		return (1);
	else
		return (0);
}

void	add_redir_back(t_redirection **redirections, t_redirection *new_redir)
{
	t_redirection	*current;

	if (!new_redir)
		return ;
	if (!*redirections)
	{
		*redirections = new_redir;
		return ;
	}
	current = *redirections;
	while (current->next)
		current = current->next;
	current->next = new_redir;
}

t_redir_type	convert_token_type_to_redir_type(t_token_type token_type)
{
	if (token_type == TOKEN_REDIR_INPUT)
		return (REDIR_INPUT);
	else if (token_type == TOKEN_REDIR_OUTPUT)
		return (REDIR_OUTPUT);
	else if (token_type == TOKEN_REDIR_APPEND)
		return (REDIR_APPEND);
	else if (token_type == TOKEN_REDIR_HEREDOC)
		return (REDIR_APPEND);
	else
		return (REDIR_NONE);
}

t_redirection	*create_redirection(t_token **token_now,
		t_token_type token_type, t_shell_data *shell)
{
	t_redirection	*redir;

	redir = (t_redirection *)malloc(sizeof(t_redirection));
	if (!redir)
	{
		shell->internal_code = ERROR_CRITICAL;
		return (NULL);
	}
	redir->type = convert_token_type_to_redir_type(token_type);
	redir->target = ft_strdup((const char *)(*token_now)->content);
	if (!redir->target)
	{
		shell->internal_code = ERROR_CRITICAL;
		free(redir);
		return (NULL);
	}
	redir->heredoc_fd = -1;
	redir->next = NULL;
	return (redir);
}

void	process_redir_token(t_command *cmd, t_token **token_now,
		t_shell_data *shell)
{
	t_redirection	*new_redir;
	t_token_type	token_type;

	token_type = (*token_now)->type;
	*token_now = (*token_now)->next;
	if (*token_now == NULL || (*token_now)->type != TOKEN_WORD)
	{
		shell->internal_code = ERROR_SYNTAX_REDIR;
		return ;
	}
	new_redir = create_redirection(token_now, token_type, shell);
	add_redir_back(&cmd->redirections, new_redir);
	if (!new_redir || shell->internal_code != OKAY)
	{
		if (cmd)
			free_cmd(cmd);
		return ;
	}
	*token_now = (*token_now)->next;
}
