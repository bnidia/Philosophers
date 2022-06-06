/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*                                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnidia <bnidia@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 08:42:42 by bnidia            #+#    #+#             */
/*   Updated: 2022/05/30 15:43:17 by bnidia           ###    ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_numlen(unsigned long long num, int base);

void	itoa_append(char *s, int *s_i, long nbr)
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

int	ft_numlen(unsigned long long num, int base)
{
	int	i;

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