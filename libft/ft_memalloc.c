/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgena <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 10:22:06 by mgena             #+#    #+#             */
/*   Updated: 2019/09/25 14:56:21 by mgena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	char *res;

	if (size == 0)
		return (NULL);
	res = malloc(size);
	if (res == NULL)
		return (NULL);
	while (size != 0)
	{
		((char*)res)[--size] = 0;
	}
	return (res);
}
