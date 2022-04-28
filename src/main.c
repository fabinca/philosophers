/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfabian <cfabian@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 15:52:46 by cfabian           #+#    #+#             */
/*   Updated: 2022/02/27 17:29:22 by cfabian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*philo_thread(void *data_v)
{
	t_data	*data;
	t_philo	philo;

	data = (t_data *)data_v;
	philo = data->philos[data->number];
	philo.last_food = get_timestamp();
	while (data->dead == 0)
	{
		printf("%d \n", philo.status);
		if (philo.left && philo.right)
		{
			printf("test8\n");
			philo.status = 1;
			printf("test9\n");
			pthread_mutex_lock(philo.fork);
			printf("test10\n");
			if (data->dead == 1)
				break ;
			printf("test11\n");
			printf("%ld: %d took a fork.\n", get_timestamp(), philo.number + 1);
			pthread_mutex_lock(philo.left->fork);
			if (data->dead == 1)
				break ;
			printf("%ld: %d took a fork.\n", get_timestamp(), philo.number + 1);
			if (data->dead == 1)
				break ;
			philo.last_food = get_timestamp();
			printf("%ld: %d is eating.\n", philo.last_food, philo.number + 1);
			usleep(data->time_to_eat * 1000);
			philo.status = 2;
			pthread_mutex_unlock(philo.fork);
			pthread_mutex_unlock(philo.left->fork);
			if (data->dead == 1)
				break ;
			printf("%ld: %d is sleeping.\n", get_timestamp(), philo.number + 1);
			usleep(data->time_to_sleep * 1000);
			if (data->dead == 1)
				break ;
			printf("%ld: %d is thinking.\n", get_timestamp(), philo.number + 1);
		}
		if (get_timestamp() - philo.last_food > data->time_to_die)
		{
			data->dead = 1;
			philo.status = 0;
		}
	}
	if (philo.status == 0)
		printf("%d has died.\n", philo.number + 1);
	return (NULL);
}

t_philo	*init_philos(int nb, pthread_mutex_t *forks)
{
	t_philo	*philos;
	int16_t	i;

	i = 0;
	philos = (t_philo *)malloc(sizeof(t_philo) * nb);
	while (i++ < nb)
	{
		philos[i].number = i;
		philos[i].status = 2;
		philos[i].nb_meals = 0;
		philos[i].fork = &(forks[i]);
		if (i != 0)
			philos[i].left = &philos[i - 1];
		else
			philos[i].left = &philos[nb - 1];
		if (i != nb - 1)
			philos[i].right = &philos[i + 1];
		else
			philos[i].right = &philos[0];
		pthread_mutex_init(philos[i].fork, NULL);
	}
	return (philos);
}

t_data	init_data(int argc, char **argv)
{
	t_data	data;

	data.nb_of_philos = ft_atoi(argv[1]);
	data.forks = malloc(data.nb_of_philos * sizeof(pthread_mutex_t));
	data.time_to_die = ft_atoi(argv[2]);
	data.time_to_eat = ft_atoi(argv[3]);
	data.time_to_sleep = ft_atoi(argv[4]);
	data.dead = 0;
	if (argc == 5)
		data.nb_meals = -10;
	else
		data.nb_meals = ft_atoi(argv[5]);
	data.philos = init_philos(data.nb_of_philos, data.forks);
	return (data);
}

int	main(int argc, char **argv)
{
	int16_t		i;
	t_data		data;
	pthread_t	*tid;

	if (argc < 5 || argc > 6)
	{
		printf("Usage: ./philo number_of_philosophers time_to_die time_to_eat \
		time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
		return (0);
	}
	i = -1;
	data = init_data(argc, argv);
	tid = (pthread_t *)malloc(sizeof(pthread_t) * data.nb_of_philos);
	while (++i < data.nb_of_philos)
	{
		data.number = i;
		pthread_create(&(tid[i]), NULL, &philo_thread, &data);
		usleep(1);
	}
	i = -1;
	while (++i < data.nb_of_philos)
		pthread_join(tid[i], NULL);
	i = -1;
	free_all(tid, data);
	return (0);
}
