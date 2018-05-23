#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
	char *demo, *temp;
	char *(arr)[1024];
	int i = 0;
	temp = strdup(argv[1]);
	while((demo = strsep(&temp, " "))!=NULL)
		arr[i++] = demo;
	if(argv[1]!=NULL)
	{
		if(strchr(arr[0],'-')==NULL)
		{
			int err = unlink(arr[0]);
			if(err==-1)
				printf("File doesn't exist or It's a Directory\n");
		}
		else if(strcmp(arr[0],"-v")==0)
		{
			int err = unlink(arr[1]);
			if(err==-1)
				printf("File doesn't exist or It's a Directory\n");
			else
				printf("removed: '%s'\n", arr[1]);
		}
		else if(strcmp(arr[0],"-i")==0)
		{
			printf("rm: remove regular file '%s'?", arr[1]);
			char input;
			scanf("%c",&input);
			if(input=='y' || input=='Y')
			{
				int err = unlink(arr[1]);
				if(err==-1)
					printf("File doesn't exist or It's a Directory\n");
			}
		}
		else
			printf("Invalid Command\n");
	}
	else
		printf("Missing Operand\n");
	exit(0);
}