/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 18:49:02 by sguan             #+#    #+#             */
/*   Updated: 2025/07/19 16:33:13 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	skip_space(const char *str, int i)
{
	while (str[i] == ' ')
		i++;
	return (i);
}

int	parse_sign(const char *str, int *i)
{
	int	sign;

	sign = 1;
	if (str[*i] == '+' || str[*i] == '-')
	{
		if (str[*i] == '-')
			sign = -1;
		(*i)++;
	}
	return (sign);
}

int	accumulate_value(const char *str, int *i, long *out, int sign)
{
	int	digit;

	*out = 0;
	if (!str || !out)
		return (0);
	while (str[*i] && ft_isdigit(str[*i]))
	{
		digit = (str[*i] - '0');
		if (sign == 1 && *out > (LONG_MAX - digit) / 10)
		{
			*out = LONG_MAX;
			return (0);
		}
		if (sign == -1 && *out > -((LONG_MIN + digit) / 10))
		{
			*out = LONG_MIN;
			return (0);
		}
		*out = (*out * 10) + digit;
		(*i)++;
	}
	return (1);
}

int	ft_strtol(const char *str, long *out)
{
	int	i;
	int	sign;
	int	res;

	i = 0;
	sign = 1;
	if (!str)
		return (0);
	i = skip_space(str, i);
	sign = parse_sign(str, &i);
	if (!ft_isdigit(str[i]))
		return (0);
	res = accumulate_value(str, &i, out, sign);
	if (res == 0)
		return (0);
	i = skip_space(str, i);
	if (str[i])
		return (0);
	*out = *out * sign;
	return (1);
}
/*
#include <limits.h>
#include <stdio.h>

void	run_test(const char *str) {
	long out_my = 0;
	long out_std = 0;
	char *end_std;

	int ret_my = ft_strtol(str, &out_my);
	out_std = strtol(str, &end_std, 10);

	printf("input: \"%s\"\n", str);
	printf("  ft_strtol  : ret=%d, value=%ld\n", ret_my, out_my);
	printf("  std strtol : value=%ld, end=\"%s\"\n", out_std, end_std);
	printf("--------------------------\n");
}

int	main(void) {

	run_test("0");
	run_test("123");
	run_test("-456");
	run_test("   789   ");
	run_test("+42");

	char long_max[32], long_min[32];
	snprintf(long_max, sizeof(long_max), "%ld", LONG_MAX);
	snprintf(long_min, sizeof(long_min), "%ld", LONG_MIN);
	run_test(long_max);//
	run_test(long_min);//
	run_test("9223372036854775808"); //
	run_test("-9223372036854775809"); //

	run_test("");
	run_test("  ");
	run_test("abc");
	run_test("12abc34");
	run_test("++123");
	run_test("--123");
	run_test("+-123");
	run_test("-+123");

	run_test("   +00123   ");
	run_test("   -00123   ");//

	run_test("+");
	run_test("-");

	run_test("123 456");
	run_test(" 123x ");
	run_test("0x123");

	run_test("99999999999999999999");
	run_test("-99999999999999999999");
	return (0);
}
*/
