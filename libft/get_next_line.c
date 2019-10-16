/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgena <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 17:46:54 by mgena             #+#    #+#             */
/*   Updated: 2019/10/16 21:38:25 by mgena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int		ft_strline(char **str, char **line)
{
	int		len;
	char	*tmp;

	len = 0;
	while ((*str)[len] != '\n' && (*str)[len])
		len++;
	if ((*str)[len] == '\n')
	{
		*line = ft_strsub(*str, 0, len);
		tmp = ft_strdup(*str + len + 1);
		free(*str);
		*str = tmp;
		if ((*str)[0] == '\0')
			ft_strdel(str);
	}
	else
	{
		*line = ft_strdup(*str);
		ft_strdel(str);
	}
	return (1);
}

int				get_next_line(const int fd, char **line)
{
	static char		*stc[10240];
	char			bs[BUFF_SIZE + 1];
	char			*tmp;
	int				ret;

	if (fd < 0 || !line)
		return (-1);
	while ((ret = read(fd, bs, BUFF_SIZE)) > 0)
	{
		bs[ret] = '\0';
		if (stc[fd] == NULL)
			stc[fd] = ft_strdup(bs);
		else
		{
			tmp = ft_strjoin(stc[fd], bs);
			free(stc[fd]);
			stc[fd] = tmp;
		}
		if (ft_strchr(stc[fd], '\n'))
			break ;
	}
	if (ret < 0 || stc[fd] == NULL)
		return (ret < 0 ? -1 : 0);
	return (ft_strline(&stc[fd], line));
}
