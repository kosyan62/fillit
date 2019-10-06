/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgena <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 10:26:27 by mgena             #+#    #+#             */
/*   Updated: 2019/09/16 19:54:39 by mgena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	i;

	if (s == NULL)
		return (NULL);
	res = ft_strnew(len);
	if (res == 0)
		return (NULL);
	i = 0;
	while (i != len)
	{
		res[i] = s[start];
		i++;
		start++;
	}
	return (res);
}
