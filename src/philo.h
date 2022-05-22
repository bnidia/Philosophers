/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*                                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnidia <bnidia@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 08:42:42 by bnidia            #+#    #+#             */
/*   Updated: 2022/05/02 14:33:00 by bnidia           ###    ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_main
{
// Входные данные
	int 			number_of_philosophers;
	int 			time_to_die;
	int 			time_to_eat;
	int 			time_to_sleep;
	int 			number_of_times_each_philosopher_must_eat;
// Мьютексы на вилки, печать и смерть
	pthread_mutex_t	*mtx_forks;
	pthread_mutex_t	mtx_print;
	pthread_mutex_t	mtx_dead;
// Переменная на случай ошибок
	int 			err;
}				t_main;

typedef struct s_philo
{
	int				id;
	int				count_of_eat;
	pthread_t		tid;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	mtx_eat;
	long long int	last_time_eat;
	t_main			*params;
}				t_philo;

// Основа программы
int		init(t_main *m, int argc, char **argv);
int 	simulation(t_main *m);
int 	memory_clearing(t_main *m);


long	get_time(void);
void	ft_usleep(long time);
void	print(t_philo *p, char *str);

#endif
