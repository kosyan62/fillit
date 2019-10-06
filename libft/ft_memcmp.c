/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgena <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 10:42:07 by mgena             #+#    #+#             */
/*   Updated: 2019/09/16 19:48:25 by mgena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	int res;

	if ((s1 == NULL && s2 == NULL) || n == 0)
		return (0);
	while (*(char*)s1 == *(char*)s2 && n != 1)
	{
		n--;
		s1++;
		s2++;
	}
	res = ((*(unsigned char*)s1 - *(unsigned char*)s2));
	return (res);
}
