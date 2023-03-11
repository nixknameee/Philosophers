/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eating.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngjokaj <ngjokaj@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 14:30:07 by ngjokaj           #+#    #+#             */
/*   Updated: 2023/03/11 11:10:53 by ngjokaj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*Die Funktion "ft_sleep" prüft, ob "philo" am Leben ist, lässt ihn schlafen, 
loggt eine Nachricht und lässt ihn denken.*/

static int	ft_sleep(t_philo *philo)
{
	if (!check_philo_status(philo))
		return (0);
	philo_status(philo, "is sleeping");
	if (!ft_usleep(philo->data->time_to_sleep, philo))
		return (0);
	if (!check_philo_status(philo))
		return (0);
	philo_status(philo, "is thinking");
	ft_usleep(1, philo);
	return (1);
}

/*Die Funktion "eat_and_count" reserviert die Gabeln, lässt "philo" essen, zählt
die Mahlzeiten und gibt eine Rückgabe von 1 zurück.*/

int	eat_and_count(t_philo *philo, int lock_order)
{
	philo->data->forks[philo->right_fork] = philo->philo_id;
	philo->data->forks[philo->left_fork] = philo->philo_id;
	if (lock_order == 0)
	{
		pthread_mutex_unlock(&philo->data->m_forks[philo->left_fork]);
		pthread_mutex_unlock(&philo->data->m_forks[philo->right_fork]);
	}
	else if (lock_order == 1)
	{
		pthread_mutex_unlock(&philo->data->m_forks[philo->right_fork]);
		pthread_mutex_unlock(&philo->data->m_forks[philo->left_fork]);
	}
	if (!check_philo_status(philo))
		return (0);
	philo_status(philo, "has taken a fork");
	philo_status(philo, "has taken a fork");
	philo_status(philo, "is eating");
	philo->time_last_meal = ft_gettime();
	if (!ft_usleep(philo->data->time_to_eat, philo))
		return (0);
	philo->meals++;
	return (1);
}

/*Die Funktion "drop_forks" gibt die reservierten Gabeln von "philo" 
frei, indem sie die Mutexe entsperrt und die Gabeln zurücksetzt.*/
static void	drop_forks(t_philo *philo, int lock_order)
{
	if (lock_order == 0)
	{
		pthread_mutex_lock(&philo->data->m_forks[philo->left_fork]);
		philo->data->forks[philo->left_fork] = 0;
		pthread_mutex_unlock(&philo->data->m_forks[philo->left_fork]);
		pthread_mutex_lock(&philo->data->m_forks[philo->right_fork]);
		philo->data->forks[philo->right_fork] = 0;
		pthread_mutex_unlock(&philo->data->m_forks[philo->right_fork]);
	}
	else if (lock_order == 1)
	{
		pthread_mutex_lock(&philo->data->m_forks[philo->right_fork]);
		philo->data->forks[philo->right_fork] = 0;
		pthread_mutex_unlock(&philo->data->m_forks[philo->right_fork]);
		pthread_mutex_lock(&philo->data->m_forks[philo->left_fork]);
		philo->data->forks[philo->left_fork] = 0;
		pthread_mutex_unlock(&philo->data->m_forks[philo->left_fork]);
	}
}

/*Die Funktion sperrt oder entsperrt die Mutexe der Gabeln basierend auf 
den übergebenen Parametern. Wenn "flag" gleich 1 ist und "lock_order" gleich 0, 
werden die Mutexe in der Reihenfolge "right_fork" -> "left_fork" gesperrt,
sonst in der Reihenfolge "left_fork" -> "right_fork". 
Andernfalls werden die Mutexe entsperrt.*/

static void	manage_forks(t_philo *philo, int flag, int lock_order)
{
	if (flag == 1 && lock_order == 0)
	{
		pthread_mutex_lock(&philo->data->m_forks[philo->right_fork]);
		pthread_mutex_lock(&philo->data->m_forks[philo->left_fork]);
	}	
	else if (flag == 1 && lock_order == 1)
	{
		pthread_mutex_lock(&philo->data->m_forks[philo->left_fork]);
		pthread_mutex_lock(&philo->data->m_forks[philo->right_fork]);
	}
	else
	{
		if (lock_order == 0)
		{
			pthread_mutex_unlock(&philo->data->m_forks[philo->left_fork]);
			pthread_mutex_unlock(&philo->data->m_forks[philo->right_fork]);
		}
		else
		{
			pthread_mutex_unlock(&philo->data->m_forks[philo->right_fork]);
			pthread_mutex_unlock(&philo->data->m_forks[philo->left_fork]);
		}
	}
}

/*Die Funktion philosopher_dine überprüft, ob der Philosoph am Leben ist 
und sperrt die Gabeln. Wenn beide Gabeln frei sind, isst der Philosoph
und gibt dann die Gabeln frei und schläft. Wenn nicht, gibt er die Gabeln 
frei und ruft check_philo_status auf, um zu überprüfen, ob er nochlebt. 
Die Funktion gibt immer 1 zurück.*/

int	philosopher_dine(t_philo *philo)
{
	if (!check_philo_status(philo))
		return (0);
	manage_forks(philo, 1, philo->philo_id % 2);
	if (philo->data->forks[philo->right_fork] == 0
		&& philo->data->forks[philo->left_fork] == 0)
	{
		if (!eat_and_count(philo, philo->philo_id % 2))
			return (0);
		drop_forks(philo, philo->philo_id % 2);
		if (!ft_sleep(philo))
			return (0);
		return (1);
	}
	else
	{
		manage_forks(philo, 0, philo->philo_id % 2);
		if (!check_philo_status(philo))
			return (0);
	}
	return (1);
}
