/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_status_test.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 02:01:45 by abaryshe          #+#    #+#             */
/*   Updated: 2025/07/01 23:28:26 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_project/includes/minishell.h"

int	main(int argc, char const *argv[], char const *envp[])
{
	t_shell_data	*shell;
	int				exit_status;
	t_str_buffer	*buf;
	char			*input;

	(void)argc;
	(void)argv;
	if (setup_signals() == FAIL)
		return (print_error(NULL,
				"Critical error: Failed to set up signals.\n"), EXIT_FAILURE);
	shell = init_shell_data(envp);
	if (!shell)
		return (print_error(NULL, "Error: Failed to initialize shell.\n"),
			EXIT_FAILURE);

	input = "";
	buf = init_str_buffer(4);
	if (!buf)
		printf("crit\n");
	print_str_buffer(buf);
	append_str_buffer(buf, "ab|");

	append_str_buffer(buf, "here is the status: ");
	append_last_exit_status(buf, shell);
	print_str_buffer(buf);
	shell->last_exit_status = 666;
	append_str_buffer(buf, "here is the status: ");
	append_last_exit_status(buf, shell);
	print_str_buffer(buf);
	shell->last_exit_status = 127;
	append_str_buffer(buf, "here is the status: ");
	append_last_exit_status(buf, shell);
	print_str_buffer(buf);
	shell->last_exit_status = 0;
	append_str_buffer(buf, "here is the status: ");
	append_last_exit_status(buf, shell);
	print_str_buffer(buf);

	free_str_buffer(buf);
	exit_status = shell->last_exit_status;
	free_shell(shell);
	printf("\033[0;31mEVERTYTHING WAS FREED?\n\033[0m");
	return (exit_status);
}
