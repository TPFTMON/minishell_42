/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_word.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:53:29 by abaryshe          #+#    #+#             */
/*   Updated: 2025/07/02 03:03:18 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_to_argv(t_command *cmd, char *str_to_add, t_shell_data *shell)
{
	int		size;
	char	**new_argv;
	int		i;

	size = 0;
	while (cmd->argv && cmd->argv[size])
		size++;
	new_argv = (char **)malloc(sizeof(char *) * (size + 2));
	if (!new_argv)
	{
		shell->internal_code = ERROR_CRITICAL;
		return ;
	}
	i = 0;
	while (i < size)
	{
		new_argv[i] = cmd->argv[i];
		i++;
	}
	new_argv[size] = str_to_add;
	new_argv[size + 1] = NULL;
	if (cmd->argv)
		free(cmd->argv);
	cmd->argv = new_argv;
}

void	process_word_token(t_command *cmd, t_token **token_now,
		t_shell_data *shell)
{
	char	*arg_to_add;

	arg_to_add = ft_strdup((const char *)(*token_now)->content);
	if (!arg_to_add)
	{
		free_cmd(cmd);
		shell->internal_code = ERROR_CRITICAL;
		return ;
	}
	add_to_argv(cmd, arg_to_add, shell);
	if (shell->internal_code != OKAY)
	{
		if (arg_to_add)
			free(arg_to_add);
		if (cmd)
			free_cmd(cmd);
		return ;
	}
	*token_now = (*token_now)->next;
}
