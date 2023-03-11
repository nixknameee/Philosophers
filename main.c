/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngjokaj <ngjokaj@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 14:30:06 by ngjokaj           #+#    #+#             */
/*   Updated: 2023/03/11 09:09:16 by ngjokaj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*Füllt die übergebene Struktur t_data mit den Werten aus dem argv-Array.
Überprüft dabei, ob die übergebenen Argumente gültig sind. Gibt 1 zurück, 
wenn die Struktur erfolgreich befüllt wurde und 0 wenn es einen Fehler gab.*/

static int	initialize_data(char **argv, t_data *data)
{
	data->nbr_philos = ft_atol(argv[1]);
	data->time_to_die = ft_atol(argv[2]);
	data->time_to_eat = ft_atol(argv[3]);
	data->time_to_sleep = ft_atol(argv[4]);
	if (argv[5])
		data->meals_to_eat = ft_atol(argv[5]);
	else
		data->meals_to_eat = -1;
	data->start_time = ft_gettime();
	if (data->nbr_philos <= 0 || data->time_to_die <= 0
		|| data->time_to_eat <= 0 || data->time_to_sleep <= 0)
	{
		printf("Error: Invalid arguments\n");
		return (0);
	}
	return (1);
}

/*Funktion, die überprüft, ob alle Philosophen die vorgegebene Anzahl von
Mahlzeiten erreicht haben und in diesem Fall eine entsprechende 
Nachricht ausgibt.*/

static void	check_meals(t_data data)
{
	int	i;

	i = 0;
	if (data.meals_to_eat == -1)
		return ;
	while (i < data.nbr_philos)
	{
		if (data.philo[i].meals != data.meals_to_eat)
			return ;
		i++;
	}
	pthread_mutex_lock(&data.philo->data->m_write);
	printf("%lld all have eaten %d times\n", ft_gettime()
		- data.start_time, data.meals_to_eat);
	pthread_mutex_unlock(&data.philo->data->m_write);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc == 5 || argc == 6)
	{
		if (!initialize_data(argv, &data))
			return (1);
		if (data.nbr_philos == 1)
		{
			one_philo(&data, argv[2]);
			return (0);
		}
		if (!initialize_philosophers(&data))
			return (1);
		check_meals(data);
		finish_process(&data);
	}
	else
	{
		printf("Invalid usage. Please provide the following arguments:\n");
		printf("./philo <number_of_philosophers> <time_to_die> <time_to_eat> \
<time_to_sleep> [<number_of_times_each_philosopher_must_eat>]\n");
		printf("\nExample usage:\n");
		printf("./philo 5 800 200 100 7\n");
		return (1);
	}
	return (0);
}
