/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 04:46:23 by abaryshe          #+#    #+#             */
/*   Updated: 2025/07/02 23:44:58 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_project/includes/minishell.h"

/* ||| expand_env_var ||| : */
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

	input = "what $miaou$USER+miaou31USER$COLORTERM$WHATTPATH$USER|MIOUA_mi_ER=hehehehe";
	i = 5;

	buf = init_str_buffer(4);
	if (!buf)
		printf("crit\n");
	print_str_buffer(buf);
	append_str_buffer(buf, "ab|");
	print_str_buffer(buf);
	printf("The index: [%d]\n---\n", i);
	expand_env_var(buf, input, &i, shell);
	printf("The index: [%d]\n", i);
	print_str_buffer(buf);
	printf("The index: [%d]\n---\n", i);
	expand_env_var(buf, input, &i, shell);
	printf("The index: [%d]\n", i);
	print_str_buffer(buf);

	free_str_buffer(buf);
	exit_status = shell->last_exit_status;
	free_shell(shell);
	printf("\033[0;31mEVERTYTHING WAS FREED?\n\033[0m");
	return (exit_status);
}

/* ||| append_env_name ||| : */
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

// 	input = "what $USER$COLORTERM$WHATTPATH$USER|MIOUA_mi_ER=hehehehe";
// 	i = 6;

// 	buf = init_str_buffer(4);
// 	if (!buf)
// 		printf("crit\n");
// 	print_str_buffer(buf);
// 	append_str_buffer(buf, "ab| ");
// 	print_str_buffer(buf);
// 	append_env_name(buf, input, &i, shell);
// 	printf("The index: [%d]\n", i);
// 	print_str_buffer(buf);
// 	append_char_buffer(buf, ' ');
// 	i++;
// 	append_env_name(buf, input, &i, shell);
// 	printf("The index: [%d]\n", i);
// 	print_str_buffer(buf);
// 	append_char_buffer(buf, ' ');
// 	i++;
// 	append_env_name(buf, input, &i, shell);
// 	printf("The index: [%d]\n", i);
// 	print_str_buffer(buf);

// 	free_str_buffer(buf);
// 	exit_status = shell->last_exit_status;
// 	free_shell(shell);
// 	printf("\033[0;31mEVERTYTHING WAS FREED?\n\033[0m");
// 	return (exit_status);
// }

/* ||| get_env_val ||| : */
// int	main(int argc, char const *argv[], char const *envp[])
// {
// 	t_shell_data	*shell;
// 	int				exit_status;
// 	char			*input;
// 	int				i;

// 	(void)argc;
// 	(void)argv;
// 	if (setup_signals() == FAIL)
// 		return (print_error(NULL,
// 				"Critical error: Failed to set up signals.\n"), EXIT_FAILURE);
// 	shell = init_shell_data(envp);
// 	if (!shell)
// 		return (print_error(NULL, "Error: Failed to initialize shell.\n"),
// 			EXIT_FAILURE);

// 	input = "what $COLORTERM/PATH$USER|MIOUA_mi_ER=hehehehe";
// 	i = 6;
// 	char	*res;
// 	char	*name_to_find;

// 	name_to_find = get_env_name(input, &i, shell);
// 	res = get_env_val(name_to_find, shell);
// 	printf("The env name: [%s]\nThe index: [%d]\n", name_to_find, i);
// 	printf("The %s's value: [%s]\n", name_to_find, res);
// 	free(name_to_find);
// 	free(res);

// 	exit_status = shell->last_exit_status;
// 	free_shell(shell);
// 	printf("\033[0;31mEVERTYTHING WAS FREED?\n\033[0m");
// 	return (exit_status);
// }

/* ||| get_env_name |||*/
// int	main(int argc, char const *argv[], char const *envp[])
// {
// 	t_shell_data	*shell;
// 	int				exit_status;
// 	char			*input;
// 	int				i;

// 	(void)argc;
// 	(void)argv;
// 	if (setup_signals() == FAIL)
// 		return (print_error(NULL,
// 				"Critical error: Failed to set up signals.\n"), EXIT_FAILURE);
// 	shell = init_shell_data(envp);
// 	if (!shell)
// 		return (print_error(NULL, "Error: Failed to initialize shell.\n"),
// 			EXIT_FAILURE);

// 	input = "what $WHAT=_MIAOUhehehehehehe                       hsjakdhfajkshd";
// 	i = 6;
// 	char	*res;

// 	res = get_env_name(input, &i, shell);
// 	printf("The env name: [%s]\nThe index: [%d]\n", res, i);
// 	free(res);

// 	exit_status = shell->last_exit_status;
// 	free_shell(shell);
// 	printf("\033[0;31mEVERTYTHING WAS FREED?\n\033[0m");
// 	return (exit_status);
// }
