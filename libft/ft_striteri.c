/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:22:07 by abaryshe          #+#    #+#             */
/*   Updated: 2024/11/19 21:18:59 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	index;

	index = 0;
	while (s[index] != 0)
	{
		f(index, s + index);
		index++;
	}
}
/*
void	ft_toup(unsigned int index, char *s)
{
	if (*s > 96 && *s < 123)
		s[index - index] -= 32;
}

#include <stdio.h>

int	main(void)
{
	char	str[] = "I like you!";

	ft_striteri(str, &ft_toup);
	printf("%s\n", str);
	return (0);
}
*/
