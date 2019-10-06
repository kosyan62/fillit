/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgena <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 20:12:12 by mgena             #+#    #+#             */
/*   Updated: 2019/09/17 18:19:23 by mgena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	int		d;
	char	*res;

	d = ft_countdigits(n);
	d = (n < 0) ? ++d : d;
	res = ft_strnew(d);
	if (res == NULL)
		return (NULL);
	if (n < 0)
	{
		if (n == -2147483648)
			return (ft_strcpy(res, "-2147483648"));
		res[0] = '-';
		n = -n;
	}
	else if (n == 0)
		ft_strcpy(res, "0");
	while (n != 0)
	{
		res[d - 1] = n % 10 + '0';
		d--;
		n /= 10;
	}
	return (res);
}
