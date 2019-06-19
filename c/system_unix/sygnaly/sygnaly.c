#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void uchwyc_dzielenie_przez_zero(int num_sygnalu) {

	if (num_sygnalu == SIGFPE) {
		printf("Dzielenie przez zero!\n");
	} else {
		printf("Nieoczekiwany sygnal!\n");
		exit(0);
	}
}

void uchwyc_alarm(int num_sygnalu) {
	
	if (num_sygnalu == SIGALRM) {
		printf("Alarm zostal ugaszony!\n");
	} else {
		printf("Nieoczekiwany sygnal!\n");
		exit(0);
	}
}

int main() {  
	
	//printf("Wysylam sygnal SIGSTOP!\n");
	//raise(SIGSTOP);
	// znajdz pid sygnalu w terminalu: ps -f | grep sygnal
	// zatrzymaj proces: kill -STOP pid 
	//printf("Sygnal zostal zabity!\n");

	// sprobuj schwytac sygnal SIGALRM
	void (*rezultat_proby_schwytania_sygnalu)(int);
	rezultat_proby_schwytania_sygnalu = signal(SIGALRM, uchwyc_alarm);

	if (rezultat_proby_schwytania_sygnalu == SIG_ERR) {
		printf("Wystapil nieznany blad!\n");
		exit(0);
	}

	// wyslij sygnal SIGALRM po 3 sekundach
	// jesli sygnal nie zostanie schwytany, to program zostanie zakonczony
	alarm(3);
	for(int i = 0; i < 6; i++){
		printf("%d\n", i+1);
		sleep(1);
	} 

	rezultat_proby_schwytania_sygnalu = signal(SIGFPE, uchwyc_dzielenie_przez_zero);
	
	if (rezultat_proby_schwytania_sygnalu == SIG_ERR) {
		printf("Wystapil nieznany blad!\n");
		exit(0);
	}

  float a = 1.0;
  float b = 0.0;
	float ulamek = a/b;
	
	printf("Wynik dzieielenia przez zero: %f\n", ulamek);
	
    return 0;
}
