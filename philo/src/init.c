/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*                                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnidia <bnidia@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 08:42:42 by bnidia            #+#    #+#             */
/*   Updated: 2022/05/10 20:31:29 by bnidia           ###    ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_philosophers(t_main *m);

/** @name init
 * @description initialises main struct with parameters from command line,
 * checks some input errors and starts init_philosophers function
 * @param t_main *m a main program struct
 * int argc, char *argv[] - command line parameters
 * @return 0 if successful, other values on error
 * @author bnidia														*/
int	init(t_main *m, int argc, char *argv[])
{
	if (argc != 5 && argc != 6)
		return (printf("Arguments error. Need 4 or 5.\n"));
	if (ft_atoi_r(argv[1], &m->number_of_philosophers)
		|| ft_atoi_r(argv[2], &m->time_to_die)
		|| ft_atoi_r(argv[3], &m->time_to_eat)
		|| ft_atoi_r(argv[4], &m->time_to_sleep))
		return (printf("Parameters parsing error.\n"));
	if (argc == 6 && ft_atoi_r(argv[5], &m->number_of_eat))
		return (printf("Parameter parsing error.\n"));
	if (m->number_of_philosophers < 1 || m->time_to_die < 0
		|| m->time_to_eat < 0 || m->time_to_sleep < 0
		|| (argc == 6 && m->number_of_eat < 0))
		return (printf("Invalid arguments.\n"));
	if (init_philosophers(m) != 0)
		return (printf("init_philosophers error\n"));
	return (0);
}

/** @name init_philosophers
 * @description allocates memory for forks and philosophers,
 * initialises mutex for forks, saves them to left and right
 * philosophers hands
 * The numbering of philosophers in the conclusion begins with one.
 * We give the last philosopher a fork with a smaller number in his right hand,
 * as Edsger Dijkstra bequeathed to us in 1965
 * @param t_main *m a main program struct
 * @return 0 if successful, other values on error
 * @author bnidia								*/
static int	init_philosophers(t_main *m)
{
	int	i;

	i = m->number_of_philosophers;
	m->philo = (t_ph *)malloc(sizeof(t_ph) * i);
	m->mtx_forks = (t_mutex *)malloc(sizeof(t_mutex) * i);
	if (m->philo == NULL || m->mtx_forks == NULL)
		return (printf("Memory. Malloc error.\n"));
	i = 0;
	while (i < m->number_of_philosophers)
	{
		m->philo[i] = (t_ph){};
		m->philo[i].id = i + 1;
		m->philo[i].number_of_eat = m->number_of_eat;
		if (pthread_mutex_init(&m->mtx_forks[i], NULL) != 0)
			return (printf("Init t_mutex fork error.\n"));
		m->philo[i].left_fork = &m->mtx_forks[i];
		if (i == m->number_of_philosophers - 1)
			m->philo[i].right_fork = &m->mtx_forks[0];
		else
			m->philo[i].right_fork = &m->mtx_forks[i + 1];
		m->philo[i].m = m;
		i++;
	}
	return (0);
}
