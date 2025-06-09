/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 14:39:14 by abaryshe          #+#    #+#             */
/*   Updated: 2025/01/09 10:29:24 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*mem_ptr;
	size_t	mem_size;

	mem_size = count * size;
	mem_ptr = (void *)malloc(mem_size);
	if (mem_ptr == NULL)
		return (NULL);
	else
		ft_bzero(mem_ptr, mem_size);
	return (mem_ptr);
}
/*
int	main(void)
{
	void	*ptr_1;
	void	*ptr_2;
	size_t	count = __SIZE_MAX__;
	size_t	size = __SIZE_MAX__;

	ptr_1 = ft_calloc(count, size);
	ptr_2 = calloc(count, size);
	free(ptr_1);
	free(ptr_2);
}*/