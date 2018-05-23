#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>

#define max 1024

sem_t w, r;
int buf;
int nr = 0;
int nre = 0;
int nwr = 0;
int front = -1;
int rear = -1;
int q[max];

// method to produce at the end of the queue (ENQUEUE)
int insert(int num)
{
	if(rear==max-1)
	{
		return -1;
	}
	if(front==-1)
	{
		front = 0;
	}
	rear++;
	q[rear] = num;
	return 0;
}

// method to consume from the starting of the queue (DEQUEUE)
int delete()
{
	int num;
	if(front==-1 || front==rear+1)
	{
		return -1;
	}
	num = q[front];
	front++;
	return num;
}

// method to ask for number of readers & writers involved
void number()
{
	printf("\nEnter the number of Readers & Writers:\n");
	scanf("%d", &nre);
	scanf("%d", &nwr);
}

// method to initialise the queue
void initwrite()
{
	printf("Write Something:\n");
	scanf("%d", &buf);
	insert(buf);
}

void startread()
{
	sem_wait(&r);
	nr++;
	if(nr==1)
	{
		sem_wait(&w);
	}
	sem_post(&r);
}

void endread()
{
	sem_wait(&r);
	nr--;
	if(nr==0)
	{
		sem_post(&w);
	}
	sem_post(&r);
}

void startwrite()
{
	sem_wait(&w);
}

void endwrite()
{
	sem_post(&w);
}

// 	thread method for readers
void *reader(void *arg)
{
	int temp = (int) arg;
	startread();
	// critical section
	int a = delete();
	if(a==-1)
	{
		// QUEUE is empty (ERROR_2)
		printf("Reader %d is reading content: ---\n", temp);
	}
	else
	{
		printf("Reader %d is reading content: %d\n", temp, a);
	}
	endread();
}

// 	thread method for writers
void *writer(void *arg)
{
	int temp = (int) arg;
	startwrite();
	// critical section
	printf("Writer %d is writing content: ", temp);
	scanf("%d", &buf);
	int a = insert(buf);
	if(a==-1)
	{
		// QUEUE is full (ERROR_1)
		printf("---Operation was not successful---\n");
	}
	else
	{
		printf("---Operation was successful---\n");
	}
	endwrite();
}



int main()
{	
	int id, numthr;
	number();
	initwrite();
	sem_init(&w, 0, 1);
	sem_init(&r, 0, 1);
	pthread_t rt[100], wt[100];
	for(int i=0; i<nre; i++)
	{
		pthread_create(&rt[i], NULL, reader, (void *)i);
	}
	for(int i=0; i<nwr; i++)
	{
		pthread_create(&wt[i], NULL, writer, (void *)i);
	}
	for(int i=0; i<nwr; i++)
	{
		pthread_join(wt[i], NULL);
	}
	for(int i=0; i<nre; i++)
	{
		pthread_join(rt[i], NULL);
	}
	sem_destroy(&r);
	sem_destroy(&w);
	return 0;
}
