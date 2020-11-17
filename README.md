# get_next_line

`run.sh` is a plain script that contains compilation line where you can change buffer size\
and as well run valgrind to test on leaks.

`main_fd.c` - test reading from one file.\
`main_multfd.c` - test reading from multiple files (read by turns one line from two files).

Tests:
- file with only one line
- long file with BUFFER_SIZE=9999
- long file with BUFFER_SIZE=1
- BUFFER_SIZE is exactly the line length