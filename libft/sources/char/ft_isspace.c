/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 21:56:34 by abaryshe          #+#    #+#             */
/*   Updated: 2025/06/04 23:30:31 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isspace(int c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (c);
	return (0);
}

// int main(void)
// {
// 	// Test ft_isspace function
// 	char test_chars[] = {' ', '\f', '\n', '\r', '\t', '\v', 'h', '6', '\a', 0};
// 	for (int i = 0; test_chars[i] != 0; i++)
// 	{
// 		if (ft_isspace(test_chars[i]))
// 			printf("'%c' is a whitespace character.\nReturn value: [%d]\n",
//				test_chars[i], ft_isspace(test_chars[i]));
// 		else
// 			printf("'%c' is NOT a whitespace character.\nReturn value: [%d]\n",
//				test_chars[i], ft_isspace(test_chars[i]));
// 		printf("------------------\n");
// 	}
// 	return (0);
// }
