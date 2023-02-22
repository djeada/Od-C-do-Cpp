## Debugowanie programów przy użyciu GDB

GDB (ang. GNU Debugger) to narzędzie służące do debugowania programów napisanych w języku C, C++ i innych. Umożliwia ono m.in. kontrolowanie procesu wykonywania programu, zatrzymywanie go w określonych miejscach, analizę zmiennej i wiele innych.

## Instalacja

GDB jest narzędziem dostępnym na wiele systemów operacyjnych, w tym na systemy Unix oraz Windows. Aby zainstalować GDB, należy skorzystać z menadżera pakietów dla swojego systemu operacyjnego. 

Na przykład, w systemie Ubuntu, GDB można zainstalować przez wywołanie następującej komendy:

```bash
apt install gdb
```

## Przykłady użycia


Aby uruchomić program w trybie debugowania przy użyciu GDB, należy wywołać komendę gdb z argumentem będącym ścieżką do programu. Dodanie opcji -tui spowoduje uruchomienie GDB w trybie tekstowym z interfejsem użytkownika. Na przykład:

```bash
gdb -tui sciezka_do_programu
```

Breakpoint to punkt w programie, w którym GDB zatrzyma wykonywanie programu. Można ustawić breakpointy w dowolnym miejscu w kodzie, na przykład na konkretnej linii lub w konkretnej funkcji. Aby ustawić breakpoint, należy wywołać komendę break z argumentem będącym miejscem, w którym chcemy ustawić breakpoint. Na przykład:

```bash
break main            # ustawia breakpoint na początku funkcji main
break file.c:12       # ustawia breakpoint na linii 12 pliku file.c
break function        # ustawia breakpoint na początku funkcji function
```

Aby usunąć breakpoint, użyj:

```bash
delete linia_kodu
```  

Aby uruchomić program z GDB, należy wywołać komendę run. GDB zatrzyma się na pierwszym breakpointcie, jeśli takowy został ustawiony. Aby uruchomić program bez zatrzymywania się na breakpointach, należy dodać opcję `-q`. Na przykład:

```bash
run            # wykonuje program z zatrzymaniem na pierwszym breakpointcie
run -q         # wykonuje program bez zatrzymywania się na breakpointach
```  

Aby wyświetlić wartość zmiennej, należy wywołać komendę:

```bash
info locals
```

Aby zatrzymać się przy każdej modyfikacji konkretnej zmiennej, użyj:

```bash
watch nazwa_zmiennej
```

Możemy też poprosić o wylistowanie nazw funkcji, które były kolejno wywoływane aż program dotarł do aktualnej linii kodu:

```bash
bt
```

Jeśli zatrzymaliśmy się przy wywołaniu funkcji, to możemy przejść do jej definicji:

```bash
step
```

Aby przejść do następnej linii kodu, użyj:

```bash
next
```
Aby wznowić pracę zatrzymanego programu, użyj:

```bash
continue
```

Aby zamknąć GDB użyj:

```bash
quit
```
