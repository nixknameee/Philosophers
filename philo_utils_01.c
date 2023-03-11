/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_01.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngjokaj <ngjokaj@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 08:24:20 by ngjokaj           #+#    #+#             */
/*   Updated: 2023/03/11 11:54:23 by ngjokaj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_philo_status(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->m_dead);
	if (philo->data->is_dead != 0 || philo->meals == philo->data->meals_to_eat)
	{
		philo->done = 1;
		pthread_mutex_unlock(&philo->data->m_dead);
		return (0);
	}
	if (ft_gettime() - philo->time_last_meal >= philo->data->time_to_die
		&& philo->data->is_dead == 0)
	{
		pthread_mutex_unlock(&philo->data->m_dead);
		philo_status(philo, "died");
		pthread_mutex_lock(&philo->data->m_dead);
		philo->data->is_dead = 1;
		philo->done = 1;
		pthread_mutex_unlock(&philo->data->m_dead);
		return (0);
	}
	pthread_mutex_unlock(&philo->data->m_dead);
	return (1);
}

/*Schleife, die den Philosophen weiter essen lässt, solange er nicht genug
gegessen hat oder tot ist. Wenn der Philosoph nicht tot ist, wird geprüft,
ob er essen kann. Andernfalls wird die Funktion beendet.*/

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo->meals != philo->data->meals_to_eat && !philo->done)
	{
		pthread_mutex_lock(&philo->data->m_dead);
		if (!philo->data->is_dead)
		{
			pthread_mutex_unlock(&philo->data->m_dead);
			if (!philosopher_dine(philo))
				return (NULL);
		}
		else
		{
			pthread_mutex_unlock(&philo->data->m_dead);
			return (NULL);
		}
	}
	return (NULL);
}

void	one_philo(t_data *data, char *time_to_die)
{
	pthread_t	thread1;

	if (pthread_create(&thread1, NULL, *ft_null, (void *) 1))
	{
		printf("Error system!");
		return ;
	}
	printf("0 1 has taken a fork\n");
	usleep(data->time_to_die * 1000);
	printf("%s 1 died\n", time_to_die);
	pthread_join(thread1, NULL);
}
