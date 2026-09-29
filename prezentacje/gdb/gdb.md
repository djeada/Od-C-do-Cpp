# Debugowanie programów z GDB

GDB (GNU Debugger) pozwala zatrzymywać program, wykonywać go krokowo, sprawdzać wartości zmiennych i analizować stos wywołań. Najwięcej zyskujemy, gdy program został skompilowany z informacjami debugowania.

## Cele

Po tej prezentacji powinieneś umieć:

- skompilować program do debugowania,
- ustawić breakpoint i uruchomić program pod kontrolą GDB,
- rozróżnić `step`, `next` i `continue`,
- sprawdzić zmienne oraz stos wywołań,
- użyć watchpointa do znalezienia miejsca zmiany wartości.

## Kompilacja do debugowania

Dla programu w C:

```bash
gcc -g -O0 -Wall -Wextra main.c -o program
```

Dla C++:

```bash
g++ -g -O0 -Wall -Wextra main.cpp -o program
```

- `-g` dodaje informacje debugowania.
- `-O0` wyłącza optymalizacje, dzięki czemu wykonywanie krokowe jest łatwiejsze do śledzenia.
- Program zoptymalizowany również można debugować, ale część zmiennych lub linii może nie odpowiadać bezpośrednio kodowi źródłowemu.

## Uruchomienie GDB

```bash
gdb ./program
```

Tryb tekstowego interfejsu użytkownika:

```bash
gdb -tui ./program
```

Najprostszy przebieg sesji:

```text
(gdb) break main
(gdb) run
(gdb) next
(gdb) print zmienna
(gdb) continue
(gdb) quit
```

## Breakpointy

Breakpoint zatrzymuje program przed wykonaniem wskazanej linii lub funkcji.

```text
(gdb) break main
(gdb) break plik.c:42
(gdb) break funkcja
```

Breakpoint warunkowy:

```text
(gdb) break plik.c:42 if licznik == 10
```

Przydatne polecenia:

```text
(gdb) info breakpoints
(gdb) disable 2
(gdb) enable 2
(gdb) delete 2
```

## Sterowanie wykonaniem

| Polecenie | Znaczenie |
| --- | --- |
| `run` | uruchom lub uruchom ponownie program |
| `continue` / `c` | wykonuj do następnego zatrzymania |
| `next` / `n` | wykonaj następną linię bez wchodzenia do funkcji |
| `step` / `s` | wykonaj następną linię, wchodząc do wywołanej funkcji |
| `finish` | wykonuj do powrotu z bieżącej funkcji |
| `until` | wykonuj do późniejszej linii w bieżącej ramce |

Argumenty programu można podać po `run`:

```text
(gdb) run plik.txt --verbose
```

## Zmienne i wyrażenia

```text
(gdb) print x
(gdb) print tablica[3]
(gdb) print *ptr
(gdb) info locals
(gdb) info args
```

Stałe śledzenie wyrażenia:

```text
(gdb) display licznik
(gdb) undisplay 1
```

## Watchpointy

Watchpoint zatrzymuje program, gdy zmieni się obserwowana wartość.

```text
(gdb) watch saldo
(gdb) continue
```

To szczególnie przydatne, gdy wiadomo **co** zostało nadpisane, ale nie wiadomo **gdzie**.

Dostępne są też:

```text
(gdb) rwatch zmienna   # zatrzymanie przy odczycie
(gdb) awatch zmienna   # zatrzymanie przy odczycie lub zapisie
```

Obsługa zależy od możliwości sprzętowych i systemu.

## Stos wywołań

Gdy program zatrzyma się w błędnym miejscu:

```text
(gdb) backtrace
(gdb) frame 2
(gdb) info locals
```

Skrót dla `backtrace` to `bt`.

Przykładowy schemat analizy awarii:

1. Uruchom program poleceniem `run`.
2. Po zatrzymaniu wykonaj `bt`.
3. Przejdź do interesującej ramki poleceniem `frame N`.
4. Sprawdź argumenty i zmienne lokalne.
5. Ustaw breakpoint wcześniej i odtwórz problem.

## Kod źródłowy i pamięć

```text
(gdb) list
(gdb) list funkcja
(gdb) x/16xb ptr
(gdb) x/8gx ptr
```

Polecenie `x` pozwala oglądać pamięć w różnych formatach. Jest przydatne m.in. przy wskaźnikach, buforach i analizie uszkodzeń pamięci.

## Najczęstsze pułapki

- Bez `-g` debugowanie kodu źródłowego jest znacznie mniej wygodne.
- Optymalizacje mogą zmienić kolejność instrukcji lub usunąć zmienne.
- `next` nie wchodzi do funkcji, a `step` wchodzi.
- Watchpoint obserwuje zmianę wartości, a breakpoint miejsce wykonania.
- Sam komunikat o segmentation fault zwykle nie wystarcza — najpierw sprawdź `bt`.

## Podsumowanie

Minimalny zestaw poleceń, który warto zapamiętać:

```text
break
run
next
step
continue
print
watch
backtrace
frame
quit
```

GDB najlepiej traktować jako narzędzie do stawiania hipotez: zatrzymaj program przed podejrzanym miejscem, sprawdź stan i zawężaj obszar, w którym powstaje błąd.
