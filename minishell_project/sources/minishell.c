/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 17:57:24 by abaryshe          #+#    #+#             */
/*   Updated: 2025/07/14 17:19:21 by abaryshe         ###   ########.fr       */
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
				write(STDOUT_FILENO, EXIT_MSG_OK, 33);
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
		shell->current_command = parse_input(input, shell);
		if (!shell->current_command)
		{
			if (input)
				free(input);
			continue ;
		}
		// printf("\033[0;32m%s\n\033[0m", input);
		free(input);
		print_cmd_list(&shell->current_command);
		// free_cmd_list(&shell->current_command);
		// Input line string is now processed or copied by parser
		// G. Execute Commandse
		if (shell->current_command)
		{
			shell->is_executing = 1; // Set flag before execution
			executor(shell, shell->current_command);
			shell->is_executing = 0; // Clear flag after execution
			free_cmd_list(&shell->current_command);
			shell->current_command = NULL;
		}
	}
}

int	main(int argc, char const *argv[], char const *envp[])
{
	t_shell_data	*shell;
	int				exit_status;

	(void)argc;
	(void)argv;
	if (setup_signals() == FAIL)
		return (print_error(NULL,
				"Critical error: Failed to set up signals.\n"), EXIT_FAILURE);
	shell = init_shell_data(envp);
	if (!shell)
		return (print_error(NULL, "Error: Failed to initialize shell.\n"),
			EXIT_FAILURE);
	run_shell_loop(shell);

	// int				i = 0;
	// while (shell->envp[i])
	// {
	// 	printf("%s\n", shell->envp[i]);
	// 	i++;
	// }

	exit_status = shell->last_exit_status;
	free_shell(shell);
	printf("\033[0;31mEVERTYTHING WAS FREED?\n\033[0m");
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
