/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input_text.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 00:08:25 by abaryshe          #+#    #+#             */
/*   Updated: 2025/07/02 03:36:12 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ||| parse_input ||| : */
int	main(int argc, char const *argv[], char const *envp[])
{
	t_shell_data	*shell;
	int				exit_status;
	char			*input;
	t_token			*tokens;
	t_command		*pipeline_head;

	(void)argc;
	(void)argv;
	if (setup_signals() == FAIL)
		return (print_error(NULL,
				"Critical error: Failed to set up signals.\n"), EXIT_FAILURE);
	shell = init_shell_data(envp);
	if (!shell)
		return (print_error(NULL, "Error: Failed to initialize shell.\n"),
			EXIT_FAILURE);

	// input = "$USER+321<1miaou  '< cat mia:$?ou\t\t['|'$_'|']\t\t\t\t> what | <     what <<'$USER' \"$USER\">>a('miaou')";
	// input = ">>>|<\">$|$<\">>\"miads<<>>$_USER_<<$USER>>\">'>><>\"<<>>'<,.,.,>mia'$USER'o+$?={$USER}!='\"$USER()\"'u>><<<|>'>><<'<<>>";
	// input = "m\"iao\"u <\"$m_USER_+$?-$?\">W\"AF\"  ' !<>| ' +{$?}---\"-|||-\"";
	// input = "cat | arg1 | arg2 | arg3<miaou | j >hey <<no >>YES | <<\"no way bro\" whaaaat... >>WAF";
	input = " '|' noob <  miaou  'what$USER' $? | ls -la   >  m|wc -l< \"} $USER {\" | $USER+$?-MIAOU >> HE'E|E|E'Y ";
	tokens = lex_input(input, shell);
	print_token_list(&tokens);
	pipeline_head = build_cmd_list(&tokens, shell);
	print_cmd_list(&pipeline_head);
	if (tokens)
		free_token_list(&tokens);
	if (pipeline_head)
		free_cmd_list(&pipeline_head);

	exit_status = shell->last_exit_status;
	free_shell(shell);
	printf("Exit status: [%d]\n", exit_status);
	printf("\033[0;31mEVERTYTHING WAS FREED?\n\033[0m");
	return (exit_status);
	// PIPE IN THE END + REDIRECTONS CLEANUP
}
