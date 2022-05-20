/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfabian <cfabian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 12:27:39 by cfabian           #+#    #+#             */
/*   Updated: 2022/05/20 13:48:56 by cfabian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int64_t	ft_gettimestamp(int64_t start)
{
	struct timeval	tv;
	int64_t			now;

	gettimeofday(&tv, NULL);
	now = tv.tv_sec * 1000 + tv.tv_usec / 1000 - start;
	return (now);
}
