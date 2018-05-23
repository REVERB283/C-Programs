#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

int main(int argc, char const *argv[])
{
	if(argv[1]!=NULL)
	{
		char *demo, *temp;
		char *(arr)[1024];
		int i = 0;
		temp = strdup(argv[1]);
		while((demo = strsep(&temp, " "))!=NULL)
			arr[i++] = demo;
		if(strcmp(arr[0],"-v")!=0 && strcmp(arr[0],"-m")!=0 && strcmp(arr[0],"-p")!=0 && strcmp(arr[0],"-Z")!=0)
		{
			int a = mkdir(arr[0],S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
			if(a==-1)
				printf("mkdir: cannot create directory '%s': File exists\n", arr[0]);
		}
		else if(strcmp(arr[0],"-v")==0)
		{
			int a = mkdir(arr[1],S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
			if(a==-1)
				printf("mkdir: cannot create directory '%s': File exists\n", arr[1]);
			else
				printf("mkdir: created directory '%s'\n", arr[1]);
		}
		else if(strcmp(arr[0],"-p")==0)
			mkdir(arr[1],S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
		else
			printf("Invalid Option\n");
	}
	else
		printf("Missing Operand\n");
    exit(0);
}