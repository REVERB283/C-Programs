#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>

static int compare (const void *str1, const void *str2)
{
	return strcmp(* (char * const *)str1, * (char * const *)str2);
}

int main (int argc, char *argv[])
{
	DIR *directory;

	struct dirent *dirptr;
	char *(arr)[1024];
	int i = 0;
	directory = opendir(".");
	if(directory==NULL)
	{
		printf("Invalid Option\n");
		exit(1);
	}
	while ((dirptr = readdir(directory)) != NULL)
		arr[i++] = dirptr->d_name;
	qsort(arr,i,sizeof(char *),compare);
	if(argv[1]==NULL)
	{
		for(int j=0;j<i;j++)
		{
			if(strchr(arr[j],'.')!=NULL)
			{
				if(strcmp(arr[j],strchr(arr[j],'.')))
					printf("%s   ", arr[j]);
			}
			else
			{
				if(strcmp(arr[j],".")!=0 && strcmp(arr[j],"..")!=0) 
					printf("%s   ", arr[j]);
			}
		}
		printf("\n");
	}
	else if(strcmp(argv[1],"-a")==0)
	{
		for(int j=0;j<i;j++)
		{
			printf(" %s ", arr[j]);
		}
		printf("\n");
	}
	else if(strcmp(argv[1],"-d")==0)
		printf(".\n");
	else
		printf("Invalid Command\n");
	closedir(directory);
	exit(0);
}