#include "fillit.h"

static void		print_map(char *map, int map_side_size)
{
	for (int i = 0; i < map_side_size; i++)
	{
		for (int j = 0; j < map_side_size; j++)
			printf("%c", map[j + map_side_size * i]);
		printf("\n");
	}
}

static void		initiate_tetros(t_tetro *tetros, int tetros_count)
{
	for (int i = 0; i < tetros_count; i++)
	{
		tetros[i].c_max = 0;
		tetros[i].i = 0;
		int minr = tetros[i].r[0];
		int minc = tetros[i].c[0];
		for (int j = 1; j < 4; j++)
		{
			if (tetros[i].r[j] < minr)
				minr = tetros[i].r[j];
			if (tetros[i].c[j] < minc)
				minc = tetros[i].c[j];
		}
		for (int j = 0; j < 4; j++)
		{
			tetros[i].r[j] -= minr;
			tetros[i].c[j] -= minc;
			if (tetros[i].c[j] > tetros[i].c_max)
				tetros[i].c_max = tetros[i].c[j];
		}
	}
}

static int	find_minimum_map_size(int tetros_count)
{
	int map_side_size = 2;

	while (map_side_size * map_side_size < tetros_count * 4)
		map_side_size++;
	return map_side_size;
}

static void		calculate_sharp_placement(t_tetro *tetros, int tetros_count, int map_side_size)
{
	for (int i = 0; i < tetros_count; i++)
	{
		tetros[i].p[0] = tetros[i].c[0];
		tetros[i].p[1] = tetros[i].c[1] + map_side_size * tetros[i].r[1];
		tetros[i].p[2] = tetros[i].c[2] + map_side_size * tetros[i].r[2];
		tetros[i].p[3] = tetros[i].c[3] + map_side_size * tetros[i].r[3];
	}
}

static int		place_tetro(t_tetro *tetro, char let, int map_side_size, char *map)
{
	int map_len = map_side_size * map_side_size;
	for (int i = tetro->i; i < map_len; i++)
	{
		if (tetro->c_max + i % map_side_size >= map_side_size)
			continue ;
		if (i + tetro->p[3] >= map_len)
			return 0;
		if (map[i + tetro->p[0]] == '.'
		&& map[i + tetro->p[1]] == '.'
		&& map[i + tetro->p[2]] == '.'
		&& map[i + tetro->p[3]] == '.')
		{
			map[i + tetro->p[0]] = let;
			map[i + tetro->p[1]] = let;
			map[i + tetro->p[2]] = let;
			map[i + tetro->p[3]] = let;
			tetro->i = i;
			return 1;
		}
	}
	return 0;
}

void	fillit(t_tetro *tetros, int tetros_count)
{
	char	map[144];
	memset(map, '.', 144);

	initiate_tetros(tetros, tetros_count);
	int map_side_size = find_minimum_map_size(tetros_count);
	calculate_sharp_placement(tetros, tetros_count, map_side_size);
	for (int i = 0; i < tetros_count; i++)
	{
		if (place_tetro(&tetros[i], i + 'A', map_side_size, map) == 0)
		{
			tetros[i--].i = 0;
			if (i == -1 && map_side_size++)
				calculate_sharp_placement(tetros, tetros_count, map_side_size);
			else
			{
				map[tetros[i].p[0] + tetros[i].i] = '.';
				map[tetros[i].p[1] + tetros[i].i] = '.';
				map[tetros[i].p[2] + tetros[i].i] = '.';
				map[tetros[i].p[3] + tetros[i].i] = '.';
				tetros[i--].i += 1;
			}
		}
	}
	print_map(map, map_side_size);
}
