/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfabian <cfabian@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 18:16:03 by cfabian           #+#    #+#             */
/*   Updated: 2022/05/18 21:01:50 by cfabian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	take_left_fork(t_philo *philo)
{
	if (philo->hand_fork[0] == 1 || term(philo))
		return ;
	pthread_mutex_lock(&philo->data_ptr->f_mutex[philo->left]);
	if (philo->data_ptr->fork_state[philo->left] == 1)
	{
		philo->data_ptr->fork_state[philo->left] = 0;
		pthread_mutex_unlock(&philo->data_ptr->f_mutex[philo->left]);
		philo->hand_fork[0] = 1;
		if (term(philo))
			return ;
		print_message(philo->number, "has taken left fork");
	}
	else
		pthread_mutex_unlock(&philo->data_ptr->f_mutex[philo->left]);
}

void	take_right_fork(t_philo *philo)
{
	if (philo->hand_fork[1] == 1 || term(philo))
		return ;
	pthread_mutex_lock(&philo->data_ptr->f_mutex[philo->number]);
	if (philo->data_ptr->fork_state[philo->number] == 1)
	{
		philo->data_ptr->fork_state[philo->number] = 0;
		pthread_mutex_unlock(&philo->data_ptr->f_mutex[philo->number]);
		philo->hand_fork[1] = 1;
		if (term(philo))
			return ;
		print_message(philo->number, "has taken right fork");
	}
	else
		pthread_mutex_unlock(&philo->data_ptr->f_mutex[philo->number]);
}

void	put_down_right_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->data_ptr->f_mutex[philo->number]);
	philo->data_ptr->fork_state[philo->number] = 1;
	pthread_mutex_unlock(&philo->data_ptr->f_mutex[philo->number]);
	philo->hand_fork[1] = 0;
}

void	put_down_left_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->data_ptr->f_mutex[philo->left]);
	philo->data_ptr->fork_state[philo->left] = 1;
	pthread_mutex_unlock(&philo->data_ptr->f_mutex[philo->left]);
	philo->hand_fork[0] = 0;
}

void	put_down_needed_forks(t_philo *philo)
{
	int	neighbour;

	neighbour = philo->number + 1;
	if (neighbour >= philo->data_ptr->nb_p)
		neighbour = 0;
	if (philo->hand_fork[1] == 1 && philo->data_ptr->fork_state[neighbour] == 1)
	{
		put_down_right_fork(philo);
		print_message(philo->number, "has put down right fork");
		usleep(500);
		return ;
	}
	neighbour = philo->number - 1;
	if (neighbour < 0)
		neighbour = philo->data_ptr->nb_p - 1;
	if (philo->hand_fork[0] == 1 && philo->data_ptr->fork_state[neighbour] == 1)
	{
		put_down_left_fork(philo);
		print_message(philo->number, "has put down left fork");
		usleep(1000);
	}
}
