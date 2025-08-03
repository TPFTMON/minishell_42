/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 19:12:39 by abaryshe          #+#    #+#             */
/*   Updated: 2025/07/19 16:55:13 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	main(int argc, char const *argv[], char const *envp[])
// {
// 	t_shell_data	*shell;
// 	int				exit_status;
// 	char			*input;
// 	int				i;
// 	t_token			*tokens = NULL;

// 	(void)argc;
// 	(void)argv;
// 	if (setup_signals() == FAIL)
// 		return (print_error(NULL,
// 				"Critical error: Failed to set up signals.\n"), EXIT_FAILURE);
// 	shell = init_shell_data(envp);
// 	if (!shell)
// 		return (print_error(NULL, "Error: Failed to initialize shell.\n"),
// 			EXIT_FAILURE);

// 	input = " < cat miaou\t\t\t\t\t\t> what
// | <     what <<'$USER' \"$USER\">>a('miaou')";
// 	i = 0;

// 	tokens = tokenize_input(tokens, input, shell);
// 	print_token_list(tokens);

// 	free_token_list(tokens);
// 	exit_status = shell->last_exit_status;
// 	free_shell(shell);
// 	printf("\033[0;31mEVERTYTHING WAS FREED?\n\033[0m");
// 	return (exit_status);
// }

/* ||| lex_input ||| : */
// int	main(int argc, char const *argv[], char const *envp[])
// {
// 	t_shell_data	*shell;
// 	int				exit_status;
// 	char			*input;
// 	int				i;
// 	t_token			*tokens;

// 	(void)argc;
// 	(void)argv;
// 	if (setup_signals() == FAIL)
// 		return (print_error(NULL,
// 				"Critical error: Failed to set up signals.\n"), EXIT_FAILURE);
// 	shell = init_shell_data(envp);
// 	if (!shell)
// 		return (print_error(NULL, "Error: Failed to initialize shell.\n"),
// 			EXIT_FAILURE);

// 	// input = "$USER+321<1miaou  '< cat mia:$?ou\t\t['|'$_'|']
// \t\t\t\t> what | <     what <<'$USER' \"$USER\">>a('miaou')";
// 	input = ">>>|<\">|<\">>>'>><><<>>'<,.,.,>
//mia'$USER'o+$?={$USER}!='\"$USER()\"'u>><<<|>>><<<<>>";
// 	i = 0;

// 	tokens = lex_input(input, shell);
// 	print_token_list(&tokens);

// 	free_token_list(&tokens);
// 	exit_status = shell->last_exit_status;
// 	free_shell(shell);
// 	printf("\033[0;31mEVERTYTHING WAS FREED?\n\033[0m");
// 	return (exit_status);
// }
