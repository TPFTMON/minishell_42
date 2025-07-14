/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguan <sguan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 12:36:36 by sguan             #+#    #+#             */
/*   Updated: 2025/06/22 00:22:04 by sguan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(char **envp, const char *name)
{
	size_t	len;
	int		i;

	i = 0;
	len = ft_strlen(name);
	while (envp && envp[i])
	{
		if (ft_strncmp(envp[i], name, len) == 0 && envp[i][len] == '=')
			return (envp[i] + len + 1);
		i++;
	}
	return (NULL);
}

int	set_env_value(char ***envp, char *key, char *value)
{
	int		key_len;
	int		i;
	char	*tmp;
	char	*new_env;

	i = 0;
	key_len = ft_strlen(key);
	while (envp && (*envp)[i])
	{
		if (!ft_strncmp((*envp)[i], key, key_len) && (*envp)[i][key_len] == '=')
		{
			tmp = ft_strjoin(key, "=");
			if (!tmp)
				return (1);
			new_env = ft_strjoin(tmp, value);
			free(tmp);
			if (!new_env)
				return (1);
			free((*envp)[i]);
			(*envp)[i] = new_env;
			return (0);
		}
		i++;
	}
	return (1);
}

char	*make_env_var(char *key, char *value)
{
	char	*tmp;
	char	*res;

	tmp = ft_strjoin(key, "=");
	if (!tmp)
		return (NULL);
	res = ft_strjoin(tmp, value);
	free(tmp);
	return (res);
}

char	**add_env_value(char ***envp, char *key, char *value)
{
	char	**new_envp;
	int		i;

	if (!envp || !*envp || !key || !value)
		return (NULL);
	i = 0;
	while (envp && (*envp)[i])
		i++;
	new_envp = malloc(sizeof(char *) * (i + 2));
	if (!new_envp)
		return (NULL);
	ft_memcpy(new_envp, *envp, i * sizeof(char *));
	new_envp[i] = make_env_var(key, value);
	if (!new_envp[i])
		return (NULL);
	new_envp[i + 1] = NULL;
	free(*envp);
	*envp = new_envp;
	return (new_envp);
}
