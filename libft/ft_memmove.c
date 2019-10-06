/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgena <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 10:46:32 by mgena             #+#    #+#             */
/*   Updated: 2019/09/10 13:27:37 by mgena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*res;

	i = 0;
	res = (char*)dest;
	if (dest == NULL && src == NULL)
		return (NULL);
	if ((char*)dest > (char*)src)
	{
		while (n != i)
		{
			n--;
			((char*)dest)[n] = ((char*)src)[n];
		}
	}
	else
	{
		while (i != n)
		{
			((char*)dest)[i] = ((char*)src)[i];
			i++;
		}
	}
	return (res);
}
