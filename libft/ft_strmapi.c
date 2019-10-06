/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgena <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 10:25:34 by mgena             #+#    #+#             */
/*   Updated: 2019/09/16 19:54:12 by mgena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t			len;
	unsigned int	i;
	char			*res;

	if (s == NULL || f == NULL)
		return (NULL);
	len = ft_strlen(s);
	res = ft_strnew(len);
	if (res == NULL)
		return (NULL);
	i = 0;
	while (i != len)
	{
		res[i] = f(i, s[i]);
		i++;
	}
	return (res);
}
