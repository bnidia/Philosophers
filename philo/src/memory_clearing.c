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

int 	memory_clearing(t_main *m)
{
	int i;

	i = 0;
	while (i != m->number_of_philosophers)
	{
		pthread_mutex_destroy(&m->mtx_forks[i]);
		i++;
	}
	pthread_mutex_destroy(&m->mtx_print);
	pthread_mutex_destroy(&m->mtx_dead);
	pthread_mutex_destroy(&m->mtx_satisfied);
	free(m->mtx_forks);
	m->mtx_forks = NULL;
	free(m->philo);
	m->philo = NULL;

	return (0);
}
