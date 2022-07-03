/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*                                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnidia <bnidia@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 08:42:42 by bnidia            #+#    #+#             */
/*   Updated: 2022/05/31 18:43:23 by bnidia           ###    ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/** @name memory_clearing
 * @description clears the memory at the end of the program
 * @param t_main *m a main program struct
 * @return nothing
 * @author bnidia								*/
void	memory_clearing(t_main *m)
{
	int	i;

	i = 0;
	while (i != m->number_of_philosophers)
	{
		pthread_mutex_destroy(&m->mtx_forks[i]);
		i++;
	}
	free(m->mtx_forks);
	m->mtx_forks = NULL;
	free(m->philo);
	m->philo = NULL;
}
