/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 13:00:33 by abaryshe          #+#    #+#             */
/*   Updated: 2025/07/16 10:01:27 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_n_set_parser_errors(t_shell_data *shell)
{
	if (shell->internal_code == ERROR_CRITICAL)
		print_error("minishell", ERROR_MSG_CRITICAL_MEM);
	else if (shell->internal_code == ERROR_SYNTAX_REDIR)
		print_error("minishell", ERROR_MSG_REDIR);
	else if (shell->internal_code == ERROR_SYNTAX_PIPE)
		print_error("minishell", ERROR_MSG_PIPE);
	else if (shell->internal_code == ERROR_SYNTAX_UNEXPECTED_TOKEN)
		print_error("minishell", ERROR_MSG_UNEXPECTED_TOKEN);
	else if (shell->internal_code == ERROR_UNIQUE)
		print_error("minishell", ERROR_MSG_UNIQUE);
	else
		print_error(NULL, "ERROR\n");
	set_last_exit_status(shell);
}
