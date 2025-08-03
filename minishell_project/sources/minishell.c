/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 17:57:24 by abaryshe          #+#    #+#             */
/*   Updated: 2025/07/18 16:51:31 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t	g_received_signal_value;

void	execute_commands(t_shell_data *shell)
{
	shell->is_executing = 1;
	executor(shell, shell->current_command);
	shell->is_executing = 0;
	free_cmd_list(&shell->current_command);
	shell->current_command = NULL;
}

void	run_shell_loop(t_shell_data *shell)
{
	char	*input;

	while (1)
	{
		shell->is_executing = 0;
		process_last_status(shell);
		process_pending_signal(shell);
		input = readline(shell->prompt);
		process_pending_signal(shell);
		if (!input)
			break ;
		if (shell->interactive_mode)
			add_history(input);
		shell->current_command = parse_input(input, shell);
		if (input)
			free(input);
		if (!shell->current_command)
			continue ;
		if (shell->current_command)
			execute_commands(shell);
	}
}

int	main(int argc, char const *argv[], char const *envp[])
{
	t_shell_data	*shell;
	int				exit_status;

	(void)argc;
	(void)argv;
	if (configure_interactive_signals() == FAIL)
		return (print_error_with_code(NULL, ERROR_MSG_CRITICAL_SIGNALS_INTER,
				EXIT_FAILURE));
	shell = init_shell_data(envp);
	if (!shell)
		return (print_error_with_code(NULL, ERROR_MSG_CRITICAL_SHELL_DATA,
				EXIT_FAILURE));
	run_shell_loop(shell);
	exit_status = shell->last_exit_status;
	if (shell->interactive_mode)
		write(STDOUT_FILENO, EXIT_MSG_OK, 33);
	free_shell(shell);
	return (exit_status);
}

// void	run_shell_loop(t_shell_data *shell)
// {
// 	char	*input;

// 	while (1)
// 	{
// 		process_last_status(shell);
// 		process_pending_signal(shell);
// 		shell->is_executing = 0;
// 		// if (shell->interactive_mode)
// 		// 	shell->prompt = update_prompt(shell);
// 		// errno = 0;
// 		input = readline(shell->prompt);
// 		process_pending_signal(shell);
// 		if (!input)
// 			break ;
// 		if (input[0] == '\0')
// 		{
// 			if (shell->interactive_mode)
// 				add_history(input);
// 			free(input);
// 			continue ;
// 		}
// 		if (shell->interactive_mode)
// 			add_history(input);
// 		shell->current_command = parse_input(input, shell);
// 		if (!shell->current_command)
// 		{
// 			if (input)
// 				free(input);
// 			continue ;
// 		}
// 		free(input);
// print_cmd_list(&shell->current_command);
// 		if (shell->current_command)
// 		{
// 			shell->is_executing = 1;
// 			executor(shell, shell->current_command);
// 			free_cmd_list(&shell->current_command);
// 			shell->current_command = NULL;
// 		}
// 	}
// }

// int				i = 0;
// while (shell->envp[i])
// {
// 	printf("%s\n", shell->envp[i]);
// 	i++;
// }

// void	readline_loop(t_shell_data *shell)
// {
// 	char	*input;

// 	while (1)
// 	{
// 		process_pending_signal(shell);
// 		input = readline(shell->prompt);
// 		process_pending_signal(shell);
// 		if (!input)
// 			break ;
// 		if (shell->interactive_mode)
// 			add_history(input);
// 		if (input[0] == '\0')
// 		{
// 			free(input);
// 			continue ;
// 		}
// 		printf("\033[0;32m%s\n\033[0m", input);
// 		free(input);
// 	}
// }

// int	main(int argc, char const *argv[], char const *envp[])
// {
// 	t_shell_data	*shell;
// 	int		exit_status;

// 	(void)argc;
// 	(void)argv;
// 	setup_signals();
// 	shell = init_shell_data(envp);
// 	if (!shell)
// 	{
// 		print_error(NULL, "Error: Failed to initialize shell.\n");
// 		return (EXIT_FAILURE);
// 	}
// 	readline_loop(shell);
// 	exit_status = shell->last_exit_status;
// 	free_shell(shell);
// 	printf("\033[0;31mEVERTYTHING WAS FREED.\n\033[0m");
// 	return (exit_status);
// }

// int i = 0;
// while (shell->envp[i])
// {
// 	printf("%s\n", shell->envp[i]);
// 	i++;
// }

// if (shell->interactive_mode)
// 	printf("interactive mode\n");
// else
// 	printf("non-interactive mode\n");
