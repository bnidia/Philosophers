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
# define YELLOW "\e[33m"
# define YELLOW_RESET "\e[0m"
# define TIME_FORMAT 9

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
typedef struct timeval	t_time;
typedef pthread_mutex_t mutex;

struct s_main
{
// Входные данные
	int 	number_of_philosophers;
	int 	time_to_die;
	int 	time_to_eat;
	int 	time_to_sleep;
	int 	number_of_eat;

	// Ссылка на философов
	t_ph	*philo;

	// Мьютексы на вилки, печать и смерть
	mutex	*mtx_forks;
	mutex	mtx_print;
	mutex	mtx_dead;
	mutex	mtx_satisfied;
	// Кто-то умер
	int		dead;
	int 	satisfied;
};

struct s_philo
{
	char			id[16]; //номер с 1, для вывода логов
	int				count_of_eat;
	pthread_t		tid;
	mutex			*left_fork;
	mutex			*right_fork;
	t_time			t_event;
	t_time			t_last_time_eat;
	t_main			*m;
};

// Основа программы
int		init(t_main *m, int argc, char **argv);
int 	simulation(t_main *m);
int 	memory_clearing(t_main *m);

// Функции для инициализации
int		ft_atoi_r(const char *num_ptr, int *result);
void	itoa_append(char *s, int *s_i, long nbr);
void	str_append(char *s, int *s_i, char *str);

// Функция философа
void	*p_life(void *args);

void	sleep_to(t_time t_event);
void	print(t_ph *p, t_time time, char *str);
void	print_all_ate(t_main *m);
void	convert_time(t_time *t_event, long time);

#endif
