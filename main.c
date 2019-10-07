/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgena <mgena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 16:39:51 by mgena             #+#    #+#             */
/*   Updated: 2019/09/30 18:34:30 by mgena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <stdio.h>

void print_tetramino(const u_int16_t *tet)
{
	for (int i = 0; i < 4; i++) {
		for (int j = 15; j >= 0; j--) {
			printf("%d", tet[i] >> j & 1);
		}
		printf("\n");
	}
	printf("\n");
}

void    print_map(const u_int16_t *array) {
	for (int i = 0; i < 16; i++) {
		for (int j = 15; j >= 0; j--) {
			printf("%d", array[i] >> j & 1);
		}
		printf("\n");
	}
}

void error(void)
{
    ft_putstr("error\n");
    exit(0);
}

u_int64_t bit_shift(u_int64_t tet)
{
	while ((9223512776490647552U & tet) == 0)
		tet <<= 1;
	while ((61440U & tet) == 0)
		tet >>= 16;
	return (tet);
}

u_int64_t    make_tetramino(const char *string)
{
    u_int64_t res;
    u_int64_t tmp;
	size_t i;

	i = 0;
    tmp = 0;
    res = 0;
    while (i != 19)
    {
        if (string[i] == '#')
            res = res | (1 << tmp);
        if (string[i++] == '\n')
        {
            res = res << 16;
            tmp = 0;
        }
        else
	        tmp++;
    }
	res = reverse_bits_64(res);
	res = bit_shift(res);
    return (res);
}

void get_tetraminos(int fd, u_int64_t tetraminoarr[26])
{
	char tetrachr[22];
	int x;

	x = 0;
	ft_bzero(tetrachr, 22);

	while (read(fd, tetrachr, 21) > 0)
	{
		tetraminoarr[x++] = make_tetramino(tetrachr);
	}
	if (tetrachr[21] == '\n')
		error();
}

int main(void)
{
	int fd;
	char *line;
	u_int64_t tetramino_array[26];
	u_int16_t map[16];
	int i = 0;

	fd = open("test", O_RDONLY);
    get_tetraminos(fd, tetramino_array);
    while (i != 5)
    {
    	printf("%llu\n", tetramino_array[i]);
    	print_tetramino((const u_int16_t *) &(tetramino_array[i++]));
    }
	*(u_int64_t*)(map)  ^= tetramino_array[0];
	*(u_int64_t*)(map)  ^= tetramino_array[1] >> 1;
    print_map(map);
    return 0;
}