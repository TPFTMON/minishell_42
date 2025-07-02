/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_token_test.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 02:53:49 by abaryshe          #+#    #+#             */
/*   Updated: 2025/07/01 23:28:26 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ||| get_next_token ||| : */
int	main(int argc, char const *argv[], char const *envp[])
{
	t_shell_data	*shell;
	int				exit_status;
	char			*input;
	int				i;
	(void)argc;
	(void)argv;
	if (setup_signals() == FAIL)
		return (print_error(NULL,
				"Critical error: Failed to set up signals.\n"), EXIT_FAILURE);
	shell = init_shell_data(envp);
	if (!shell)
		return (print_error(NULL, "Error: Failed to initialize shell.\n"),
			EXIT_FAILURE);

	input = "miaou'|''$USER'+\"$USER|'$USER'\"\t>><'$USER'_miaou";
	i = 0;

	t_token			*tokens = NULL;
	t_token			*token1 = NULL;
	t_token			*token2 = NULL;
	t_token			*token3 = NULL;
	t_token			*token4 = NULL;

	printf("The index: [%d]\n---\n", i);
	token1 = get_next_token(input, &i, shell);
	printf("The index: [%d]\n", i);
	add_token_back(&tokens, token1);
	print_token_list(tokens);
	(i)++;
	printf("The index: [%d]\n---\n", i);
	token2 = get_next_token(input, &i, shell);
	printf("The index: [%d]\n", i);
	add_token_back(&tokens, token2);
	print_token_list(tokens);
	printf("The index: [%d]\n---\n", i);
	token3 = get_next_token(input, &i, shell);
	printf("The index: [%d]\n", i);
	add_token_back(&tokens, token3);
	print_token_list(tokens);
	printf("The index: [%d]\n---\n", i);
	token4 = get_next_token(input, &i, shell);
	printf("The index: [%d]\n", i);
	add_token_back(&tokens, token4);
	print_token_list(tokens);

	free_token_list(tokens);
	exit_status = shell->last_exit_status;
	free_shell(shell);
	printf("\033[0;31mEVERTYTHING WAS FREED?\n\033[0m");
	return (exit_status);
}
