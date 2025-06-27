/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_env_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 23:22:01 by abaryshe          #+#    #+#             */
/*   Updated: 2025/06/27 03:12:10 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_last_exit_status(t_str_buffer *buf, t_shell_data *shell)
{
	char	*last_exit_str;

	last_exit_str = ft_itoa(shell->last_exit_status);
	append_str_buffer(buf, last_exit_str);
	free(last_exit_str);
}

char	*get_env_var_name(char *input, int *i, t_shell_data *shell)
{
	char	*name_to_find;
	int		j;

	j = *i;
	while (ft_isalnum(input[j] || input[j] == '_'))
		j++;
	name_to_find = ft_substr(input, (*i + 1), (j - *i));
	if (!name_to_find)
	{
		shell->last_exit_status = CRITICAL_ERROR;
		return (NULL);
	}
	return (name_to_find);
	*i = j;
}

char	*get_env_value(char *name_to_find, t_shell_data *shell)
{
	char	*value;
	char	*key;
	size_t	len;
	size_t	i;

	key = ft_strjoin(name_to_find, "=");
	len = ft_strlen(key);
	while (ft_strncmp(shell->envp[i], key, len))
		i++;
	free(key);
	if (!shell->envp[i])
		return (NULL);
	value = ft_strdup(shell->envp[i]);
	if (!value)
	{
		shell->last_exit_status = CRITICAL_ERROR;
		return (NULL);
	}
	return (value);
}

void	process_env_var_name(t_str_buffer *buf, char *input, int *i, t_shell_data *shell)
{
	char	*env_value;
	char	*name_to_find;

	name_to_find = get_env_var_name(input, i, shell);
	env_value = get_env_value(name_to_find, shell->envp);
	free(name_to_find);
	append_str_buffer(buf, env_value);
	free(env_value);
}

void	process_env_var(t_str_buffer *buf, char *input, int *i, t_shell_data *shell)
{
	*i++;
	if (input[*i] == '?')
	{
		process_last_exit_status(buf, shell);
		*i++;
		return ;
	}
	else if (ft_isdigit(input[*i]))
	{
		*i++;
		return ;
	}
	else if (!ft_isalpha(input[*i]) || input[*i] == '_')
	{
		append_char_buffer(buf, '$');
		return ;
	}
	else
		process_env_var_name(buf, input, i, shell);
}
