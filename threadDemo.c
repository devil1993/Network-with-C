#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void *thread_function(void *arg);

char message[] = "Hello world";

int main(int argc, char const *argv[])
{
	int res;
	pthread_t a_thread;
	void *thread_result;

	res = pthread_create(&a_thread,NULL,thread_function,(void*)message);
	if (res)
	{
		perror("thread creation failed");
		exit(EXIT_FAILURE);
	}
	printf("Waiting thread to finish\n");
	res = pthread_join(a_thread,&thread_result);
	if (res)
	{
		perror("Thread join failed");
		exit(EXIT_FAILURE);
	}
	printf("Thread joined, it returned: %s\n", (char*)thread_result);
	printf("Message is now: %s\n", message);
	exit(EXIT_SUCCESS);
	return 0;
}

void *thread_function(void *arg){
	printf("Thread running, argument is :%s\n", (char*)arg);
	sleep(2);
	strcpy(message,"Bye");
	pthread_exit("Thank you for cpu time");
}