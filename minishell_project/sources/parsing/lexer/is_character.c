/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_character.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:19:09 by abaryshe          #+#    #+#             */
/*   Updated: 2025/07/19 16:36:28 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Checks if the character is a metacharacter ('<', '>', '|' or '$').
 * If expanded is true is_metacharacter checks for a dollar sign ('$').
 * Otherwise, it checks for redirections and a pipe ('<', '>', '|').
 */
int	is_metacharacter(int c, int expanded)
{
	char	ch;

	ch = (char)c;
	if (expanded)
	{
		if (ch == '$')
			return (ch);
	}
	else
	{
		if (ch == '<' || ch == '>' || ch == '|')
			return (ch);
	}
	return (0);
}

// int main(void)
// {
// 	int ch;
// 	int f_ch;
// 	int ch1;
// 	int f_ch1;
// 	int f_ch2;

// 	ch = '>';
// 	f_ch = 'g';
// 	ch1 = '$';
// 	f_ch1 = 'a';
// 	f_ch2 = '<';
// 	printf("ch: %d, f_ch:
// 	%d\n", is_metacharacter(ch, 0), is_metacharacter(f_ch, 0));
// 	printf("ch1: %d, f_ch1: %d, f_ch2: %d\n", is_metacharacter(ch1, 1),
// 	is_metacharacter(f_ch1, 1), is_metacharacter(f_ch2, 1));
// 	return (0);
// }
