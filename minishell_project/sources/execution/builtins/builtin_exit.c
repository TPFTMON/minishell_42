/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguan <sguan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 23:21:55 by sguan             #+#    #+#             */
/*   Updated: 2025/07/15 16:10:19 by sguan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_numeric(char *arg)
{
	int	i;

	i = 0;
	if (!arg || !arg[0])
		return (0);
	while (arg[i] == ' ')
		i++;
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	if (!ft_isdigit(arg[i]))
		return (0);
	while (ft_isdigit(arg[i]))
		i++;
	while (arg[i] == ' ')
		i++;
	if (arg[i] == '\0')
		return (1);
	return (0);
}

int	builtin_exit(t_shell_data *shell, char **args)
{
	int		exit_value;
	long	value;

	printf("exit\n");
	exit_value = shell->last_exit_status;
	if (args && args[1])
	{
		if (!is_numeric(args[1]) || (args[2] == NULL && !ft_strtol(args[1],
					&value)))
		{
			ft_dprintf(2, "exit: %s: numeric argument required\n", args[1]);
			exit_value = 2;
		}
		else if (args[2])
		{
			ft_dprintf(2, "exit: too many arguments\n");
			return (1);
		}
		else
			exit_value = (unsigned char)value;
	}
	exit(exit_value);
}
