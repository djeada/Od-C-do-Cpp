#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {  
	printf("Rodzic przed forkiem \n");
	int zwroconaWartosc = fork();

	printf("wartosc zwrocona przez fork: %d \n", zwroconaWartosc);
	
	if(zwroconaWartosc == 0){
		printf("Dziecko jest wykonywane. \n");
		sleep(5);
		printf("Dziecko umiera. \n");
	}
	else {
		printf("Rodzic %d oczekuje na dziecko \n", zwroconaWartosc);
		int exitCode = 0; //what main of the kid is returnng

		waitpid(zwroconaWartosc, &exitCode, 0);
		printf("Rodzic umiera. \n");
	}

    return 0;
}
