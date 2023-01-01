
## C vs Cpp

* C został stworzony w 1970 roku, a C++ w 1985 roku. 
* C++ jest (prawie) nadzbiorem C. Kompilatory C++ prawie zawsze poradzą sobie z kodem napisanym w czystym C.

### Dyrektywy #include

W C załączając biblioteki standardowe dodajemy rozszerzenie '.h' po nazwie biblioteki. W C++ nie musimy dodawać rozszerzeń.

Przykłady załączania bibliotek w C:

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

Przykłady załączania bibliotek w C++:

    #include <iostream>
    #include <vector>
    #include <string>

Przykłady załączania bibliotek z C w C++:

    #include <cstdlib>
    #include <cstring>
    #include <cmath>

### Słowa kluczowe

Przykłady słów kluczowych wykorzystywanych zarówno w C i C++:

    auto
    break
    case
    char
    const
    continue
    default
    do
    double
    else
    enum
    extern
    float
    for
    goto
    if
    int
    long
    register
    return
    short
    signed
    sizeof
    static
    struct
    switch
    typedef
    union
    unsigned
    void
    volatile
    while

Przykłady słów kluczowych używanych jedynie w C++:

    static_cast
    dynamic_cast
    const_cast
    reinterpret_cast
    bool
    explicit
    namespace
    protected
    throw
    using
    catch
    false
    new
    public
    true
    virtual
    class
    friend
    operator
    template
    try
    delete
    inline
    private
    this
    typename

### Funkcjonalności dostępne jedynie w C++

* Przeciążanie funkcji
* Przekazywanie zmiennych przez referencję
* Inicjalizacja zmiennych przy użyciu nawiasów okrągłych
	int x(5);
* Domyślne wartości dla parametrów funkcji

### Dlaczego C?

* Minimalny język zawierający wszystko, czego potrzebujesz do napisania dowolnego programu, bez zbędnych abstrakcji.
* Mechanizmy języka są niezależne od siebie nawzajem.
* Mała standardowa biblioteka.
* Napotkane problemy możesz zawsze rozwiązać samemu, dokładnie tak jak chcesz. Nie ma potrzeby dolepiania tysięcy zewnętrznych bibliotek i frameworków.
* Jesteś kowalem własnego losu. Masz niemalże nieograniczoną kontrolę nad pamięcią wykorzystywaną przez twój program. Możesz zadecydować o tym, skąd pamięć jest brana i jak jest używana.
* Niedościgniona stabilność. Programy skompilowane w latach 80'tych działają do dziś.

### Dlaczego C++?

* C++ jest twoim przyjacielem, jeśli chcesz używać abstrakcji niedostępnych w C.
