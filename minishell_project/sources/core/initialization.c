/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 18:01:33 by abaryshe          #+#    #+#             */
/*   Updated: 2025/07/01 23:47:32 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**copy_envp(char const **envp)
{
	int		i;
	char	**copy;

	if (!envp)
		return (NULL);
	i = 0;
	while (envp[i])
		i++;
	copy = (char **)malloc(sizeof(char *) * (i + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		copy[i] = ft_strdup(envp[i]);
		if (!copy[i])
			free_string_array(copy);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

t_shell_data	*init_shell_data(char const **envp)
{
	t_shell_data	*shell;

	shell = (t_shell_data *)malloc(sizeof(t_shell_data));
	if (!shell)
		return (NULL);
	shell->envp = copy_envp(envp);
	if (!shell->envp)
		return (free_shell(shell));
	shell->last_exit_status = 0;
	shell->current_command = NULL;
	if (isatty(STDIN_FILENO))
		shell->interactive_mode = 1;
	else
		shell->interactive_mode = 0;
	shell->prompt = NULL;
	if (shell->interactive_mode)
	{
		shell->prompt = "\e[1;36mminishell> \e[0m";
		tcgetattr(STDIN_FILENO, &shell->original_termios);
	}
	shell->is_executing = 0;
	shell->internal_code = OKAY;
	return (shell);
}
