/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfabian <cfabian@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 15:09:09 by cfabian           #+#    #+#             */
/*   Updated: 2022/05/18 15:35:47 by cfabian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	free_all(pthread_t *tid, t_data data, t_philo *philos)
{
	free(tid);
	free(philos);
	free(data.fork_state);
	free(data.f_mutex);
}
