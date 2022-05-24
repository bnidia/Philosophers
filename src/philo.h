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

typedef struct s_main	t_main;
typedef struct s_philo	t_ph;
typedef pthread_mutex_t mutex;

struct s_main
{
// Входные данные
	int 	number_of_philosophers;
	int 	time_to_die;
	int 	time_to_eat;
	int 	time_to_sleep;
	int 	number_of_times_each_philosopher_must_eat;

	// Ссылка на философов
	t_ph	*philo;

	// Мьютексы на вилки, печать и смерть
	mutex	*mtx_forks;
	mutex	mtx_print;
	mutex	mtx_dead;

	// Переменная на случай ошибок
	int 			err;
};

struct s_philo
{
	int			id;
	int			count_of_eat;
	pthread_t	tid;
	mutex		*left_fork;
	mutex		*right_fork;
	size_t		last_time_eat;
	t_main		*params;
};

// Основа программы
int		init(t_main *m, int argc, char **argv);
int 	simulation(t_main *m);
int 	memory_clearing(t_main *m);

// Функции для инициализации
int	ft_atoi_zero(const char *num_ptr);

// Функция философа
void	*p_life(void *args);

long	get_time(void);
void	ft_usleep(long time);
void	print(t_ph *p, char *str);

#endif
