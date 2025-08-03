/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguan <sguan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 22:28:57 by sguan             #+#    #+#             */
/*   Updated: 2025/07/19 16:27:40 by sguan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_cd_args(char **args)
{
	int	argc;

	argc = 0;
	while (args[argc])
		argc++;
	if (argc > 2)
	{
		ft_dprintf(2, "cd: too many arguments\n");
		return (1);
	}
	if (argc > 1 && args[1][0] == '-'
		&& args[1][1] != '\0' && !ft_strcmp(args[1], "--"))
	{
		ft_dprintf(2, "cd: invalid path: %s\n", args[1]);
		return (2);
	}
	return (0);
}

static char	*get_cd_dest(char **args, char **envp, int *status)
{
	char	*dest;

	if (!args[1] || args[1][0] == '\0'
		|| (args[1][0] == '~' && args[1][1] == '\0')
		|| (args[1][0] == '-' && args[1][1] == '-' && args[1][2] == '\0'))
	{
		dest = get_env_value(envp, "HOME");
		if (!dest)
			return (*status = 1, ft_dprintf(2, "cd: HOME not set\n"), NULL);
	}
	else if (args[1][0] == '-' && args[1][1] == '\0')
	{
		dest = get_env_value(envp, "OLDPWD");
		if (!dest)
			return (*status = 1, ft_dprintf(2, "cd: OLDPWD not set\n"), NULL);
		printf("%s\n", dest);
	}
	else
		dest = args[1];
	return (dest);
}

int	cd_update_env(char ***envp)
{
	char	cwd[4096];
	int		set_old;
	char	**new_env;

	if (!getcwd(cwd, sizeof(cwd)))
		cwd[0] = '\0';
	set_old = set_env_value(envp, "OLDPWD", cwd);
	if (set_old != 0)
	{
		new_env = add_env_value(envp, "OLDPWD", cwd);
		if (new_env)
			*envp = new_env;
	}
	if (getcwd(cwd, sizeof(cwd)))
	{
		if (set_env_value(envp, "PWD", cwd) != 0)
		{
			new_env = add_env_value(envp, "OLDPWD", cwd);
			if (new_env)
				*envp = new_env;
		}
	}
	return (0);
}

int	builtin_cd(char **args, char ***envp)
{
	int		status;
	char	*dest;

	status = check_cd_args(args);
	if (status)
		return (status);
	dest = get_cd_dest(args, *envp, &status);
	if (!dest)
		return (status);
	if (chdir(dest) != 0)
	{
		ft_dprintf(2, "minishell: cd: %s: %s\n", dest, strerror(errno));
		return (1);
	}
	status = cd_update_env(envp);
	return (status);
}
