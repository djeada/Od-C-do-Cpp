#include <unistd.h>
#include <sys/wait.h>

//Przyklad szeregowego vs rowneleglego programu

//int forkNexec(StrVec argList);

void szeregowo(){
	     char *const parmList[] = {"/bin/sleep", "5", NULL};

	
	int pid1 = fork();
	execv("/bin/sleep", parmList);
	waitpid(pid1, NULL, 0);

	int pid2 = fork();
	execv("/bin/sleep", parmList);
	waitpid(pid2, NULL, 0);
}

void rownolegle(){
	 char *const parmList[] = {"sleep", "5", NULL};
	 
	int pid1 = fork();
	int pid2 = fork();
	
	execv("/bin/sleep", parmList);
	execv("/bin/sleep", parmList);
	
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}

int main() {  
	rownolegle();

    return 0;
}
