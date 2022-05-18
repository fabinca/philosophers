/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfabian <cfabian@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 16:33:30 by cfabian           #+#    #+#             */
/*   Updated: 2022/05/18 16:40:31 by cfabian          ###   ########.fr       */
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
		if (term(philo))
			return ;
		philo->hand_fork[0] = 1;
		printf("%li philosopher %i has taken left fork.\n", ft_gettimestamp(), philo->number + 1);
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
		if (term(philo))
			return ;
		philo->hand_fork[1] = 1;
		printf("%li philosopher %i has taken right fork.\n", ft_gettimestamp(), philo->number + 1);
	}
	else
		pthread_mutex_unlock(&philo->data_ptr->f_mutex[philo->number]);
}

void	think(t_philo *philo, int64_t time)
{
	if (term(philo))
		return ;
	printf("%li philosopher %i is thinking.\n", ft_gettimestamp(), philo->number + 1);
	usleep(time);
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

void	eat(t_philo *philo)
{
	int64_t	now;

	now = ft_gettimestamp();
	printf("%li philosopher %i is eating. (%i)\n", \
	now, philo->number + 1, philo->nb_meals);
	philo->nb_meals += 1;
	if (philo->nb_meals == philo->data_ptr->nb_meals)
	{
		//pthread_mutex_lock(&philo->data_ptr->incr_philos_finished);
		philo->data_ptr->philos_finished_nbm += 1;
		//pthread_mutex_unlock(&philo->data_ptr->incr_philos_finished);
		if (philo->data_ptr->philos_finished_nbm == philo->data_ptr->nb_p)
		{
			//pthread_mutex_lock(&philo->data_ptr->check_term);
			philo->data_ptr->term += 1;
			//pthread_mutex_unlock(&philo->data_ptr->check_term);
		}
	}
	usleep(philo->data_ptr->time_to_sleep * 1000 -(ft_gettimestamp() - now));
	philo->last_food = now;
	put_down_left_fork(philo);
	put_down_right_fork(philo);
	

}

void	philo_sleep(t_philo *philo)
{
	int64_t	now;

	if (term(philo))
		return ;
	now = ft_gettimestamp();
	printf("%li philosopher %i is sleeping.\n", now, philo->number + 1);
	if (now - philo->last_food + philo->data_ptr->time_to_sleep * 1000 < \
		philo->data_ptr->time_to_die * 1000)
		usleep(philo->data_ptr->time_to_sleep * 1000);
	else
		usleep((philo->data_ptr->time_to_die * 1000 - \
		(now - philo->last_food)));
}

bool	term(t_philo *philo)
{
	int64_t	now;

	//pthread_mutex_lock(&philo->data_ptr->check_term);
	if (philo->data_ptr->term > 0)
	{
		//pthread_mutex_unlock(&philo->data_ptr->check_term);
		return (1);
	}
	now = ft_gettimestamp();
	if (now - philo->last_food < philo->data_ptr->time_to_die)
	{
		//pthread_mutex_unlock(&philo->data_ptr->check_term);
		return (0);
	}
	philo->data_ptr->term += 1;
	//pthread_mutex_unlock(&philo->data_ptr->check_term);
	printf("%li philosopher %i died.\n", now, philo->number + 1);
	return (1);
}
