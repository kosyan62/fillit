/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgena <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 11:48:02 by mgena             #+#    #+#             */
/*   Updated: 2019/09/10 13:24:47 by mgena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t i;

	i = 0;
	while (i != n)
	{
		((unsigned char*)dest)[i] = ((unsigned char*)src)[i];
		if ((unsigned char)c == ((unsigned char*)src)[i++])
			return (&((unsigned char*)dest)[i]);
	}
	return (NULL);
}
