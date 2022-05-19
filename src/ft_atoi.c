/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfabian <cfabian@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 10:49:06 by cfabian           #+#    #+#             */
/*   Updated: 2022/05/18 20:44:17 by cfabian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* pointed to by nptr to int.  The behavior is the same as */
/* strtol(nptr, NULL, 10); except that atoi() does not detect errors. */
/* RETURN VALUE         top */
/* The converted value or 0 on error. */

#include "../philo.h"
/* #include <stdio.h> */

static int	ft_isspace(int c)
{
	if (c == ' ' || c == '\f' || c == '\n'
		|| c == '\r' || c == '\t' || c == '\v')
		return (1);
	return (0);
}

static bool	num_out_of_range(int s, unsigned long int num, char c)
{
	if (s == -1 && num == INT_MAX / 10 && (c - '1') > INT_MAX % 10)
		return (true);
	if (s == 1 && num == INT_MAX / 10 && (c - '0') > INT_MAX % 10)
		return (true);
	if (num > INT_MAX / 10)
		return (true);
	return (false);
}

int	ft_atoi(const char *str)
{
	unsigned int		i;
	unsigned long int	num;
	int					s;

	i = 0;
	num = 0;
	s = 1;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-')
		s = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (num_out_of_range(s, num, str[i]))
		{
			printf("%s%s: Input number to big, defaults to 0%s\n", \
			RED, str, DEF);
			return (0);
		}
		num = num * 10 + (str[i] - '0');
		i++;
	}
	return (s * num);
}

/*
int main ()
{
	printf("+012345: %d\n", ft_atoi("+012345"));
	printf("-1569: %d\n", ft_atoi("-1569"));
	printf("-+156: %d\n", ft_atoi("-+156"));
	printf("12345n: %d\n", ft_atoi("12345n"));
	printf("int_max is %d; int_min is %d \n", INT_MAX, INT_MIN);
	printf("+02147483647: %d \n", ft_atoi("+02147483647"));
	printf("+2147483648: %d \n", ft_atoi("+2147483648"));
	printf("+2147483657: %d \n", ft_atoi("+2147483657"));
	printf("+21474836470: %d \n", ft_atoi("+21474836470"));
	printf("-2147483648: %d \n", ft_atoi("-2147483648"));
	printf("-2147483649: %d \n", ft_atoi("-2147483649"));
}
*/