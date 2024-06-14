## Wyjątki w programowaniu

W programowaniu, wyjątki służą jako mechanizm do sygnalizowania i obsługi nieoczekiwanych sytuacji, które mogą wystąpić podczas działania programu. Choć wyjątki często są używane w odpowiedzi na błędy, nie każdy wyjątek musi wynikać z błędu. Wyjątek może być również środkiem do poinformowania innych części kodu o pewnych warunkach lub sytuacjach, które wymagają specjalnej uwagi.

### Rodzaje błędów w programowaniu

1. **Błędy składniowe:** Są to błędy związane z nieprawidłowym użyciem składni języka. Takie błędy zwykle są łatwe do wykrycia, gdyż kompilatory i interpretery zgłaszają je przed uruchomieniem programu. Przykład: niezamknięty nawias lub brakujący średnik.

2. **Błędy logiczne:** Odnoszą się do sytuacji, gdy program działa inaczej, niż tego oczekiwano, mimo że nie zawiera błędów składniowych. Przykład: niewłaściwie zaprogramowana pętla `for` powodująca nieskończoną iterację.

3. **Błędy semantyczne:** Są to błędy, w których kod jest technicznie poprawny, ale nie wykonuje zamierzonej akcji. Przykład: zastosowanie niewłaściwej zmiennej w obliczeniach.

4. **Wyjątki:** Są najczęściej związane z błędami podczas wykonywania programu, nie z innymi rodzajami błędów.

### Rodzaje problemów, które mogą prowadzić do wyjątków

1. **Problemy z pamięcią:** Takie jak próba dostępu do niezainicjowanej pamięci, wycieki pamięci czy korzystanie z wskaźnika po jego dealokacji.

2. **Nieprzewidziane sytuacje wejścia/wyjścia:** Przykładem może być próba odczytu pliku, który nie istnieje, lub próba zapisu do pliku, gdy brakuje uprawnień.

3. **Nieprawidłowe operacje:** Jak dzielenie przez zero lub operacje na niekompatybilnych typach danych.

4. **Zewnętrzne warunki:** Takie jak utrata połączenia z bazą danych lub przerwanie połączenia sieciowego.

Wyjątki w programowaniu służą do sygnalizowania takich problemów. Pozwalają programistom na określenie, jak program powinien reagować w takich sytuacjach, umożliwiając bardziej kontrolowane i eleganckie zarządzanie niespodziewanymi warunkami.

### Mechanizm wyjątków

W momencie wystąpienia wyjątku w programie, normalny przepływ kontroli jest przerywany. Wyjątek, jeśli nie zostanie obsłużony w odpowiednim miejscu, może doprowadzić do zakończenia działania programu. Jednak dzięki mechanizmowi `try-catch` można przechwytywać i obsługiwać te wyjątki.

Poniżej znajduje się przykład działania wyjątków w C++:

```cpp
#include <iostream>
#include <stdexcept>

void funkcja() { throw std::runtime_error("Wystąpiła wyjątkowa sytuacja!"); }

int main() {
  try {
    funkcja();
  } catch (const std::runtime_error &e) {
    std::cout << "Przechwycono wyjątek: " << e.what() << std::endl;
  }

  std::cout << "Życie toczy się dalej" << std::endl;

  return 0;
}
```

W powyższym kodzie, funkcja `funkcja()` rzuca wyjątek typu `std::runtime_error`. Ten wyjątek jest następnie przechwytywany i obsługiwany w bloku `try-catch` w funkcji `main()`. Dzięki temu program nie kończy swojego działania po wystąpieniu wyjątku, co potwierdza komunikat "Życie toczy się dalej".

Programiści mają możliwość korzystania z wielu wbudowanych typów wyjątków w C++, ale także mogą definiować własne typy wyjątków, dostosowane do specyficznych potrzeb swojego kodu.

### Tworzenie własnych wyjątków

Definiowanie własnych typów wyjątków w C++ jest prostym procesem, który polega na dziedziczeniu po istniejących klasach wyjątków. Najczęściej używaną klasą bazową dla własnych wyjątków jest `std::exception`.

Oto jak można zdefiniować własny wyjątek:

```c++
class MojWyjatek : public std::exception
{
public:
    MojWyjatek(const std::string& komunikat) : komunikat_(komunikat) {}
    virtual const char* what() const throw() { return komunikat_.c_str(); }
private:
    std::string komunikat_;
};
```

W tym przykładzie, klasa `MojWyjatek` dziedziczy po `std::exception` i umożliwia przekazanie indywidualnego komunikatu, który jest następnie zwracany przez przesłoniętą funkcję `what()`. Tak zdefiniowany wyjątek może być rzucony i przechwycony w taki sam sposób, jak wbudowane typy wyjątków.

### Hierarchia wyjątków w C++

C++ posiada rozbudowaną hierarchię klas wyjątków, która ułatwia zarządzanie różnymi typami błędów. Na szczycie tej hierarchii znajduje się klasa `std::exception`, z której dziedziczą inne klasy wyjątków.

```cpp
#include <iostream>
#include <exception>

class BaseException : public std::exception {
public:
    virtual const char* what() const throw() {
        return "BaseException";
    }
};

class DerivedException : public BaseException {
public:
    virtual const char* what() const throw() {
        return "DerivedException";
    }
};

int main() {
    try {
        throw DerivedException();
    } catch (const BaseException& e) {
        std::cout << "Caught: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Caught: " << e.what() << std::endl;
    }

    return 0;
}
```

W powyższym przykładzie klasa `DerivedException` dziedziczy po `BaseException`, a `BaseException` dziedziczy po `std::exception`. Kiedy `DerivedException` jest rzucany, może być przechwycony przez catch blok obsługujący `BaseException`, ponieważ `DerivedException` jest typem bardziej szczegółowym, dziedziczącym po `BaseException`.

### Praktyczne zastosowania wyjątków

Wyjątki w programowaniu mają szerokie zastosowanie, począwszy od prostych przypadków obsługi błędów, aż po bardziej zaawansowane techniki, takie jak zapewnianie integralności danych czy zarządzanie zasobami.

1. **Obsługa błędów wejścia/wyjścia:** Wyjątki mogą być używane do obsługi błędów przy otwieraniu, odczycie lub zapisie plików.
   
2. **Operacje na zasobach:** Zarządzanie zasobami, takimi jak pamięć czy połączenia sieciowe, może być uproszczone przy użyciu wyjątków. W C++, konstrukcja RAII (Resource Acquisition Is Initialization) często współdziała z wyjątkami, aby zapewnić automatyczne zwalnianie zasobów.

3. **Walidacja danych:** Wyjątki mogą być używane do walidacji danych wejściowych w programie. Jeśli dane nie spełniają określonych kryteriów, rzucany jest wyjątek, który następnie może być obsłużony, aby podjąć odpowiednie działania naprawcze.

4. **Komunikacja między warstwami aplikacji:** Wyjątki mogą służyć do przekazywania informacji o błędach między różnymi warstwami aplikacji, na przykład między warstwą danych a warstwą logiki biznesowej.

### Zalety i wady używania wyjątków

Zalety:

1. **Czytelność kodu:** Wyjątki pozwalają na oddzielenie logiki obsługi błędów od logiki biznesowej, co prowadzi do bardziej przejrzystego i czytelnego kodu.
2. **Koncentracja na logice biznesowej:** Dzięki mechanizmom wyjątków, programiści mogą skupić się na logice biznesowej, nie musząc martwić się o obsługę błędów na każdym kroku.
3. **Lepsze zarządzanie błędami:** Wyjątki pozwalają na centralne zarządzanie błędami, co ułatwia ich obsługę i diagnozowanie.

Wady:

1. **Wydajność:** Rzucanie i przechwytywanie wyjątków jest operacją kosztowną pod względem wydajności. Nie należy ich używać do kontrolowania normalnego przepływu programu.

2. **Złożoność:** Niewłaściwe użycie wyjątków może prowadzić do skomplikowanego i trudnego do zrozumienia kodu. Utrzymanie dużej liczby wyjątków w różnych miejscach kodu może być wyzwaniem.

3. **Brak przewidywalności:** Wyjątki mogą być trudne do przewidzenia i testowania, szczególnie w dużych systemach, gdzie różne moduły mogą rzucać i przechwytywać wyjątki na różne sposoby.

4. **Ukrywanie błędów:** Nadmierne poleganie na wyjątkach może prowadzić do sytuacji, w której prawdziwe błędy są ukrywane, co utrudnia ich wykrycie i naprawę. Programiści mogą być skłonni do przechwytywania wszystkich wyjątków bez odpowiedniego przetwarzania, co prowadzi do niewłaściwej obsługi błędów.

5. **Koszt refaktoryzacji:** Wprowadzenie wyjątków do istniejącego kodu może wymagać znacznej refaktoryzacji, zwłaszcza jeśli kod wcześniej nie korzystał z tego mechanizmu. Może to być czasochłonne i skomplikowane.

### Najlepsze praktyki związane z wyjątkami

Aby skutecznie korzystać z wyjątków, warto stosować się do kilku najlepszych praktyk:

1. **Używaj wyjątków do wyjątkowych sytuacji:** Wyjątki powinny być używane tylko do sytuacji naprawdę wyjątkowych, które nie są częścią normalnego przepływu programu.

2. **Dokumentuj rzucane wyjątki:** Każda funkcja, która może rzucić wyjątek, powinna być odpowiednio udokumentowana, aby inni programiści wiedzieli, jakie wyjątki mogą wystąpić i jak je obsługiwać.

3. **Specyficzne przechwytywanie wyjątków:** Zawsze staraj się przechwytywać najbardziej specyficzny wyjątek możliwy, zamiast ogólnych wyjątków. Pozwala to na bardziej precyzyjną i kontrolowaną obsługę błędów.

4. **Zachowuj spójność:** Upewnij się, że używanie wyjątków w całym projekcie jest spójne. Stosowanie jednolitych konwencji dotyczących nazewnictwa i obsługi wyjątków pomoże utrzymać czytelność kodu.

5. **Czyszczenie zasobów:** Zawsze zwracaj uwagę na zasoby, które mogą zostać alokowane przed wystąpieniem wyjątku. Używaj konstrukcji RAII (Resource Acquisition Is Initialization) w C++ lub bloków `finally` w innych językach, aby upewnić się, że zasoby są zawsze poprawnie zwalniane.
