/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_buffer_test.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 14:25:58 by abaryshe          #+#    #+#             */
/*   Updated: 2025/07/19 16:55:47 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_project/includes/minishell.h"

// int main(void)
// {
// 	t_str_buffer	*buf;

// 	buf = init_str_buffer(4);
// 	if (!buf)
// 		printf("crit\n");
// 	print_str_buffer(buf);
// 	// append_str_buffer(buf, "ab");

// 	// append_str_buffer(buf, "012345678901234567890123456789012345
// 6789012345678901234567890123456789012345678901234567890123456789");

// 	append_str_buffer(buf, "abcd");
// 	print_str_buffer(buf);
// 	append_str_buffer(buf, "0123");
// 	print_str_buffer(buf);
// 	append_str_buffer(buf, "abcd0123");
// 	print_str_buffer(buf);
// 	append_str_buffer(buf, "abcd0123abcd0123");
// 	print_str_buffer(buf);
// 	append_str_buffer(buf, "abcd0123abcd0123abcd0123abcd0123");

// 	// append_char_buffer(buf, '0');
// 	// append_char_buffer(buf, '1');
// 	// append_char_buffer(buf, '2');
// 	// print_str_buffer(buf);
// 	// append_char_buffer(buf, '3');
// 	// print_str_buffer(buf);
// 	// append_str_buffer(buf, "Hello ");
// 	// append_str_buffer(buf, "H");
// 	// append_char_buffer(buf, 'e');
// 	// append_char_buffer(buf, 'l');
// 	// append_char_buffer(buf, 'l');
// 	// append_char_buffer(buf, 'o');
// 	// append_char_buffer(buf, ' ');
// 	// append_char_buffer(buf, 'W');
// 	// append_char_buffer(buf, 'o');
// 	// append_char_buffer(buf, 'r');
// 	// append_char_buffer(buf, 'l');
// 	// append_char_buffer(buf, 'd');
// 	// append_char_buffer(buf, '!');
// 	// append_char_buffer(buf, '\n');
// 	// append_str_buffer(buf, "HELLO WORLD!!!");
// 	// append_char_buffer(buf, '!');
// 	// append_char_buffer(buf, '!');
// 	// append_char_buffer(buf, '!');
// 	// append_char_buffer(buf, '!');
// 	// append_char_buffer(buf, '!');
// 	// append_str_buffer(buf, "|WHAT|");
// 	print_str_buffer(buf);
// 	free_str_buffer(buf);
// 	return (0);
// }
