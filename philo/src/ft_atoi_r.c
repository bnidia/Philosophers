/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*                                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnidia <bnidia@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 08:42:42 by bnidia            #+#    #+#             */
/*   Updated: 2022/05/22 16:07:23 by bnidia           ###    ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/** @name ft_atoi_r
 * @description converts string to integer
 * @param const char *num_ptr, int *result
 * @return 0 if successful, 1 as error, when >INT_MAX <INT_MIN or letters
 * @example "   -0156" -> -156
 * @author bnidia								*/
int	ft_atoi_r(const char *num_ptr, int *result)
{
	ssize_t		num;
	int			sign;

	num = 0;
	sign = 1;
	while (*num_ptr == '\t' || *num_ptr == '\n' || *num_ptr == '\v' \
		|| *num_ptr == '\f' || *num_ptr == '\r' || *num_ptr == ' ')
		num_ptr++;
	if (*num_ptr == '-' || *num_ptr == '+')
		if (*num_ptr++ == '-')
			sign = -1;
	while (*num_ptr >= '0' && *num_ptr <= '9')
		num = num * 10 + *num_ptr++ - '0';
	if (num * sign > INT_MAX || num * sign < INT_MIN || *num_ptr != '\0')
		return (1);
	*result = (int)num;
	return (0);
}
