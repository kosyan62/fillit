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

/*
** Tetramino structure:
** Represents a single tetramino piece with its bit pattern and dimensions
** - cont: 64-bit representation of the tetramino shape (4x4 grid encoded as bits)
** - x: X coordinate of the tetramino's position on the map
** - y: Y coordinate of the tetramino's position on the map
** - height: Height of the tetramino in grid units
** - width: Width of the tetramino in grid units
*/
typedef	struct		s_tetramino
{
	u_int64_t		cont;
	int				x;
	int				y;
	int				height;
	int				width;
}					t_tetramino;

/*
** Map structure:
** Represents the game board where tetraminos are placed
** - cont: Array of 16-bit values representing each row of the map
** - tetramino_count: Number of tetraminos to be placed
** - size: Current size of the square map (size x size)
*/
typedef	struct		s_map
{
	u_int16_t		cont[16];
	int				tetramino_count;
	int				size;
}					t_map;

/*
** Function prototypes with documentation:
*/

/*
** make_tetramino - Converts string representation to bit pattern
** @string: 4x4 grid string with '#' and '.' characters
** Returns: 64-bit representation of the tetramino
** Side effects: Calls error() if invalid format
*/
uint64_t			make_tetramino(const char *string);

/*
** get_tetraminos - Reads tetraminos from file descriptor
** @fd: File descriptor to read from
** @tetraminoarr: Array to store parsed tetraminos
** Returns: Number of tetraminos read
** Side effects: Calls error() if invalid input format
*/
int					get_tetraminos(int fd, t_tetramino tetraminoarr[26]);

/*
** get_pos - Sets position coordinates for a tetramino
** @i: Array containing [x, y] coordinates
** @tet: Tetramino structure to update
** Returns: void
** Side effects: Modifies tet->x and tet->y
*/
void				get_pos(int i[2], t_tetramino *tet);

/*
** fillit - Main backtracking algorithm to place tetraminos
** @tet: Array of tetraminos to place
** @map: Map structure representing the game board
** Returns: 1 if successful placement, 0 if no solution
** Side effects: Modifies map content and tetramino positions
*/
int					fillit(t_tetramino *tet, t_map *map);

/*
** error - Prints error message and exits program
** Returns: void (never returns)
** Side effects: Prints "error\n" and exits with code 0
*/
void				error(void);

/*
** check_tetramino - Validates tetramino shape against known patterns
** @res: 64-bit tetramino representation
** Returns: void
** Side effects: Calls error() if invalid shape
*/
void				check_tetramino(uint64_t res);

/*
** bit_shift - Normalizes tetramino to top-left position
** @tet: Raw tetramino bit pattern
** Returns: Normalized tetramino bit pattern
** Side effects: Calls error() if invalid pattern
*/
uint64_t			bit_shift(uint64_t tet);

/*
** tetra_width - Calculates width of tetramino
** @tet: Tetramino bit pattern
** Returns: Width in grid units
** Side effects: None
*/
int					tetra_width(uint64_t tet);

/*
** tetra_height - Calculates height of tetramino
** @tet: Tetramino bit pattern
** Returns: Height in grid units
** Side effects: None
*/
int					tetra_height(uint64_t tet);

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
