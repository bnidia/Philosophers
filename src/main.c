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

#include "philo.h"

int	ft_atoi(const char *num_ptr)
{
	ssize_t		num;
	int			sign;

	num = 0;
	sign = 1;
	while (*num_ptr == '\t' || *num_ptr == '\n' || *num_ptr == '\v' \
		|| *num_ptr == '\f' || *num_ptr == '\r' || *num_ptr == ' ')
		num_ptr++;
	if (*num_ptr == '-')
		sign = -1;
	if (*num_ptr == '-' || *num_ptr == '+')
		num_ptr++;
	while (*num_ptr >= '0' && *num_ptr <= '9')
		num = num * 10 + *num_ptr++ - '0';
	if (num * sign > INT_MAX || num * sign < INT_MIN)
		return (0);
	return ((int)num * sign);
}

int	init(t_setup *s, int argc, char *argv[])
{
	if (argc >= 5)
	{
		s->number_of_philosophers = ft_atoi(argv[1]);
		s->time_to_die = ft_atoi(argv[2]);
		s->time_to_eat = ft_atoi(argv[3]);
		s->time_to_sleep = ft_atoi(argv[4]);
	}
	//if (argc == 6)
	return (0);
}

void *print(void *buf)
{
	for (int i = 0; i < 20; i++)
	{
		write(1, (char *)buf, strlen(buf));
		usleep(100000);
	}
	return NULL;
}

int	main(int argc, char *argv[])
{
	int	err;


}