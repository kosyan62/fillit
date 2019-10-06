/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgena <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 17:40:45 by mgena             #+#    #+#             */
/*   Updated: 2019/09/25 14:58:52 by mgena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static const char	*miss_space(const char *nptr)
{
	while ((*nptr > 8 && *nptr < 14) || *nptr == 32)
		nptr++;
	return (nptr);
}

static long			flag_ret(long res, const char *nptr, short flag)
{
	if (flag == 0)
	{
		if (res == 922337203685477580 && *nptr <= '7')
			return (-((res * 10) + (*nptr - '0')));
		else
			return (-9223372036854775807 - 1);
	}
	else
	{
		if (res == 922337203685477580 && *nptr <= '7')
			return (res * 10 + (*nptr - '0'));
		else
			return (9223372036854775807);
	}
}

long				ft_atol(const char *nptr)
{
	short	flag;
	long	res;

	res = 0;
	flag = 1;
	nptr = miss_space(nptr);
	if (*nptr == '-')
		flag = 0;
	else if (*nptr == '+')
		flag = 1;
	if (*nptr == '-' || *nptr == '+')
		nptr++;
	while (*nptr >= '0' && *nptr <= '9')
	{
		if (res >= 922337203685477580)
		{
			res = flag_ret(res, nptr, flag);
			flag = 2;
			break ;
		}
		res = res * 10 + (*nptr - '0');
		nptr++;
	}
	res = (flag == 0) ? -res : res;
	return (res);
}
