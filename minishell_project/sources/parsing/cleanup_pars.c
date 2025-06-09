/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_pars.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 08:32:58 by abaryshe          #+#    #+#             */
/*   Updated: 2025/06/03 05:23:02 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token_list(t_token *tokens)
{
}

void	free_parsing(t_token *tokens, t_command *commands)
{
	if (tokens)
		free_token_list(tokens);
	if (commands)
		free_commands(commands);
}
