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

```c++
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
