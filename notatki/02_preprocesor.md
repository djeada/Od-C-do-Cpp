## Preprocesor

Pan Preprocesor to program, który przetwarza kod źródłowy języka programowania, zmieniając go przed kompilacją lub interpretacją. Pana Preprocesora można sterować za pomocą specjalnych zaklęć zwanych dyrektywami, rozpoczynających się od znaku `#`. Dyrektywy mogą być umieszczone w dowolnym miejscu programu, ale zwykle definiuje się je na początku pliku. 

Dyrektywy są szeroko stosowane do wykonywania różnych zadań, takich jak: załączenie biblioteki, definiowanie stałych lub zmiennej preprocesora, włączanie i wyłączanie części kodu w zależności od wybranego warunku. Przykładem może być dyrektywa `#include` używana do załączenia biblioteki:

```c++
#include <biblioteka>
```

lub dyrektywa `#define` używana do definiowania stałych:

```c++
#define TRUE 1
```

lub dyrektywa `#if` używana do włączania/wyłączania części kodu w zależności od wybranego warunku:

```c++
#if 1 == 1
  // kod
#else
  // inny kod
#endif
```
