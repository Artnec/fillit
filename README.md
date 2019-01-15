# fillit

algorithm that gets as input [tetromino](https://en.wikipedia.org/wiki/Tetromino) shaped pieces, and fits them on smallest possible square map.


how to use fillit:
```
file named sample contains four tetromino shaped pieces.
cat -e sample
....$
##..$
.#..$
.#..$
$
....$
####$
....$
....$
$
#...$
###.$
....$
....$
$
....$
##..$
.##.$
....$

fillit produces smallest possible square containing all of pieces from given file.
./fillit sample
DDAA
CDDA
CCCA
BBBB
```

file given to fillit as argument must contain at least 1 and at most 26 valid pieces,
which must be separated by one new line.
piece is valid if it has exactly four connected '#' symbols,
and twelve '.' symbols, on 4 by 4 square grid.
