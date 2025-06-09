/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 08:33:01 by abaryshe          #+#    #+#             */
/*   Updated: 2025/06/03 05:17:04 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*expand_tokens(t_token *tokens, t_shell_data *shell)
{
}

// t_token	*expand_tokens(t_token *tokens, t_shell *shell)
// {
	// t_token	*current;
	// int		status;
//
	// if (!tokens)
		// return (NULL);
	// current = tokens;
	// while (current)
	// {
		// if (current->type == TOKEN_WORD || current->type == TOKEN_VARIABLE)
		// {
			// status = expand_token(current, shell);
			// if (status != TRUE)
			// {
				// shell->last_exit_status = status;
				// return (NULL);
			// }
		// }
		// current = current->next;
	// }
	// return (tokens);
// }
