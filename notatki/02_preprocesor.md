## Preprocesor

Preprocesor to narzędzie, które działa na kodzie źródłowym języka programowania przed właściwym procesem kompilacji. Za jego działanie odpowiadają dyrektywy preprocesora, rozpoczynające się od znaku `#`. Mimo że dyrektywy te mogą być rozmieszczone w dowolnym miejscu kodu źródłowego, zwykle umieszcza się je na początku pliku dla większej przejrzystości.

Dyrektywy preprocesora pełnią różne funkcje, w tym:

### 1. Załączanie bibliotek

Dzięki dyrektywie `#include`, możemy załączyć zawartość innych plików do naszego kodu. Na przykład:

```c++
#include <iostream>
```

lub

```c++
#include "moj_plik.h"
```

### 2. Definiowanie stałych i makr

Za pomocą `#define` można definiować stałe lub makra:

```c++
#define PI 3.141592653589793
```

Można również definiować makra z parametrami, które działają jak funkcje:

```c++
#define MAX(x, y) ((x) > (y) ? (x) : (y))
```

### 3. Warunkowa kompilacja

Dyrektywy takie jak `#if`, `#ifdef`, `#ifndef`, `#else`, `#elif` oraz `#endif` umożliwiają kompilację różnych fragmentów kodu w zależności od spełnienia określonych warunków:

```c++
#ifdef DEBUG
   std::cout << "Tryb debugowania aktywny!" << std::endl;
#endif
```

Warto również pamiętać o dyrektywie #undef, która umożliwia usunięcie wcześniej zdefiniowanej stałej lub makra:

```c++
#undef PI
```

Używając preprocesora w sposób przemyślany, można zwiększyć elastyczność kodu, dostosowując go do różnych środowisk lub warunków kompilacji.
