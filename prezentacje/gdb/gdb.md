## Instalacja

W systemach operatych o dystrybucję Debian:
  
    apt install gdb
    
W systemach opeartych o dystrybucję Arch:

    pacman -S gdb


## Przykłady użycia


Aby uruchomić program przy użyciu GDB, użyj:

    gdb -tui sciezka_do_programu

Możemy teraz ustawić tak zwane *breakpoints*, czyli linie kodu przy wykonywaniu których GDB się zatrzyma dając nam możliwość wglądu w stan zmiennych:

    break linia_kodu
    break nazwa_pliku:linia_kodu
    break nazwa_funkcji

Aby usunąć *breakpoint*, użyj:

    delete linia_kodu
    
Aby zatrzymać się przy każdej modyfikacji konkretnej zmiennej, użyj:

    watch nazwa_zmiennej

Aby uruchomić program, którego ścieżkę podaliśmy jako argument do GDB, użyj:

    run

Po zatrzymaniu się przy *breakpoint* możemy podjerzeć stan zmiennych lokalnych:

    info locals

Możemy też poprosić o wylistowanie nazw funkcji, które były kolejno wywoływane aż program dotarł do aktualnej linii kodu:

    bt
    
Jeśli zatrzymaliśmy się przy wywołaniu funkcji, to możemy przejść do jej definicji:

    step

Aby przejść do następnej linii kodu, użyj:

    next

Aby wznowić pracę zatrzymanego programu, użyj:
    
    continue

Aby zamknąć GDB użyj:

    quit
