# fdelete
The OS gives us functions such as open(), read(), write(), close(), lseek() to handle files.

But the OS doesn't provide a function to delete something from a file.

One simple solution to this problem is discussed in http://www.tutorialspanel.com/delete-a-specific-line-from-a-text-file-using-c/index.htm

My attempt in this code is to write a function to delete a line from a file without the need of an extra file and by storing only a single line from the file at a time in memory.
