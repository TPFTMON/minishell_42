/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguan <sguan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:23:37 by sguan             #+#    #+#             */
/*   Updated: 2025/07/19 16:30:37 by sguan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_n_flag(const char *arg)
{
	int	i;

	i = 1;
	if (!arg || arg[0] != '-')
		return (false);
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

int	builtin_echo(char **args)
{
	int		i;
	bool	n_flag;

	i = 1;
	n_flag = false;
	while (args[i] && is_n_flag(args[i]))
	{
		n_flag = true;
		i++;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (!n_flag)
		printf("\n");
	return (0);
}
