#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
	while(1)
	{
		FILE *appendfile;
		char in[1024], out[1024];
		char *a, *b;
		printf(">>>	");
		gets(in);
		appendfile = fopen("/home/iiitd/src/history.txt","a");
		fprintf(appendfile, "%s\n", in);
		fclose(appendfile);
		a = strdup(in);
		b = strsep(&a, " ");
		if(strcmp(b,"\n")==0)
			continue;
		if(strcmp(b,"exit")==0)
		{
			if(a==NULL)
				exit(0);
			else
				printf("Invalid Option\n");
			continue;
		}
		else if(strcmp(b,"pwd")==0)
		{
			if(a==NULL)
			{
				getcwd(out,1024);
				printf(" %s\n", out);
			}
			else
				printf("Invalid Option\n");
			continue;
		}
		else if(strcmp(b,"cd")==0)
		{
			if(a!=NULL)
			{
				int err = chdir(a);
				if(err==-1)
					printf("No such file or directory \n");
			}
			else
				chdir("/home/");
			continue;
		}
		else if(strcmp(b,"history")==0)
		{
			if(a==NULL)
			{
				FILE *readfile;
				char readline[1024];
				int line = 0;
				readfile = fopen("/home/iiitd/src/history.txt","r");
				while(fgets(readline,1024,readfile))
				{
					printf(" %i %s",line,readline);
					line++;
				}
				fclose(readfile);
				continue;
			}
			if(strcmp(a,"-c")==0)
			{
				FILE *clearfile;
				clearfile = fopen("/home/iiitd/src/history.txt","w");
				fclose(clearfile);
			}
			else if(strcmp(a,"-w")==0)
				continue;
			else
				printf(" Invalid Option\n");
			continue;
		}
		else if(strcmp(b,"echo")==0)
		{
			char *demo, *temp;
			char *(arr)[1024];
			int i = 0;
			temp = strdup(a);
			while((demo = strsep(&temp, " "))!=NULL)
				arr[i++] = demo;
			if(strchr(arr[0],'-')==NULL)
			{
				for(int j=0; j<i; j++)
				{
					if(strcmp(arr[j],"")!=0 && strcmp(arr[j],"\"")!=0 && strcmp(arr[j],"\'")!=0)
					{
						char *s,*str;
						str = strdup(arr[j]);
						while((s = strsep(&str,"\"")))
						{
							if(strcmp(s,"")!=0)
								printf("%s ", s);
						}
					}
				}
				printf("\n");
			}
			else if(strcmp(arr[0],"-n")==0)
			{
				for(int j=1; j<i; j++)
				{
					if(strcmp(arr[j],"")!=0 && strcmp(arr[j],"\"")!=0 && strcmp(arr[j],"\'")!=0)
					{
						char *s,*str;
						str = strdup(arr[j]);
						while((s = strsep(&str,"\"")))
						{
							if(strcmp(s,"")!=0)
								printf("%s ", s);
						}
					}
				}
			}
			else
				printf("Invalid Option\n");
			continue;
		}
		pid_t pid;
		pid = fork();
		if(pid<0)
			return 1;
		else if(pid==0)
		{
			if(strcmp(b,"ls")==0)
				execl("/home/iiitd/src/ls",b,a,NULL);
			else if(strcmp(b,"cat")==0)
				execl("/home/iiitd/src/cat",b,a,NULL);
			else if(strcmp(b,"rm")==0)
				execl("/home/iiitd/src/rm",b,a,NULL);
			else if(strcmp(b,"mkdir")==0)
				execl("/home/iiitd/src/mkdir",b,a,NULL);
			else if(strcmp(b,"date")==0)
				execl("/home/iiitd/src/date",b,a,NULL);
			else
			{
				printf("Invalid Commmand\n");
				continue;
			}
		}
		else
			wait(NULL);
	}
	return 0;
}