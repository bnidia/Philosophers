/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*                                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnidia <bnidia@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 08:42:42 by bnidia            #+#    #+#             */
/*   Updated: 2022/05/24 15:13:42 by bnidia           ###    ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	eat(t_ph *p);
static int	sleep(t_ph *p);
static int	think(t_ph *p);
static int	eat_counting(t_ph *p);

/** @name philosopher
 * @description The philosopher's life function, or the parallel flow function
 * @param void *args accepts a pointer to void*,
 * providing the ability to pass any variables and structures here
 * @return void* can return references to any variables
 * @author bnidia														*/
void	*philosopher(void *args)
{
	t_ph			*p;

	p = (t_ph *)args;
	gettimeofday(&p->eat_before, NULL);
	while (!(
			eat(p) || \
			sleep(p) || \
			think(p) \
	));
	return ((void *)0);
}

/** @name eat
 * @description simulates philosophers eating
 * @param t_ph *p a philosopher struct
 * @return 0 if successful, 1 otherwise
 * @author bnidia												*/
static int	eat(t_ph *p)
{
	gettimeofday(&p->event, NULL);
	if (dead_handler(p, false))
		return (1);
	pthread_mutex_lock(p->left_fork);
	gettimeofday(&p->event, NULL);
	print(p->event, p, " has taken a fork\n");
	pthread_mutex_lock(p->right_fork);
	gettimeofday(&p->event, NULL);
	print(p->event, p, " has taken a fork\n");
	print(p->event, p, " is eating\n");
	if (eat_counting(p))
	{
		pthread_mutex_unlock(p->right_fork);
		pthread_mutex_unlock(p->left_fork);
		return (1);
	}
	p->eat_before = \
	calc_time_sum(&p->event, p->m->time_to_eat + p->m->time_to_die);
	sleep_to(p->event, p->m->time_to_eat);
	pthread_mutex_unlock(p->right_fork);
	pthread_mutex_unlock(p->left_fork);
	return (0);
}

/** @name sleep
 * @description simulates philosophers sleeping
 * @param t_ph *p a philosopher struct
 * @return 0 if successful, 1 otherwise
 * @author bnidia								*/
static int	sleep(t_ph *p)
{
	gettimeofday(&p->event, NULL);
	if (dead_handler(p, false))
		return (1);
	print(p->event, p, " is sleeping\n");
	sleep_to(p->event, p->m->time_to_sleep);
	return (0);
}

/** @name think
 * @description simulates philosophers thinking
 * @param t_ph *p a philosopher struct
 * @return 0 if successful, 1 otherwise
 * @author bnidia 								*/
static int	think(t_ph *p)
{
	gettimeofday(&p->event, NULL);
	if (dead_handler(p, false))
		return (1);
	print(p->event, p, " is thinking\n");
	return (0);
}

/** @name eat_counting
 * @description controls number of eat, when it equals to desired number of eat
 * stops philosopher. If it is the last satisfied philosopher, function sets
 * dead variable to the true, so main cycle can stop
 * @param t_ph *p a philosopher struct
 * @return 0 if successful, 1 otherwise
 * @author bnidia								*/
static int	eat_counting(t_ph *p)
{
	static int		satisfied = 0;
	static t_mutex	mtx_satisfied = PTHREAD_MUTEX_INITIALIZER;

	p->number_of_eat--;
	if (p->number_of_eat == 0)
	{
		pthread_mutex_lock(&mtx_satisfied);
		satisfied++;
		if (satisfied == p->m->number_of_philosophers)
		{
			printf("All %d philosophers ate %d times", \
					satisfied, p->m->number_of_eat);
			dead_handler(p, true);
		}
		pthread_mutex_unlock(&mtx_satisfied);
		return (1);
	}
	return (0);
}
