/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguan <sguan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 17:42:57 by sguan             #+#    #+#             */
/*   Updated: 2025/07/19 16:31:31 by sguan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	validate_unset_key(char *arg)
{
	int	i;

	if (!arg || !arg[0])
		return (0);
	if (!ft_isalpha(arg[0]) && arg[0] != '_')
		return (0);
	i = 1;
	while (arg[i])
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	remove_env_value(char ***envp, int i)
{
	free((*envp)[i]);
	while ((*envp)[i + 1])
	{
		(*envp)[i] = (*envp)[i + 1];
		i++;
	}
	(*envp)[i] = NULL;
}

void	unset_remove_env(char *arg, char ***envp)
{
	int	arg_len;
	int	i;

	i = 0;
	arg_len = ft_strlen(arg);
	while (envp && (*envp)[i])
	{
		if (!ft_strncmp((*envp)[i], arg, arg_len) && ((*envp)[i][arg_len] == '='
				|| !(*envp)[i][arg_len]))
			remove_env_value(envp, i);
		else
			i++;
	}
}

int	builtin_unset(char **args, char ***envp)
{
	int	i;

	i = 1;
	if (!args[1])
		return (ft_dprintf(2, "unset: not enough arguments\n"));
	while (args && args[i])
	{
		if (!validate_unset_key(args[i]))
			return (ft_dprintf(2, "unset: %s: invalid parameter name\n",
					args[i]));
		unset_remove_env(args[i], envp);
		i++;
	}
	return (0);
}
