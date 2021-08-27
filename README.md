# fdelete

C gives us fscanf(), fprintf(), fread(), fwrite() but doesn't provide any function for deleting specific part of a file

fdelete() is the function for this purpose.

One simple solution to this problem is discussed in http://www.tutorialspanel.com/delete-a-specific-line-from-a-text-file-using-c/index.htm

My attempt in this code is to write a function to delete a line from a file without the need of an extra file and by storing only a single byte from the file at a time in memory.
