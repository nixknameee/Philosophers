/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngjokaj <ngjokaj@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 14:30:07 by ngjokaj           #+#    #+#             */
/*   Updated: 2023/03/11 11:52:57 by ngjokaj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int				philo_id;
	pthread_t		thread_nbr;
	int				left_fork;
	int				right_fork;
	int				meals;
	int				done;
	long long		time_last_meal;
	struct s_data	*data;
}					t_philo;

typedef struct s_data
{
	t_philo			*philo;
	pthread_mutex_t	*m_forks;
	pthread_mutex_t	m_write;
	pthread_mutex_t	m_dead;
	int				nbr_philos;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	long long		start_time;
	int				meals_to_eat;
	int				*forks;
	int				is_dead;
}					t_data;

/*---------------------main.c---------------------*/

int				main(int argc, char **argv);
//static int		initialize_data(char **argv, t_data *data);
//static void		check_meals(t_data data);

/*---------------------eating.c---------------------*/

int				philosopher_dine(t_philo *philo);
//static void		manage_forks(t_philo *philo, int flag, int lock_order);
//static void		drop_forks(t_philo *philo, int lock_order);
int				eat_and_count(t_philo *philo, int lock_order);
//static int		ft_sleep(t_philo *philo);

/*---------------------libft.c---------------------*/

int				ft_atoi(const char *string);
int				ft_isdigit(int c);
int				ft_strncmp(char const *s1, char const *s2, size_t size);
int				ft_atol(const char *nptr);

/*---------------------philo_utiles_00.c---------------------*/

void			philo_status(t_philo *philo, char *state);
int				ft_usleep(unsigned int time_to_delay, t_philo *philo);
long long		ft_gettime(void);
void			finish_process(t_data *data);
void			*ft_null(void *c);

/*---------------------philo_innut.c---------------------*/

//static int		alloc_mem(t_data *data);
//static int		init_mutex(t_data *data);
//static void		init_philo_data(t_philo *philo, int i);
//static int		create_threads(t_data *data);
int				initialize_philosophers(t_data *data);

/*---------------------philo_utils_01.c-----------------------*/
void			*routine(void *arg);
void			one_philo(t_data *data, char *time_to_die);
int				check_philo_status(t_philo *philo);

#endif
