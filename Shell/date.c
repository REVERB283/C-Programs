#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[])
{
	time_t t = time(NULL);
	struct tm *tm = localtime(&t);
	if(argv[1]==NULL)
	{
		char date[1024];
		strftime(date,1024,"%a %b %d %T %Z %Y",tm);
		puts(date);
	}
	else if(strcmp(argv[1],"-R")==0)
	{
		char date[1024];
		strftime(date,1024,"%a, %d %b %Y %T %z",tm);
		puts(date);
	}
	else if(strcmp(argv[1],"-I")==0)
	{
		char date[1024];
		strftime(date,1024,"%F",tm);
		puts(date);
	}
	else
		printf("Invalid Command\n");
	exit(0);
}