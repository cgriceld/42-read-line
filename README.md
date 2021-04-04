# readline

42 algorithmic project. The code is written in accordance with The Norm (42 coding style).

This function allows to read one text line at a time from a file. It also supports reading from \
several fd without loosing a thread in each of the files.\
Return:
- 1 (found new line and there is still something to read further)
- 0 (EOF)
- -1 (any error)

`run.sh` is a plain script that contains compilation line where you can change buffer size\
and as well run valgrind to test on leaks.

`main_fd.c` - test reading from one file.\
`main_multfd.c` - test reading from multiple files (read by turns one line from two files).

Tests:
- file with only one line
- long file with BUFFER_SIZE=9999
- long file with BUFFER_SIZE=1
- BUFFER_SIZE is exactly the line length
