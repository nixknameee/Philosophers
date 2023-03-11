/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_00.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngjokaj <ngjokaj@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 14:30:47 by ngjokaj           #+#    #+#             */
/*   Updated: 2023/03/11 11:54:55 by ngjokaj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*Die Funktion philo_status gibt den aktuellen Zustand des Philosophen philo 
aus, wenn er nicht fertig ist,der Philosoph nicht tot ist und er nicht 
genug gegessen hat.*/

void	philo_status(t_philo *philo, char *state)
{
	pthread_mutex_lock(&philo->data->m_dead);
	pthread_mutex_lock(&philo->data->m_write);
	if (!philo->done && !philo->data->is_dead
		&& philo->meals != philo->data->meals_to_eat)
	{	
		printf("%lld %d %s\n", (ft_gettime() - philo->data->start_time),
			philo->philo_id, state);
	}
	pthread_mutex_unlock(&philo->data->m_write);
	pthread_mutex_unlock(&philo->data->m_dead);
}

/*Funktion, die eine Verzögerung in Mikrosekunden verwendet, um eine bestimmte
Zeit zu warten. Wenn das Programm während des Wartens beendet wird oder der 
Philosoph gestorben ist, wird 0 zurückgegeben, andernfalls 1.*/

int	ft_usleep(unsigned int time_to_delay, t_philo *philo)
{
	long long	now;

	now = ft_gettime();
	if (!check_philo_status(philo))
		return (0);
	while ((ft_gettime() - now) < ((long long)time_to_delay))
	{
		if (!check_philo_status(philo))
			return (0);
		usleep(100);
	}
	return (1);
}

/*Funktion, die die aktuelle Systemzeit in Millisekunden seit dem 
1. Januar 1970 (Epoch) zurückgibt.*/

long long	ft_gettime(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

/*Freigabe und Zerstörung aller Mutex-Objekte sowie Freigabe des 
Speichers für Gabeln und Philosophen-Threads.*/

void	finish_process(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_philos)
	{
		pthread_mutex_destroy(&data->m_forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->m_write);
	pthread_mutex_destroy(&data->m_dead);
	free(data->m_forks);
	free(data->philo);
	free(data->forks);
}

void	*ft_null(void *c)
{
	int	*i;

	i = (int *) c;
	i++;
	return (NULL);
}
