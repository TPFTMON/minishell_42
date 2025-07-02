/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 12:09:18 by abaryshe          #+#    #+#             */
/*   Updated: 2025/07/01 23:28:26 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_project/includes/minishell.h"

/* ||| append_double_quotes ||| : */
int	main(int argc, char const *argv[], char const *envp[])
{
	t_shell_data	*shell;
	int				exit_status;
	char			*input;
	int				i;
	t_str_buffer	*buf;

	(void)argc;
	(void)argv;
	if (setup_signals() == FAIL)
		return (print_error(NULL,
				"Critical error: Failed to set up signals.\n"), EXIT_FAILURE);
	shell = init_shell_data(envp);
	if (!shell)
		return (print_error(NULL, "Error: Failed to initialize shell.\n"),
			EXIT_FAILURE);

	input = "\"I am $USER and you?\"\"|The status: $?\"+miaou31USER$COLORTERM$WHATTPATH$USER|MIOUA_mi_ER=hehehehe";
	i = 0;

	buf = init_str_buffer(4);
	if (!buf)
		printf("crit\n");
	print_str_buffer(buf);
	append_str_buffer(buf, "ab|");
	print_str_buffer(buf);
	printf("The index: [%d]\n---\n", i);
	append_double_quotes(buf, input, &i, shell);
	printf("The index: [%d]\n", i);
	print_str_buffer(buf);
	printf("The index: [%d]\n---\n", i);
	append_double_quotes(buf, input, &i, shell);
	printf("The index: [%d]\n", i);
	print_str_buffer(buf);

	free_str_buffer(buf);
	exit_status = shell->last_exit_status;
	free_shell(shell);
	printf("\033[0;31mEVERTYTHING WAS FREED?\n\033[0m");
	return (exit_status);
}

// /* ||| append_single_quotes ||| : */
// int	main(int argc, char const *argv[], char const *envp[])
// {
// 	t_shell_data	*shell;
// 	int				exit_status;
// 	char			*input;
// 	int				i;
// 	t_str_buffer	*buf;

// 	(void)argc;
// 	(void)argv;
// 	if (setup_signals() == FAIL)
// 		return (print_error(NULL,
// 				"Critical error: Failed to set up signals.\n"), EXIT_FAILURE);
// 	shell = init_shell_data(envp);
// 	if (!shell)
// 		return (print_error(NULL, "Error: Failed to initialize shell.\n"),
// 			EXIT_FAILURE);

// 	input = "'$miaou$''|$USER|'+miaou31USER$COLORTERM$WHATTPATH$USER|MIOUA_mi_ER=hehehehe";
// 	i = 0;

// 	buf = init_str_buffer(4);
// 	if (!buf)
// 		printf("crit\n");
// 	print_str_buffer(buf);
// 	append_str_buffer(buf, "ab|");
// 	print_str_buffer(buf);
// 	printf("The index: [%d]\n---\n", i);
// 	append_single_quotes(buf, input, &i, shell);
// 	printf("The index: [%d]\n", i);
// 	print_str_buffer(buf);
// 	printf("The index: [%d]\n---\n", i);
// 	append_single_quotes(buf, input, &i, shell);
// 	printf("The index: [%d]\n", i);
// 	print_str_buffer(buf);

// 	free_str_buffer(buf);
// 	exit_status = shell->last_exit_status;
// 	free_shell(shell);
// 	printf("\033[0;31mEVERTYTHING WAS FREED?\n\033[0m");
// 	return (exit_status);
// }
