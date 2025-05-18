/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 17:57:24 by abaryshe          #+#    #+#             */
/*   Updated: 2025/05/15 23:38:26 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char const *argv[])
{
	(void)argc;
	(void)argv;
	printf("\033[0;32mThis will be our future minishell!\n\033[0mMIAOU\n");
	test_exec();
	test_pars();
	return (0);
}
