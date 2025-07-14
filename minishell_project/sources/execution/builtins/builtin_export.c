/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguan <sguan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 17:11:04 by sguan             #+#    #+#             */
/*   Updated: 2025/06/27 18:54:40 by sguan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	validate_export_key(char *arg)
{
	int	i;

	if (!arg || !arg[0])
		return (0);
	if (!ft_isalpha(arg[0]) && arg[0] != '_')
		return (0);
	i = 1;
	while (arg[i])
	{
		if (arg[i] == '=')
			break ;
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	export_print(char **envp)
{
	int		i;
	char	*entry;
	char	*equal;
	char	*key;
	char	*value;

	i = 0;
	while (envp[i])
	{
		entry = envp[i];
		equal = ft_strchr(entry, '=');
		if (!equal)
			printf("declare -x %s\n", entry);
		else
		{
			key = ft_substr(entry, 0, equal - entry);
			value = ft_strdup(equal + 1);
			printf("declare -x %s=\"%s\"\n", key, value);
			free(key);
			free(value);
		}
		i++;
	}
}

void	export_update_env(char *arg, char *equal, char ***envp)
{
	char	*key;
	char	*value;
	char	**new_env;

	key = ft_substr(arg, 0, equal - arg);
	value = ft_strdup(equal + 1);
	if (!key || !value)
	{
		free(key);
		free(value);
		return ;
	}
	if (set_env_value(envp, key, value))
	{
		new_env = add_env_value(envp, key, value);
		if (new_env)
			*envp = new_env;
	}
	free(key);
	free(value);
}

int	builtin_export(char **args, char ***envp)
{
	int		i;
	char	*equal;

	i = 1;
	if (!args[1])
	{
		export_print(*envp);
		return (0);
	}
	while (args && args[i])
	{
		equal = ft_strchr(args[i], '=');
		if (!validate_export_key(args[i]))
		{
			ft_dprintf(2, "export: not an identifier: %s\n", args[i]);
			return (1);
		}
		if (equal)
			export_update_env(args[i], equal, envp);
		i++;
	}
	return (0);
}
