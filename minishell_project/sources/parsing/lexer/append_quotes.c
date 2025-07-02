/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 13:18:34 by abaryshe          #+#    #+#             */
/*   Updated: 2025/07/01 14:41:59 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	append_single_quotes(t_str_buffer *buf, char *input, int *i, t_shell_data *shell)
{
	int	j;

	if (input[*i] != '\'')
		return ;
	++(*i);
	j = *i;
	while ((input[j]) && (input[j] != '\''))
		j++;
	if (input[j] != '\'')
	{
		shell->internal_code = ERROR_SYNTAX_SINGLE_Q;
		return ;
	}
	while (*i < j)
		append_char_buffer(buf, input[(*i)++]);
	(*i)++;
}

void	append_double_quotes(t_str_buffer *buf, char *input, int *i, t_shell_data *shell)
{
	int	j;

	if (input[*i] != '\"')
		return ;
	++(*i);
	j = *i;
	while ((input[j]) && (input[j] != '\"'))
		j++;
	if (input[j] != '\"')
	{
		shell->internal_code = ERROR_SYNTAX_DOUBLE_Q;
		return ;
	}
	while (*i < j)
	{
		if (input[*i] == '$')
			expand_env_var(buf, input, i, shell);
		else
			append_char_buffer(buf, input[(*i)++]);
	}
	(*i)++;
}
