/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 14:53:11 by abaryshe          #+#    #+#             */
/*   Updated: 2025/07/01 15:13:54 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_last_exit_status(t_shell_data *shell)
{
	if ((shell->internal_code == OKAY) || (shell->internal_code == ERROR_CRITICAL))
		shell->last_exit_status = shell->internal_code;
	else
		shell->last_exit_status = 2;
	shell->internal_code = OKAY;
}
