#ifndef FILLIT_H
# define FILLIT_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>

typedef struct	s_tetro
{
	int			r[4];
	int			c[4];
	int			p[4];
	int			i;
	int			c_max;
}				t_tetro;


void	fillit(t_tetro *tetros, int tetros_count);

#endif
