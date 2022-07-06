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
# define READ 0
# define WRITE 1

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_main	t_main;
typedef struct s_philo	t_ph;
typedef struct timeval	t_time;
typedef pthread_mutex_t	t_mutex;

struct s_main
{
	int		number_of_philosophers;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		number_of_eat;
	t_ph	*philo;
	t_mutex	*mtx_forks;
};

struct s_philo
{
	int			id;
	pthread_t	tid;
	t_mutex		*left_fork;
	t_mutex		*right_fork;
	int			number_of_eat;
	t_time		event;
	t_time		best_before;
	t_main		*m;
};

// The basis of the program
int			init(t_main *m, int argc, char **argv);
int			simulation(t_main *m);
void		memory_clearing(t_main *m);

// Functions for initialization
int			ft_atoi_r(const char *num_ptr, int *result);

// The function of the philosopher
void		*philosopher(void *args);
void		sleep_to(t_time t_event, int time);
void		print(t_time time, t_ph *p, char *str, bool lock);
t_time		calc_time_sum(t_time *t_event, long time);

bool		dead_handler(t_ph *p);
t_time		read_write_best_before(t_ph *p, int flag, t_time *write_value);
bool		read_write_dead_flag(int flag, bool set_dead);
long long	calc_time_diff(t_time *minuend, t_time *subtrahend);

#endif
