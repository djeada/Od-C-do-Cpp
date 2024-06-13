## Preprocesor

Preprocesor to narzędzie, które działa na kodzie źródłowym języka programowania przed właściwym procesem kompilacji. Jest on integralną częścią kompilatora i przekształca kod źródłowy według określonych dyrektyw preprocesora, które rozpoczynają się od znaku `#`. Dyrektywy preprocesora mogą być rozmieszczone w dowolnym miejscu kodu źródłowego, jednak dla większej przejrzystości zazwyczaj umieszcza się je na początku pliku.

### Funkcje preprocesora

Dyrektywy preprocesora pełnią różne funkcje, w tym:

### 1. Załączanie bibliotek

Dzięki dyrektywie `#include`, możemy załączyć zawartość innych plików do naszego kodu, co pozwala na modularność i ponowne wykorzystanie kodu. Są dwa główne rodzaje załączania plików:

- **Załączanie bibliotek standardowych**:
  ```c++
  #include <iostream>
  ```
  Ta dyrektywa mówi preprocesorowi, aby dołączył plik nagłówkowy `iostream` z bibliotek standardowych.

- **Załączanie plików lokalnych**:
  ```c++
  #include "moj_plik.h"
  ```
  Ta dyrektywa mówi preprocesorowi, aby dołączył plik `moj_plik.h` znajdujący się w bieżącym katalogu lub w określonej ścieżce.

### 2. Definiowanie stałych i makr

Dyrektywa `#define` umożliwia definiowanie stałych i makr, które mogą upraszczać kod i zwiększać jego czytelność oraz elastyczność.

- **Definiowanie stałych**:
  ```c++
  #define PI 3.141592653589793
  ```
  Tutaj `PI` jest definiowane jako stała o wartości 3.141592653589793.

- **Definiowanie makr z parametrami**:
  ```c++
  #define MAX(x, y) ((x) > (y) ? (x) : (y))
  ```
  To makro działa jak funkcja, porównując dwie wartości i zwracając większą z nich.

### 3. Warunkowa kompilacja

Dyrektywy takie jak `#if`, `#ifdef`, `#ifndef`, `#else`, `#elif` oraz `#endif` umożliwiają kompilację różnych fragmentów kodu w zależności od spełnienia określonych warunków. Jest to szczególnie przydatne w sytuacjach, gdy kod musi być dostosowany do różnych środowisk kompilacji lub konfiguracji.

- **Przykład użycia `#ifdef`**:
  ```c++
  #ifdef DEBUG
  std::cout << "Tryb debugowania aktywny!" << std::endl;
  #endif
  ```
  Kod wewnątrz bloku `#ifdef DEBUG ... #endif` zostanie skompilowany tylko wtedy, gdy zdefiniowany jest symbol `DEBUG`.

### 4. Usuwanie definicji

Dyrektywa `#undef` umożliwia usunięcie wcześniej zdefiniowanej stałej lub makra. Może to być użyteczne, gdy chcemy ponownie zdefiniować nazwę lub upewnić się, że konkretne makro nie jest już używane.

- **Przykład użycia `#undef`**:
  ```c++
  #undef PI
  ```
  Po wykonaniu tej dyrektywy, `PI` nie będzie już rozpoznawane jako zdefiniowane makro.

### 5. Inne dyrektywy preprocesora

- **Dyrektywa `#pragma`**: Używana do dostarczania specjalnych instrukcji kompilatorowi, które mogą wpływać na sposób kompilacji kodu.
  ```c++
  #pragma once
  ```
  Ta dyrektywa zapewnia, że dany plik nagłówkowy jest dołączony tylko raz podczas kompilacji, co zapobiega problemom z wielokrotnym dołączaniem.

- **Dyrektywa `#error`**: Wykorzystuje się ją do generowania błędów kompilacji z określonym komunikatem.
  ```c++
  #ifndef VERSION
  #error "VERSION is not defined"
  #endif
  ```
