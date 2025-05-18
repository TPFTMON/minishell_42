/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 14:51:38 by abaryshe          #+#    #+#             */
/*   Updated: 2024/11/20 21:43:41 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	len;

	len = 0;
	while (lst)
	{
		lst = lst->next;
		len++;
	}
	return (len);
}
/*
#include <stdio.h>

int	main(void)
{
	t_list	*a;
	t_list	*b;
	t_list	*c;
	t_list	*d;
	t_list	**lst;
	int		i;

	a = 55;
	b = 33;
	c = 42;
	d = NULL;
	a->next = &b;
	b->next = &c;
	c->next = &d;
	lst[0] = a;
	lst[1] = b;
	lst[2] = c;
	lst[3] = d;
	while (lst[i] != NULL)
	{
		printf("%d\n", *lst[i]);
		i++;
	}
	printf("%d\n", ft_lstsize(lst));
	return (0);
}*/
