/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_bits_64.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgena <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 17:57:04 by mgena             #+#    #+#             */
/*   Updated: 2019/10/07 17:57:06 by mgena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

uint64_t	reverse_bits_64(uint64_t tet)
{
	int			i;
	uint64_t	x;
	uint64_t	res;

	x = 1;
	i = 63;
	res = 0;
	while (i > 0)
	{
		res = res | ((tet & x) << i);
		x = x << 1;
		i -= 2;
	}
	i = 1;
	while (i < 64)
	{
		res = res | ((tet & x) >> i);
		x = x << 1;
		i += 2;
	}
	return (res);
}
