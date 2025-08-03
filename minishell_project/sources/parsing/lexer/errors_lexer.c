/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_lexer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 15:17:07 by abaryshe          #+#    #+#             */
/*   Updated: 2025/07/16 10:01:27 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_lexer_errors(t_internal_code error_code)
{
	if (error_code == CRITICAL_ERROR)
		print_error("minishell", ERROR_MSG_CRITICAL_MEM);
	else if (error_code == ERROR_SYNTAX_SINGLE_Q)
		print_error("minishell", ERROR_MSG_SINGLE_QUOTE);
	else if (error_code == ERROR_SYNTAX_DOUBLE_Q)
		print_error("minishell", ERROR_MSG_DOUBLE_QUOTE);
	else
		print_error(NULL, "ERROR\n");
}
