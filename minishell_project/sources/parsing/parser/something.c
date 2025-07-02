/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 12:59:53 by abaryshe          #+#    #+#             */
/*   Updated: 2025/07/01 17:25:23 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// /**
//  * @brief Parses one simple command segment from the token stream.
//  * A segment ends at a pipe token or the end of the token list.
//  *
//  * @param current_token A pointer to the current token pointer. This function
//  * will advance the original pointer past the tokens it consumes.
//  * @param shell The main shell data structure.
//  * @return A pointer to a newly allocated and populated t_command,
//  * or NULL on error.
//  */
// t_command	*get_next_cmd(t_token **token_now, t_shell_data *shell)
// {
// 	t_command		*cmd;

// 	cmd = init_cmd();
// 	if (!cmd)
// 		return (NULL);
// 	while ((*token_now) && ((*token_now)->type != TOKEN_PIPE))
// 	{
// 		if (is_redir_token((*token_now)->type))
// 			process_redir_token(cmd, token_now, shell);
// 		else if ((*token_now)->type == TOKEN_WORD)
// 			process_argv_token(cmd, token_now, shell);
// 	}
// 	return (cmd);
// }
