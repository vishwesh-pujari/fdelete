/*
 * TODO - Future Scope - Delete Multiple Lines => Delete from byte number x to byte number y => write fmodify()
 * The OS doesn't give us an option of deleting a specific line/part from a file
 * This code attempts to write a function for this purpose
 * If this code is a success, then try to Post this answer on Stack overflow for the question of can I delete from a text file
 * man 2 truncate
 */

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>

int fdelete(char* filename, int delNum); // delNum indicates line number to be deleted

int main(int argc, char** argv) {

	if (argc == 1) {
		printf("usage: ./a.out <filename>\n");
		return EINVAL;
	}

	int delNum;
	printf("Enter line to be deleted: ");
	scanf("%d", &delNum);
	
	int ret = fdelete(argv[1], delNum);
	if (ret != 0) {
		perror("");
		return ret;
	}

	return 0;
}


/*
 * returns errno in case of error
 * returns 0 for success
 */
int fdelete(char* filename, int delNum) { // TODO - NEXT CHALLENGE IS TO DELETE MULTIPLE LINES, BEWARE OF CONSECUTIVE LINES
	FILE* fp = fopen(filename, "r+"); // open the file
	if (!fp)
		return errno;

	char line[256]; // to hold one line of file at a time
	int lineNum = 1, delete = 0, deleteFoundRightNow = 0;
	long filePosRead = ftell(fp), filePosWrite = ftell(fp); // filePosRead will hold the file position from which next read has to be performed and filePosWrite holds the file position from where next write has to be performed

	while (fscanf(fp, "%[^\n]%*c", line) != EOF) {
		//printf("line = %s\n", line);
		filePosRead = ftell(fp); // modify filePosRead bcoz we have read just now
		if (lineNum == delNum) { // if line to be deleted found
			delete = 1;
			deleteFoundRightNow = 1;
		}
		if (delete) {
			if (deleteFoundRightNow) { // read the next line only if delete is found right now. This is becoz we want to replace the line to be deleted by the next line
				if (fscanf(fp, "%[^\n]%*c", line) == EOF)
					break;
				lineNum++; // IMP - there is a problem that consecutive lines cannot be deleted
				deleteFoundRightNow = 0;
				filePosRead = ftell(fp); // store the file position in filePosRead bcoz we have read one more line right now
			}
			
			// if delete is not found right now, then we just simply write the line read to filePosWrite. We don't have to read next line in this case

			fseek(fp, filePosWrite, SEEK_SET); // set file position for writing
			fprintf(fp, "%s\n", line);
			filePosWrite = ftell(fp); // modify filePosWrite bcoz we have written right now
		} else {
			filePosWrite = ftell(fp); // update the filePosWrite to go to next line
		}
		lineNum++;
		fseek(fp, filePosRead, SEEK_SET); // set file position to filePosRead becoz we are going to read from file
	}
	
	//printf("delete = %d\nline = %s\n", delete, line);
	/*if (delete) { // after EOF, the last line will be unprocessed.
		//filePosRead = ftell(fp);
		fseek(fp, filePosWrite, SEEK_SET);
		fprintf(fp, "%s\n", line);
		//filePosWrite = ftell(fp);
	}*/


	fclose(fp);
	
	truncate(filename, filePosWrite); // truncate the file size to filePosWrite

	return 0;
}
