/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfabian <cfabian@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 10:49:06 by cfabian           #+#    #+#             */
/*   Updated: 2022/05/22 00:48:54 by cfabian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* pointed to by nptr to int.  The behavior is the same as */
/* strtol(nptr, NULL, 10); except that atoi() does not detect errors. */
/* RETURN VALUE         top */
/* The converted value or 0 on error. */

#include "../philo.h"
/* #include <stdio.h> */

static bool	num_out_of_range(int num, char c)
{
	if (num == INT_MAX / 10 && (c - '0') > INT_MAX % 10)
		return (true);
	if (num > INT_MAX / 10)
		return (true);
	return (false);
}

int	ft_atoi_philo(const char *str, bool *err, int limit, bool type)
{
	int	i;
	int	num;

	i = 0;
	num = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (num_out_of_range(num, str[i]))
		{
			printf("%s%s: Input number out of range %s\n", RED, str, DEF);
			*err = 1;
			return (0);
		}
		num = num * 10 + (str[i] - '0');
		i++;
	}
	if ((type == MAX_VAL && num > limit) || \
	(type == MIN_VAL && num < limit))
	{
		printf("%s%s: Input number invalid %s\n", RED, str, DEF);
		*err = 1;
	}
	return (num);
}
