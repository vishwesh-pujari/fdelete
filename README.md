# fdelete

C gives us fscanf(), fprintf(), fread(), fwrite() but doesn't provide any function for deleting specific part of a file

fdelete() is the function for this purpose.

One simple solution to this problem using a temporary file is discussed in http://www.tutorialspanel.com/delete-a-specific-line-from-a-text-file-using-c/index.htm

Another solution would be to read entire file inside memory and then write everything except line to be deleted back into the same file. But this solution is memory inefficient in case of large files.

My attempt in this code is to write a function to delete a line from a file without the need of an extra file and by storing only a single byte from the file at a time in memory.

Compilation: gcc -Wall fdelete.c main.c
