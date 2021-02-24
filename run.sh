#!/bin/sh

gcc -Wall -Wextra -Werror -g -D BUFFER_SIZE=21 get_next_line.c get_next_line_utils.c main_multfd.c

#valgrind --dsymutil=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./a.out