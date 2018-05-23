#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[])
{
	FILE *readfile;
	char readline[1024];
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
			readfile = fopen(arr[0],"r");
			if(readfile==NULL)
			{
				printf("File Doesn't Exist\n");
				exit(0);
			}
			while(fgets(readline,1024,readfile))
				printf("%s",readline);
			fclose(readfile);
		}
		else if(strcmp(arr[0],"-b")==0)
		{
			readfile = fopen(arr[1],"r");
			if(readfile==NULL)
			{
				printf("File Doesn't Exist\n");
				exit(0);
			}
			int line = 1;
			while(fgets(readline,1024,readfile))
			{
				if(strcmp(readline,"\n")!=0)
				{
					printf(" %d %s",line,readline);
					line++;
				}
				else
					printf(" %s",readline);
			}
			fclose(readfile);
		}
		else if(strcmp(arr[0],"-n")==0)
		{
			readfile = fopen(arr[1],"r");
			if(readfile==NULL)
			{
				printf("File Doesn't Exist\n");
				exit(0);
			}
			int line = 1;
			while(fgets(readline,1024,readfile))
			{
				printf(" %d %s",line,readline);
				line++;
			}
			fclose(readfile);
		}
		else
			printf("Invalid Option\n");
	}
	else
		printf("Missing Operands\n");
	exit(0);
}