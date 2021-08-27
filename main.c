#include <stdio.h>
#include <errno.h>
#include "fdelete.h"

int main(int argc, char** argv) {

	if (argc == 1) {
		printf("usage: ./a.out <filename>\n");
		return EINVAL;
	}

	FILE* fp = fopen(argv[1], "r+");
	if (!fp) {
		perror("");
		return errno;
	}
	
	char line[256];
	
	for (int i = 0; i < 2; i++) // ignoring first 2 chars and setting file position to 3rd byte/char
		fgetc(fp);

	int bytes;
	printf("Enter number of bytes to be deleted: ");
	scanf("%d", &bytes);
	
	int ret = fdelete(fp, bytes);
	if (ret != 0) {
		perror("");
		return ret;
	}
	fscanf(fp, "%[^\n]%*c", line);
	printf("%s\n", line);

	return 0;
}
