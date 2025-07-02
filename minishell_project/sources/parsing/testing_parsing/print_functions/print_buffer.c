/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_str_buffer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 14:50:05 by abaryshe          #+#    #+#             */
/*   Updated: 2025/06/24 15:22:25 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_str_buffer(t_str_buffer *buf)
{
	printf("string: [%s] \nlenght: [%zu] \ncapacity: [%zu]\n", buf->str, buf->len, buf->capacity);
	printf("- - - - - - - -\n");
}
