## Debugowanie programów przy użyciu GDB

GDB (GNU Debugger) to wszechstronne narzędzie służące do debugowania programów napisanych głównie w języku C i C++, choć obsługuje również wiele innych języków. Z jego pomocą można kontrolować przebieg wykonywania programu, zatrzymywać go w kluczowych momentach (tzw. breakpointy), analizować wartości zmiennych, a także śledzić wywołania funkcji.

## Funkcje i możliwości GDB

1. Ustawianie breakpointów w określonych miejscach w kodzie.
2. Krokowe wykonywanie programu.
3. Analiza wartości zmiennych w trakcie wykonywania programu.
4. Śledzenie stosu wywołań funkcji.
5. Modyfikowanie wartości zmiennych w trakcie debugowania.
6. Analiza kodu binarnego i asemblera.

## Instalacja GDB

GDB jest narzędziem dostępnym na wiele platform i systemów operacyjnych, w tym na większość dystrybucji systemów Unix (jak Linux) oraz na Windows poprzez narzędzia takie jak Cygwin.

Aby zainstalować GDB w systemie Linux, można skorzystać z odpowiedniego menadżera pakietów. Poniżej znajdują się przykłady dla kilku popularnych dystrybucji:

### Ubuntu (i pochodne):

```bash
sudo apt update
sudo apt install gdb
```

### Fedora:

```bash
sudo dnf install gdb
```

### Arch Linux:

```bash
sudo pacman -S gdb
```

## Przykłady użycia GDB

GDB oferuje mnóstwo funkcji do efektywnego debugowania aplikacji. Oto kilka podstawowych przykładów użycia tego narzędzia:

### Uruchomienie programu w trybie debugowania

Aby rozpocząć debugowanie programu, uruchom GDB z nazwą programu jako argument. Jeżeli chcesz korzystać z trybu tekstowego z bardziej rozbudowanym interfejsem użytkownika, dodaj opcję `-tui`.

```bash
gdb -tui sciezka_do_programu
```

### Ustawianie breakpointów

Breakpoint to miejsce w kodzie, w którym GDB zatrzyma wykonanie programu. Możesz ustawić breakpointy na konkretnej linii kodu, w funkcji lub nawet przy określonych warunkach.

```bash
break main           # ustawia breakpoint na początku funkcji main
break file.c:12      # ustawia breakpoint na linii 12 pliku file.c
break function       # ustawia breakpoint na początku funkcji function
```

Jeśli chcesz ustawić breakpoint, który zostanie aktywowany tylko wtedy, gdy pewien warunek zostanie spełniony, możesz użyć:

```bash
break file.c:12 if variable == 10  # zatrzymuje się na linii 12 tylko, gdy variable ma wartość 10
```

### Zarządzanie breakpointami

Aby usunąć breakpoint, można użyć komendy delete z numerem breakpointu lub bez niego (aby usunąć wszystkie breakpointy).

```bash
delete 1            # usuwa breakpoint o numerze 1
delete               # usuwa wszystkie breakpointy
```

### Wykonywanie programu

Po ustawieniu breakpointów możesz uruchomić program przy użyciu komendy run. Jeśli program ma argumenty, podaj je po run.

```bash
run arg1 arg2       # uruchamia program z argumentami arg1 i arg2
```

Jeśli program został już wcześniej uruchomiony i chcesz go ponownie uruchomić, po prostu użyj komendy run ponownie.

Warto dodać, że opcja -q nie jest typową opcją dla komendy run w GDB. Zamiast tego, jest to opcja dla samego GDB, która powoduje, że GDB działa w trybie "cichym", z mniejszą ilością informacji wyjściowych. Jeżeli chcesz uruchomić program bez zatrzymywania się na breakpointach, możesz użyć komendy continue lub skrótu c.

```bash
continue          # kontynuuje wykonanie programu do następnego breakpointu lub do jego zakończenia
```

###  Wyświetlanie wartości zmiennych

Aby przejrzeć wartości zmiennych lokalnych aktualnej funkcji, użyj:

```bash
info locals
```

Jeśli chcesz wyświetlić wartość konkretnej zmiennej, możesz użyć poniższej komendy:

```bash
print nazwa_zmiennej
```

### Śledzenie modyfikacji zmiennej

Jeśli chcesz, by GDB zatrzymał wykonanie programu za każdym razem, gdy dana zmienna jest modyfikowana, użyj:

```bash
watch nazwa_zmiennej
```

### Wyświetlanie stosu wywołań funkcji

Aby zobaczyć listę funkcji, które zostały wywołane aż do aktualnej linii kodu, użyj:

```bash
bt  # skrót od 'backtrace'
```

### Sterowanie wykonywaniem programu

1. Przejście do definicji funkcji lub wejście w nią:
Jeśli zatrzymałeś się przed wywołaniem funkcji i chcesz przejść do jej definicji (lub "wejść" w nią), użyj:

```bash
step
```

2. Przejście do następnej linii kodu (bez wchodzenia do funkcji):
Jeśli nie chcesz wchodzić do definicji funkcji i wolisz przejść do następnej linii kodu w bieżącej funkcji, użyj:

```bash
next
```

### Zakończenie pracy z GDB

Gdy skończysz debugowanie i chcesz zakończyć pracę z GDB, wpisz:

```bash
quit
```
