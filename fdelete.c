/*
 * TODO - write fmodify()
 * C gives us fscanf(), fprintf(), fread(), fwrite() but doesn't provide any function for deleting specific part of a file
 * fdelete() is the function for this purpose.
 *
 * man 2 truncate
 * The function fileno() returns the file descriptor associated with an open FILE *.
 * Display File byte by byte: od -c -b filename
 */

#include <errno.h>
#include <unistd.h>
#include "fdelete.h"

/*
 * Documentation:
 * Description: fdelete() deletes 'bytes' bytes of data from the stream pointed to by fp. bytes will be deleted from the CURRENT FILE POSITION.
 * 		Please be aware that \n and \t are also bytes. Include them in 'bytes' if you want to delete them too.
 * 		File must be opened in read + write mode while passing file pointer to this function.
 * 		File position before calling the function and after the function returns will be the same.
 * Return Values: returns 0 on success and errno on failure. Kindly use perror("") to print error if non-0 return value returned.
 * Logic: Shift all bytes from (current_file_position + number_of_bytes_to_be_deleted) to (current_file_position) and in the end truncate the file
 */
int fdelete(FILE* fp, int bytes) {
	
	// to store each byte/char from file
	char byte;
	long readPos = ftell(fp) + bytes, writePos = ftell(fp), startingPos = writePos;
	// start reading from the position which comes after the bytes to be deleted
	fseek(fp, readPos, SEEK_SET);
	while (fread(&byte, sizeof(byte), 1, fp)) {
		// modify readPos as we have read right now
		readPos = ftell(fp);
		// set file position to writePos as we are going to write now
		fseek(fp, writePos, SEEK_SET);
		
		// if file doesn't have write permission
		if (fwrite(&byte, sizeof(byte), 1, fp) == 0) 
			return errno;
		// modify writePos as we have written right now
		writePos = ftell(fp);
		// set file position for reading
		fseek(fp, readPos, SEEK_SET);
	}

	// truncate file size to remove the unnecessary ending bytes
	ftruncate(fileno(fp), writePos);
	// reset file position to the same position that we got when function was called.
	fseek(fp, startingPos, SEEK_SET); 
	return 0;
}
