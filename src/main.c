#include "fillit.h"

int		check_tetro(char *tetro, t_tetro *t)
{
	int sharps = 0, connections = 0;
	for (int i = 0; i < 20; i++)
	{
		if (tetro[i] == '#' && i % 5 != 4 && ++sharps < 5)
		{
			if (tetro[i + 1] == '#')
				connections++;
			if (i > 0 && tetro[i - 1] == '#')
				connections++;
			if (i < 14 && tetro[i + 5] == '#')
				connections++;
			if (i >= 5 && tetro[i - 5] == '#')
				connections++;
			t->r[sharps - 1] = i / 5;
			t->c[sharps - 1] = i % 5;
		}
		else if ((i % 5 == 4 && tetro[i] == '.') || (i % 5 != 4 && tetro[i] == '\n'))
			return 0;
	}
	return sharps == 4 && tetro[20] == '\n' && (connections == 6 || connections == 8);
}

void	check_and_parse_tetreminos(char *file_content, int size, t_tetro *tetro)
{
	for (int i = 0; i < size; i += 21)
	{
		if (check_tetro(file_content + i, &tetro[i / 21]) == 0)
		{
			printf("error\n");
			exit(1);
		}
	}
}

int		read_file(char *buf, char *file_name)
{
	int fd;
	int size;

	if ((fd = open(file_name, O_RDONLY)) == -1 || (size = read(fd, buf, 550)) < 0)
	{
		printf("error: bad file\n");
		return -1;
	}
	if (size < 19 || size > 546 || (size % 21 != 19 && size % 21 != 20))
	{
		printf("error: wrong file size\n");
		return -1;
	}
	buf[size++] = '\n';
	if (size % 21 == 20)
		buf[size++] = '\n';
	buf[size] = '\0';
	return size;
}

int		main(int argc, char **argv)
{
	if (argc != 2)
		printf("usage: %s file_name\n", argv[0]);
	else
	{
		char	buf[550];
		int		size;
		if ((size = read_file(buf, argv[1])) == -1)
			return -1;

		t_tetro		tetros[size / 21];
		check_and_parse_tetreminos(buf, size, tetros);

		fillit(tetros, size / 21);
	}
	return 0;
}
