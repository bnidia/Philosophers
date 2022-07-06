/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*                                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnidia <bnidia@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 08:42:42 by bnidia            #+#    #+#             */
/*   Updated: 2022/05/08 13:33:45 by bnidia           ###    ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "philo.h"

static int	start_philo_lifes(t_ph *p, int num_of_philo);
//static int	one_philosopher_case(t_main *m);

/** @name simulation
 * @description main frame of the program
 * @param t_main *m a main program struct
 * @return 0 on success, other values on error
 * @author bnidia											*/
int	simulation(t_main *m)
{
	if (start_philo_lifes(m->philo, m->number_of_philosophers))
		return (printf("start_philo_lifes() error\n"));
	while (42)
	{
		if (read_write_dead_flag(READ, NULL))
			break ;
		usleep(5000);
	}
	return (0);
}

/** @name start_philo_lifes
 * @description brings philosophers to life
 * First, we run odd philosophers i = 0 for philosopher 1
 * Then we launch even philosophers
 * @param t_ph *p, int num_of_philo
 * @return 0 on success, other values on error
 * @author bnidia											*/
static int	start_philo_lifes(t_ph *p, int num_of_philo)
{
	int		i;

	i = 0;
	while (i < num_of_philo)
	{
		if (pthread_create(&p[i].tid, NULL, philosopher, (void *) &p[i]) != 0)
			return (printf("pthread_create() error!\n"));
		pthread_detach(p[i].tid);
		i += 2;
	}
	i = 1;
	usleep(1000);
	while (i < num_of_philo)
	{
		if (pthread_create(&p[i].tid, NULL, philosopher, (void *) &p[i]) != 0)
			return (printf("pthread_create() error!\n"));
		pthread_detach(p[i].tid);
		i += 2;
	}
	return (0);
}
