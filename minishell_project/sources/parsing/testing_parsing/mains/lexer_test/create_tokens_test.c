/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initg_create_tokens.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 10:23:34 by abaryshe          #+#    #+#             */
/*   Updated: 2025/06/24 14:26:16 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_project/includes/minishell.h"

// init_token + add_token_back + free_token_list
// int main(void)
// {
// 	t_token	*tokens;
// 	t_token	*token1;
// 	t_token	*token2;
// 	t_token	*token3;
// 	t_token	*token4;
// 	t_token	*token5;
// 	t_token	*token6;
// 	t_token	*token7;
// 	t_token	*token8;
// 	char	*input = " < miaou wc -l > output.txt | ls -la >>  <<";
// 	int		i1 = 1;
// 	int		i2 = 15;
// 	int		i3 = 28;
// 	int		i4 = 37;
// 	int		i5 = 41;

// 	tokens = NULL;
// 	token1 = init_token(TOKEN_PIPE, "|");
// 	if (!token1)
// 		printf("The what now????");
// 	add_token_back(&tokens, token1);
// 	token2 = init_token(TOKEN_WORD, "miaou");
// 	if (!token2)
// 		printf("The what now????");
// 	add_token_back(&tokens, token2);
// 	token3 = init_token(TOKEN_WORD, "wc");
// 	if (!token3)
// 		printf("The what now????");
// 	add_token_back(&tokens, token3);
// 	printf("%d", i1);
// 	create_redir_pipe_token(&token4, input, &i1);
// 	if (!token4)
// 		printf("The what now????");
// 	add_token_back(&tokens, token4);
// 	printf(" -> %d\n", i1);
// 	printf("%d", i2);
// 	create_redir_pipe_token(&token5, input, &i2);
// 	if (!token5)
// 		printf("The what now????");
// 	add_token_back(&tokens, token5);
// 	printf(" -> %d\n", i2);
// 	printf("%d", i3);
// 	create_redir_pipe_token(&token6, input, &i3);
// 	if (!token6)
// 		printf("The what now????");
// 	add_token_back(&tokens, token6);
// 	printf(" -> %d\n", i3);
// 	printf("%d", i4);
// 	create_redir_pipe_token(&token7, input, &i4);
// 	if (!token7)
// 		printf("The what now????");
// 	add_token_back(&tokens, token7);
// 	printf(" -> %d\n", i4);
// 	printf("%d", i5);
// 	create_redir_pipe_token(&token8, input, &i5);
// 	if (!token8)
// 		printf("The what now????");
// 	add_token_back(&tokens, token8);
// 	printf(" -> %d\n", i5);
// 	print_token_list(tokens);
// 	free_token_list(tokens);
// 	return (0);
// }
