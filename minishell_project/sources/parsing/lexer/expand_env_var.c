/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 23:22:01 by abaryshe          #+#    #+#             */
/*   Updated: 2025/06/27 03:12:10 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Appends the internal_code to buffer.
 *
 * This function takes the internal_code field's value from struct shell
 * converts it into a string and appends it to the buffer buf.
 *
 * @param buf The t_str_buffer to write to.
 * @param shell The struct with the internal_code
 * @return void
 */
void	append_internal_code(t_str_buffer *buf, t_shell_data *shell)
{
	char	*last_exit_str;

	last_exit_str = ft_itoa(shell->last_exit_status);
	if (!last_exit_str)
	{
		shell->internal_code = CRITICAL_ERROR;
		return ;
	}
	append_str_buffer(buf, last_exit_str);
	free(last_exit_str);
}

/**
 * @brief Scans after ('$') to find the env variable name.
 *
 * This function is suposed to be used after the ('$') is encountered on the input.
 * This function will scan the characters after the index (i) until the non-env character is encountered.
 * After it will return the allocated with malloc name of the env variable.
 *
 * @param input The string on which to look for.
 * @param i The index from which to look for.
 * @param shell The struct with the internal_code.
 * @return (char *) The env variable name found.
 */
char	*get_env_name(char *input, int *i, t_shell_data *shell)
{
	char	*name_to_find;
	int		j;

	j = *i;
	while ((input[j]) && ((ft_isalnum(input[j]) || (input[j] == '_'))))
		j++;
	name_to_find = ft_substr((const char *)input, *i, (size_t)(j - (*i)));
	if (!name_to_find)
	{
		shell->internal_code = CRITICAL_ERROR;
		return (NULL);
	}
	*i = j;
	return (name_to_find);
}

char	*get_env_value(char *name_to_find, t_shell_data *shell)
{
	char	*value;
	char	*key;
	size_t	len;
	size_t	j;

	key = ft_strjoin(name_to_find, "=");
	if (!key)
	{
		shell->internal_code = CRITICAL_ERROR;
		return (NULL);
	}
	len = ft_strlen(key);
	j = 0;
	while ((shell->envp[j]) && ft_strncmp(shell->envp[j], key, len))
		j++;
	free(key);
	if (!shell->envp[j])
		return (NULL);
	value = ft_strdup(shell->envp[j] + len);
	if (!value)
	{
		shell->internal_code = CRITICAL_ERROR;
		return (NULL);
	}
	return (value);
}

void	append_env_name(t_str_buffer *buf, char *input, int *i, t_shell_data *shell)
{
	char	*env_value;
	char	*name_to_find;

	name_to_find = get_env_name(input, i, shell);
	env_value = get_env_value(name_to_find, shell);
	if ((!env_value) && (shell->internal_code != 0))
	{
		free(name_to_find);
		return ;
	}
	free(name_to_find);
	append_str_buffer(buf, env_value);
	free(env_value);
}

void	expand_env_var(t_str_buffer *buf, char *input, int *i, t_shell_data *shell)
{
	if (input[*i] != '$')
		return ;
	(*i)++;
	if (input[*i] == '?')
	{
		append_internal_code(buf, shell);
		(*i)++;
		return ;
	}
	else if (ft_isdigit(input[*i]))
	{
		(*i)++;
		return ;
	}
	else if ((input[*i] != '_') && (!ft_isalpha(input[*i])))
	{
		append_char_buffer(buf, '$');
		return ;
	}
	else
		append_env_name(buf, input, i, shell);
}
