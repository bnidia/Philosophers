/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*                                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnidia <bnidia@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 08:42:42 by bnidia            #+#    #+#             */
/*   Updated: 2022/05/03 16:15:04 by bnidia           ###    ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//801 1 is died. Process is finished
//2806 4 has taken a fork
//All the philosophers ate 7 times. Process is finished

size_t	ft_numlen(unsigned long long num, int base)
{
	size_t	i;

	i = 0;
	if (num == 0)
		return (1);
	while (num)
	{
		num /= base;
		i++;
	}
	return (i);
}

void	ft_itoa(char *s, int *s_i, long nbr)
{
	int	numlen;
	int	i;

	if (nbr == 0)
	{
		s[(*s_i)++] = '0';
		return ;
	}
	numlen = (int)ft_numlen(nbr, 10) - 1;
	i = 0;
	while (i <= numlen)
	{
		s[*s_i + numlen - i] = "0123456789"[nbr % 10];
		nbr /= 10;
		i++;
	}
	*s_i += numlen + 1;
}

void	print(t_philo *p, char *str)
{
	char	s[64];
	int		s_i;

	s_i = 0;
	ft_itoa(s, &s_i, get_time());
	s[s_i++] = ' ';
	ft_itoa(s, &s_i, p->id);
	while(*str != '\0')
		s[s_i++] = *str++;
	s[s_i++] = '\n';
	write(1, s, s_i);
}

void	print_status(t_philo *p)
{
	pthread_mutex_lock(&mtx_print);
	if (DIED)
		print(p, " is died. Process is finished");
	pthread_mutex_unlock(&mtx_print);
}

void	print_end()
{
	char	s[32];
	int 	s_i;

	s_i = 0;
	pthread_mutex_lock(&mtx_print);
	write(1, "All the philosophers ate ", 25);
	ft_itoa(s, &s_i, setup->number_of_eat);
	write(1, s, s_i);
	write(1, " times. Process is finished\n", 27);
	pthread_mutex_unlock(&mtx_print);
}