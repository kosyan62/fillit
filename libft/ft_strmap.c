/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgena <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 10:25:16 by mgena             #+#    #+#             */
/*   Updated: 2019/09/16 19:53:35 by mgena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	size_t	len;
	size_t	i;
	char	*res;

	if (s == NULL || f == NULL)
		return (NULL);
	len = ft_strlen(s);
	res = ft_strnew(len);
	if (res == NULL)
		return (NULL);
	i = 0;
	while (i != len)
	{
		res[i] = f(s[i]);
		i++;
	}
	return (res);
}
