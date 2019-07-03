#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

//when thread is created, one of its attributes defines whter it is joinable or detached
//by default if you passed NULL as the second argument the thread will be joinable state
//only joinable threads can be joined

//if threads will never join you can detach
//save some system resources

void *threadFn(void* arg){
	pthread_detach(pthread_self());
	sleep(1);
	printf("ThreadFn\n");
	pthread_exit(NULL);
}

int main(int argc, char *argv[]) {  
	
	pthread_t tid;
	int ret = pthread_create(&tid, NULL, threadFn, NULL);
	if(ret != 0){
		perror("Thread Creation Error\n");
		exit(1);
	}

	printf("After thread created in Main\n");	
	pthread_exit(NULL);
	
    return 0;
}


