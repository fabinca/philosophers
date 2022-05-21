/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfabian <cfabian@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 22:35:48 by cfabian           #+#    #+#             */
/*   Updated: 2022/05/22 00:49:45 by cfabian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len] != 0)
		len++;
	return (len);
}

static void	ft_putchar(char c)
{
	write(1, &c, 1);
}

static void	ft_putnbr(int n)
{
	if (n >= 10)
	{
		ft_putnbr(n / 10);
		ft_putnbr(n % 10);
	}
	else
		ft_putchar(n + '0');
}

static void	ft_putendl(char *s)
{
	write(1, " ", 1);
	write(1, s, ft_strlen(s));
	write(1, "\n", 1);
}

int64_t	safe_print(t_philo *philo, char *message)
{
	int64_t	timestamp;

	if (term(philo))
		return (-1);
	pthread_mutex_lock(&philo->data_ptr->print);
	timestamp = ft_gettimestamp(philo->data_ptr->start);
	ft_putnbr(timestamp);
	write(1, " philosopher ", 14);
	ft_putnbr(philo->number + 1);
	ft_putendl(message);
	pthread_mutex_unlock(&philo->data_ptr->print);
	return (timestamp);
}
