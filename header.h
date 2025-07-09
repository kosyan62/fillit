/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgena <mgena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 16:31:46 by mgena             #+#    #+#             */
/*   Updated: 2019/10/16 21:13:06 by mgena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H
# include "libft.h"
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

uint64_t			make_tetramino(const char *string);
int					get_tetraminos(int fd, t_tetramino tetraminoarr[26]);
void				get_pos(int i[2], t_tetramino *tet);
int					fillit(t_tetramino *tet, t_map *map);
void				error(void);
void				check_tetramino(uint64_t res);
uint64_t			bit_shift(uint64_t tet);
int					tetra_width(uint64_t tet);
int					tetra_height(uint64_t tet);

#endif
