/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 14:50:38 by abaryshe          #+#    #+#             */
/*   Updated: 2024/11/20 16:01:59 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}
/*
#include <stdio.h>

int	main(void)
{
	// int		*a;
	// int		b;
	char	*str;
	// t_list	*first;
	t_list	*second;

	// b = 42;
	// a = &b;
	str = "Norminette is not my type";
	// first = ft_lstnew(&a);
	second = ft_lstnew(str);
	// printf("%d\n", (int *)first->content);
	printf("%s\n", (char *)second->content);
	// free(first);
	free(second);
	return (0);
}*/
