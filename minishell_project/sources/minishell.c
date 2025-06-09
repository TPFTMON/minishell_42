/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 17:57:24 by abaryshe          #+#    #+#             */
/*   Updated: 2025/06/06 19:21:38 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_shell_loop(t_shell_data *shell)
{
	char	*input;

	while (1)
	{
		// A. Handle any pending signal from previous command or interruption
		//    This also resets shell->is_executing if a signal just terminated a command.
		process_pending_signal(shell);
		shell->is_executing = 0; // Now at prompt, not executing
		// B. Get Input
		// if (shell->interactive_mode)
		// 	shell->prompt = update_prompt(shell);
		errno = 0; // Clear errno before readline
		input = readline(shell->prompt);
		// C. Handle Signal Interruption of readline or EOF
		process_pending_signal(shell);
		if (!input)
		{ // EOF (Ctrl+D on empty line) or critical readline error
			if (shell->interactive_mode)
				write(STDOUT_FILENO, "exit\n", 5);
			break ; // Exit REPL
		}
		// D. Handle Empty Input Line (just Enter)
		if (input[0] == '\0')
		{
			if (shell->interactive_mode)
				add_history(input);
			free(input);
			continue ; // New prompt
		}
		// E. Add to History (if valid non-empty line)
		if (shell->interactive_mode)
			add_history(input);
		// F. Parse the Input
		// shell->current_command = parse_input(input, shell);
		// if (!shell->current_command)
		// { // Parsing failed (syntax error or critical error)
		// 	if (g_received_signal_value == 0)
		// 		shell->last_exit_status = SYNTAX_ERROR_CODE;
		// 	free(input);
		// 	continue ;
		// }
		printf("\033[0;32m%s\n\033[0m", input);
		free(input);
		// Input line string is now processed or copied by parser
		// G. Execute Commands
		// if (shell->current_command)
		// {
		// 	shell->is_executing = 1; // Set flag before execution
		// 	shell->last_exit_status = execute_command_pipeline(shell);
		// 	shell->is_executing = 0; // Clear flag after execution
		// 	free_command_pipeline(shell->current_command);
		// 	shell->current_command = NULL;
		// }
		// else
		// {
		// 	// Parsing failed (syntax error) or resulted in no commands.
		// 	// parse_input should have set shell->last_exit_status.
		// 	// If not, set a default error status (e.g., 2 for syntax error).
		// 	if (g_received_signal_value == 0)
		// 	{   // If no signal caused the parse fail
		// 		// shell->last_exit_status = SYNTAX_ERROR_CODE;
		// 	}
		// }
	}
}

int	main(int argc, char const *argv[], char const *envp[])
{
	t_shell_data	*shell;
	int				exit_status;

	(void)argc;
	(void)argv;
	if (setup_signals() == -1)
		return (ft_print_error(NULL, "Error: Failed to set up signals.\n"),
			EXIT_FAILURE);
	shell = init_shell_data(envp);
	if (!shell)
		return (ft_print_error(NULL, "Error: Failed to initialize shell.\n"),
			EXIT_FAILURE);
	run_shell_loop(shell);
	exit_status = shell->last_exit_status;
	free_shell(shell);
	printf("\033[0;31mEVERTYTHING WAS FREED.\n\033[0m");
	return (exit_status);
}

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
// 		ft_print_error(NULL, "Error: Failed to initialize shell.\n");
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
