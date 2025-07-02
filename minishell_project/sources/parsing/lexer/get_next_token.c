/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 11:44:32 by abaryshe          #+#    #+#             */
/*   Updated: 2025/07/01 15:11:23 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_redir_pipe_token(t_token **token, char *input, int *i,
		t_shell_data *shell)
{
	if (input[*i + 1] && (input[*i] == '<' && input[*i + 1] == '<'))
	{
		*token = init_token(TOKEN_REDIR_HEREDOC, "<<", shell);
		*i += 2;
	}
	else if (input[*i + 1] && (input[*i] == '>' && input[*i + 1] == '>'))
	{
		*token = init_token(TOKEN_REDIR_APPEND, ">>", shell);
		*i += 2;
	}
	else if (is_metacharacter(input[*i], 0))
	{
		if (input[*i] == '<')
			*token = init_token(TOKEN_REDIR_INPUT, "<", shell);
		else if (input[*i] == '>')
			*token = init_token(TOKEN_REDIR_OUTPUT, ">", shell);
		else if (input[*i] == '|')
			*token = init_token(TOKEN_PIPE, "|", shell);
		(*i)++;
	}
}

void	create_word(t_str_buffer *buf, char *input, int *i, t_shell_data *shell)
{
	while ((shell->internal_code == OKAY) && (input[*i])
		&& (!(is_metacharacter(input[*i], 0))) && (!(ft_isspace(input[*i]))))
	{
		if (input[*i] == '$')
			expand_env_var(buf, input, i, shell);
		else if (input[*i] == '\'')
			append_single_quotes(buf, input, i, shell);
		else if (input[*i] == '\"')
			append_double_quotes(buf, input, i, shell);
		else
			append_char_buffer(buf, input[(*i)++]);
	}
}

void	create_word_token(t_token **token, char *input, int *i,
		t_shell_data *shell)
{
	t_str_buffer	*buf;

	buf = init_str_buffer(32);
	if (!buf)
	{
		shell->internal_code = CRITICAL_ERROR;
		*token = NULL;
		return ;
	}
	create_word(buf, input, i, shell);
	*token = init_token(TOKEN_WORD, buf->str, shell);
	free_str_buffer(buf);
}

t_token	*get_next_token(char *input, int *i, t_shell_data *shell)
{
	t_token	*new_token;

	new_token = NULL;
	if (is_metacharacter(input[*i], 0))
	{
		create_redir_pipe_token(&new_token, input, i, shell);
		if (!new_token)
			return (NULL);
		return (new_token);
	}
	else
		create_word_token(&new_token, input, i, shell);
	if (!new_token)
		return (NULL);
	return (new_token);
}
