/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfabian <cfabian@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 15:10:27 by cfabian           #+#    #+#             */
/*   Updated: 2022/04/28 15:23:57 by cfabian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//philothread: 
//think(philonumber)
//last time eat
//check time to die
//while (now - last_food < time_to_die && end == 0)
	//mutex_lock
// if fork_left & fork right == 1
	//fork_left & fork_right = 0
	//philo_can_eat = 1
	//mutex unlock
	if philo_can_eat
		// philo eats
		// fork left & fork right = 0
		if (now - last_food < time_to_die)
		// philo sleeps 
		//philo thinks