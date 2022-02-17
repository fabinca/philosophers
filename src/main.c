/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfabian <cfabian@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 15:52:46 by cfabian           #+#    #+#             */
/*   Updated: 2022/02/17 16:25:26 by cfabian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*philo_thread(void *ptr)
{
	return (NULL);
}

t_data	*init_data(int argc, char **argv)
{
	t_data	*data;

	if (argc < 5 || argc > 6)
	{
		printf("Usage: ./philo number_of_philosophers time_to_die time_to_eat \
		time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
		return (0);
	}
	data = (t_data *)malloc(sizeof(t_data) * 1);
	if (!data)
		return (0);
	data->nb_of_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 5)
		data->nb_meals = NULL;
	else
		data->nb_meals = ft_atoi(argv[5]);
	return (data);
}

int	main(int argc, char **argv)
{
	int			i;
	int			ptr[3];
	t_data		*data;
	pthread_t	*tid;

	i = -1;
	data = init_data(argc, argv);
	tid = (pthread_t *)malloc(sizeof(pthread_t) * data->nb_of_philos);
	while (++i < data->nb_of_philos)
	{
		pthread_create(&(tid[i]), NULL, &philo_thread, (void *)ptr);
	}
	pthread_join(tid[0], NULL);
	pthread_join(tid[1], NULL);
	pthread_join(tid[2], NULL);
	return (0);
}
