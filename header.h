/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgena <mgena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 16:31:46 by mgena             #+#    #+#             */
/*   Updated: 2019/10/16 20:01:32 by mgena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H
# include "libft/libft.h"
# include "fcntl.h"

typedef	struct		s_tetramino
{
	u_int64_t		cont;
	int				x;
	int				y;
	int				height;
	int				width;
}					t_tetramino;
typedef	struct		s_map
{
	u_int16_t		cont[16];
	int				tetramino_count;
	int				size;
}					t_map;

#endif
