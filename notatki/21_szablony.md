## Szablony

Szablony są jednym z kluczowych aspektów metaprogramowania w C++. Umożliwiają pisanie generycznych funkcji i klas, które adaptują się do różnych typów danych, bez konieczności duplikowania kodu. Zapewniają one wydajność kodu zapisanego ręcznie dla konkretnego typu, zachowując jednocześnie elastyczność.

### Szablon funkcji

Aby zdefiniować szablon funkcji, używamy słowa kluczowego `template`, po którym następuje lista parametrów szablonu w nawiasach trójkątnych `<>`.

Przykład generycznej funkcji `max2`:

```c++
template <typename T> 
T max2(T arg1, T arg2) {
    return arg1 > arg2 ? arg1 : arg2;
}
```

Podczas korzystania z funkcji szablonowej, kompilator tworzy odpowiednią specjalizację funkcji dla użytego typu:

```c++
max2<int>(10, 20);       // 20
max2<double>(16.2, 3.14); // 16.2
max2<char>('a', 'b');     // 'b'
```

### Szablon klasy

Szablon klasy pozwala na zdefiniowanie generycznej klasy, która może operować na różnych typach danych:

```c++
template <typename T> 
class Box {
    T content;

public:
    Box(T content) : content(content) {}
    T getContent() const { return content; }
};
```

Tworzenie instancji klasy szablonowej:

```c++
Box<int> intBox(42);
Box<std::string> stringBox("Hello");

Wielokrotne parametry szablonu

Możemy również definiować szablony z wieloma parametrami:

c++

template <typename T, int size> 
class Array {
    T elements[size];
    // ...
};
```

Użycie:

```c++
Array<int, 5> myArray;
```

### Specjalizacja szablonu

Czasami chcemy, aby dla konkretnego typu szablon działał w inny sposób. Możemy to osiągnąć, definiując specjalizację szablonu:

```c++
template <>
class Box<std::string> {
    std::string content;
    
public:
    Box(std::string content) : content(content) {}
    std::string getContent() const { return "Content: " + content; }
};
```

Teraz, gdy użyjemy `Box<std::string>`, metoda `getContent()` zwróci nieco inną wartość niż w ogólnym przypadku.

### Typy domyślne w szablonach

Możemy określić typy domyślne dla parametrów szablonu:

```c++
template <typename T = int, int size = 10> 
class Array {
    T elements[size];
    // ...
};
```

Szablony w C++ zapewniają potężne narzędzia do tworzenia elastycznego, generycznego kodu bez poświęcania wydajności. Umożliwiają tworzenie bardziej uniwersalnych i ponownie używalnych struktur kodu, jednocześnie zapewniając możliwość optymalizacji pod kątem konkretnych typów.
