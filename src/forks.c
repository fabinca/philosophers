/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfabian <cfabian@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 18:16:03 by cfabian           #+#    #+#             */
/*   Updated: 2022/05/22 00:47:21 by cfabian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

bool	take_left_fork(t_philo *philo)
{
	if (philo->hand_fork[0] == 1)
		return (1);
	pthread_mutex_lock(&philo->data_ptr->f_mutex[philo->left]);
	if (philo->data_ptr->fork_state[philo->left] == 1)
	{
		philo->data_ptr->fork_state[philo->left] = 0;
		pthread_mutex_unlock(&philo->data_ptr->f_mutex[philo->left]);
		philo->hand_fork[0] = 1;
		if (safe_print(philo, "has taken left fork") >= 0)
			return (1);
		return (0);
	}
	pthread_mutex_unlock(&philo->data_ptr->f_mutex[philo->left]);
	return (0);
}

bool	take_right_fork(t_philo *philo)
{
	if (philo->hand_fork[1] == 1)
		return (1);
	pthread_mutex_lock(&philo->data_ptr->f_mutex[philo->number]);
	if (philo->data_ptr->fork_state[philo->number] == 1)
	{
		philo->data_ptr->fork_state[philo->number] = 0;
		pthread_mutex_unlock(&philo->data_ptr->f_mutex[philo->number]);
		philo->hand_fork[1] = 1;
		if (safe_print(philo, "has taken right fork") > 1)
			return (1);
		return (0);
	}
	pthread_mutex_unlock(&philo->data_ptr->f_mutex[philo->number]);
	return (0);
}

void	put_down_fork(t_philo *philo, bool side)
{
	int	fork;

	if (side == 0)
		fork = philo->left;
	else
		fork = philo->number;
	pthread_mutex_lock(&philo->data_ptr->f_mutex[fork]);
	philo->data_ptr->fork_state[fork] = 1;
	pthread_mutex_unlock(&philo->data_ptr->f_mutex[fork]);
	philo->hand_fork[side] = 0;
}

bool	check_fork(t_philo *philo, int fork)
{
	bool	fork_state;

	if (fork < 0)
		fork = philo->data_ptr->nb_p - 1;
	if (fork >= philo->data_ptr->nb_p)
		fork = 0;
	pthread_mutex_lock(&philo->data_ptr->f_mutex[fork]);
	fork_state = philo->data_ptr->fork_state[fork];
	pthread_mutex_unlock(&philo->data_ptr->f_mutex[fork]);
	return (fork_state);
}
