/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 18:01:33 by abaryshe          #+#    #+#             */
/*   Updated: 2025/07/19 22:23:04 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	setup_shell_level(t_shell_data *shell)
{
	char	*current_shlvl_str;
	char	*new_shlvl_str;
	int		current_level;

	current_shlvl_str = get_env_val("SHLVL", shell);
	if (current_shlvl_str == NULL)
	{
		add_env_value(&shell->envp, "SHLVL", "1");
		return (SUCCESS);
	}
	current_level = ft_atoi(current_shlvl_str);
	free(current_shlvl_str);
	if (current_level < 0)
		current_level = 0;
	current_level++;
	new_shlvl_str = ft_itoa(current_level);
	if (!new_shlvl_str)
	{
		perror("minishell: ft_itoa for SHLVL failed");
		return (FAIL);
	}
	set_env_value(&shell->envp, "SHLVL", new_shlvl_str);
	free(new_shlvl_str);
	return (SUCCESS);
}

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
	if (setup_shell_level(shell) != SUCCESS)
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
		shell->prompt = "minishell> ";
		tcgetattr(STDIN_FILENO, &shell->original_termios);
	}
	shell->is_executing = 0;
	shell->internal_code = OKAY;
	return (shell);
}
