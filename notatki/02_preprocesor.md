## Preprocesor

Pan Preprocesor przetwarza kod źródłowy. Zadania Pana Preprocesora definiuje się za pomocą specjalnych zaklęć zwanych dyrektywami, rozpoczynających się od znaku #. Dyrektywy mogą znajdować się w dowolnym miejscu programu, ale zwykle umieszcza się je na początku pliku źródłowego. Najczęściej spotykane dyrektywy to np. załączenie biblioteki:

```c++
#include <biblioteka>
```

Dyrektywy służą również do definiowania stałych:

```c++
#define TRUE 1
```

oraz włączania/wyłączania części kodu w zależności od określonego warunku, działając podobnie do zwykłych instrukcji warunkowych, tyle że ustalane przed uruchomieniem programu:

```c++
#if 1 == 1
// kod
#else
// inny kod
#endif
```
