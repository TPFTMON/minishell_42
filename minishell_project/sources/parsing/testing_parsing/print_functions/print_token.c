/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 10:27:22 by abaryshe          #+#    #+#             */
/*   Updated: 2025/07/02 01:00:59 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"

// void	print_token(t_token *token)
// {
// 	if (!token)
// 	{
// 		printf("(NULL)\n");
// 		return ;
// 	}
// 	printf("Token Type: [%d], Content: [%s]\n \\/\n", token->type,
// 		token->content);
// }

// void	print_token_list(t_token **tokens)
// {
// 	t_token	*current;
// 	size_t	i;

// 	current = *tokens;
// 	i = 0;
// 	while (current)
// 	{
// 		printf("Token's index: [%zu], ", i++);
// 		print_token(current);
// 		current = current->next;
// 	}
// 	print_token(current);
// 	printf("\n");
// }
