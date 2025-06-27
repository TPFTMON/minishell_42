/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_word_token.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 11:44:32 by abaryshe          #+#    #+#             */
/*   Updated: 2025/06/27 01:16:31 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_single_quoted(t_str_buffer *buf, char *input, int *i, t_shell_data *shell)
{
	int	j;

	*i++;
	j = *i;
	while (input[j] != '\'' && input[j])
		j++;
	if (input[j] != '\'')
	{
		shell->last_exit_status = SYNTAX_ERROR_SINGLE_Q;
		return ;
	}
	while (*i < j)
		append_char_buffer(buf, input[*i++]);
	*i++;
}

void	process_double_quoted(t_str_buffer *buf, char *input, int *i, t_shell_data *shell)
{
	int	j;

	*i++;
	j = *i;
	while (input[j] != '\"' && input[j])
		j++;
	if (input[j] != '\"')
	{
		shell->last_exit_status = SYNTAX_ERROR_DOUBLE_Q;
		return ;
	}
	while (*i < j)
	{
		if (input[*i] == '$')
			process_env_var(buf, input, *i, shell);
		else
			append_char_buffer(buf, input[*i++]);
	}
	*i++;
}

void	create_word_token(t_token **token, char *input, int *i, t_shell_data *shell)
{
	t_str_buffer	*buf;

	buf = init_str_buffer(32);
	if (!buf)
	{
		shell->last_exit_status = CRITICAL_ERROR;
		*token = NULL;
		return ;
	}
	while (!(is_metacharacter(input[*i], 0)) || !(ft_isspace(input[*i])))
	{
		if (input[*i] == '$')
			process_env_var(buf, input, i, shell);
		else if (input[*i] == '\'')
			process_single_quoted(buf, input, i, shell);
		else if (input[*i] == '\"')
			process_double_quoted(buf, input, i, shell);
		else
		{
			append_char_buffer(buf, input[*i]);
			*i++;
		}
	}
	*token = create_token(TOKEN_WORD, buf->str);
	free_str_buffer(buf);
}

// void	create_word_token(t_token **token, char *input, int *i)
// {
	// t_str_buffer *buf = buffer_init(32);
	// if (!buf) /* handle malloc error */;

	// while (line[i] is part of the same token)
	// {
	//     if (line[i] == '\'')
	//     {
	        // ... find closing quote at index j ...
	        // Append content between quotes to buffer using buffer_append_str or similar
	        // Example: append substring(line, i+1, j-i-1)
	//         i = j + 1;
	//     }
	//     else if (line[i] == '$')
	//     {
	//         // ... expand variable ...
	//         char *expanded_value = get_expanded_value(&line[i], shell_data, &len_of_var_name);
	//         buffer_append_str(buf, expanded_value);
	//         free(expanded_value); // if get_expanded_value allocates it
	//         i += len_of_var_name;
	//     }
	//     else
	//     {
	//         buffer_append_char(buf, line[i]);
	//         i++;
	//     }
	// }
	// Now the token is complete
	// char *final_token_value = buffer_finalize(buf);
	// Create t_token with final_token_value
// }
