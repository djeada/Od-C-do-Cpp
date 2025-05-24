## Liczby losowe i generatory liczb losowych

W języku C++ liczby losowe generuje się za pomocą standardowej biblioteki `<random>`. Proces losowania zaczyna się od utworzenia generatora liczb pseudolosowych, np. `std::mt19937`, który bazuje na algorytmie Mersenne Twister. Aby uzyskać bardziej losowe wyniki, generator inicjalizuje się za pomocą unikalnej wartości, zwaną "ziarnem" (ang. *seed*), co można zrobić np. poprzez `std::random_device`. Następnie używa się odpowiednich dystrybucji, takich jak `std::uniform_int_distribution` (dla liczb całkowitych z równomiernym rozkładem) lub `std::uniform_real_distribution` (dla liczb zmiennoprzecinkowych), aby wygenerować liczby z określonego zakresu. Dzięki tej bibliotece losowanie w C++ jest bardziej elastyczne i daje kontrolę nad różnymi aspektami generowania liczb losowych, w tym nad zakresem i typem wartości.

### Liczby losowe

Teraz zapoznamy się z matematycznymi podstawami pojęcia liczby losowej, definiując zmienne losowe oraz ich rozkłady.

W klasycznej teorii prawdopodobieństwa liczbę losową modeluje **zmienna losowa**

$$
X:(\Omega,\mathcal F,\mathbb P)\longrightarrow (\mathbb R,\mathcal B)
$$

gdzie $(\Omega,\mathcal F,\mathbb P)$ to przestrzeń probabilistyczna, a $\mathcal B$ – σ–algebra borelowska.

Dla każdego przedziału $A\subseteq\mathbb R$ prawdopodobieństwo $\mathbb P!\bigl(X\in A\bigr)$ jest ustalone przez rozkład $F\_X(x)=\mathbb P(X\le x)$.

#### Własności oczekiwane

W tej części opisujemy podstawowe miary statystyczne zmiennej losowej, takie jak wartość oczekiwana i wariancja.

Jeśli $X$ ma gęstość $f\_X$, to

$$
E[X]=\int_{-\infty}^{\infty}xf_X(x)dx
$$

$$
Var[X]=\int_{-\infty}^{\infty}(x- E[X])^{2}f_X(x)dx
$$

Prawo wielkich liczb (LLN) gwarantuje zbieżność średniej $\bar X\_n$ do $E\[X]$ przy $n\to\infty$, a centralne tw. graniczne (CLT) – normalne odchylenie $O(n^{-1/2})$.

#### Prawdziwa losowość vs. pseudolosowość

Teraz omówimy różnice pomiędzy rzeczywistymi źródłami losowości a deterministycznymi generatorami pseudolosowymi.

Źródła entropii

* **Prawdziwe RNG (TRNG).**  Oparte na zjawiskach fizycznych: szum termiczny, promieniotwórczość, odchylenia czasu taktowania CPU.
* **Generator pseudolosowy (PRNG).**  Deterministyczny algorytm

$$
s_{k+1}=F(s_k)\pmod m,\qquad X_k=g(s_k)
$$

który przy zadanym ziarnie $s\_0$ tworzy powtarzalną sekwencję. Parametry:

* **Okres** $p$ – najmniejsze $k>0$ z $s\_{n+k}=s\_n$.
* **Wymiar równomierności** – równomierne pokrycie hipersześcianu $\[0,1)^d$.
* **Test next-bit** (dla RNG kryptograficznych) – nieprzewidywalność kolejnego bitu z prawdopodobieństwem istotnie $>\tfrac12$.

Statystyczne testy jakości

Poniższa tabela przedstawia główne klasy testów statystycznych używanych do oceny generatorów pseudolosowych:

| Klasa testu                  | Weryfikowana własność           | Metryka                                                |
| ---------------------------- | ------------------------------- | ------------------------------------------------------ |
| **Chi-kwadrat**              | jednorodność histogramu         | $\chi^2=\sum \frac{(O\_i-E\_i)^2}{E\_i}$             |
| **Serial/correlation**       | niezależność kolejnych wartości | współczynnik $r=\frac{Cov(X\_i,X\_{i+k})}{\sigma^2}$ |
| **K–S (Kolmogorov–Smirnov)** | zgodność z dystrybuantą $F$   | statystyka sup-normy $D\_n$                          |
| **DieHard / TestU01**        | złożone właściwości             | zbiór  20–100 testów                                   |

Sekwencja testów nie dowodzi losowości, lecz obala ją, gdy statystyki wyjdą poza akceptowalny przedział ufności.

### Generowanie liczb losowych

Teraz przedstawimy dostępne w C++ generatory liczb losowych oraz ich główne właściwości i zastosowania.

Przegląd generatorów

| Generator            | Algorytm                     | Okres                 | Zastosowania                |
| -------------------- | ---------------------------- | --------------------- | --------------------------- |
| `std::mt19937`       | Mersenne Twister (19937-bit) | $2^{19937}-1$       | ogólne symulacje            |
| `std::ranlux24_base` | Tausworthe + przekładanie    | $ \approx 10^{171}$ | obliczeniowa fizyka jądrowa |
| `std::knuth_b`       | LCG + shuffling              | $2^{64}$            | proste gry, testy           |
| `std::random_device` | TRNG – entropia OS           | n/d                   | seeding, kryptografia       |

**Mersenne Twister.**  Rekurencja:

$$
x_{k+n}=x_{k+m}\oplus\bigl((x_k^{\text{upper}}\|\;x_{k+1}^{\text{lower}})\cdot A\bigr),
$$

gdzie $n=624,m=397$. Duży okres i 623-wymiarowa równomierność zapewniają dobry rozkład w praktyce nie-krypto.

#### Dystrybucje

W tej części omówione zostaną najważniejsze dystrybucje dostępne w bibliotece `<random>` oraz ich własności.

| Dystrybucja                      | Parametry           | Gęstość/PMF $f(x)$                                                 |
| -------------------------------- | ------------------- | -------------------------------------------------------------------- |
| `std::uniform_int_distribution`  | $a,b\in\mathbb Z$ | $f(k)=\tfrac1{b-a+1}$                                              |
| `std::uniform_real_distribution` | $a,b\in\mathbb R$ | $f(x)=\tfrac1{b-a}$                                                |
| `std::normal_distribution`       | $\mu,\sigma$      | $f(x)=\frac{1}{\sqrt{2\pi}\sigma}e^{-\frac{(x-\mu)^2}{2\sigma^2}}$ |
| `std::bernoulli_distribution`    | $p$               | $f(1)=p,;f(0)=1-p$                                                 |
| `std::poisson_distribution`      | $\lambda$         | $f(k)=e^{-\lambda}\frac{\lambda^k}{k!}$                            |

Dystrybucje ciągłe implementują **metodę inwersji**

$$
X=F^{-1}(U)\text{ z }U\sim\mathcal U(0,1)
$$

lub transformacje specjalne (np. Box-Muller).

#### Inicjalizacja – właściwości ziarna

Omówimy, jak dobór ziarna wpływa na powtarzalność oraz jakość generowanych sekwencji.

Jeśli dwa generatory otrzymają to samo **seed**, ich sekwencje będą identyczne:

$$
\forall n\;\;x^{(1)}_n = x^{(2)}_n.
$$

W symulacjach replikowalnych podajemy jawnie wartość seeda; w sytuacjach wymagających nieprzewidywalności (kryptografia) używamy `std::random_device`.

### Przykłady użycia (C++ 17)

Poniżej znajdują się przykłady wykorzystania biblioteki `<random>` w praktycznych scenariuszach, ilustrujące różne zastosowania dystrybucji.

#### Liczba z przedziału $\[a,b]\subset\mathbb Z$

Wygenerujemy liczbę całkowitą z zadanego przedziału.

```cpp
std::mt19937 gen(std::random_device{}());
std::uniform_int_distribution<int> dist(a,b);
int x = dist(gen);
```

*Własności.*  $\Pr{X=k}=1/(b-a+1)$. Oczekiwana wartość $E\[X]=\tfrac{a+b}{2}$, wariancja $\sigma^2=\tfrac{(b-a+1)^2-1}{12}$.

#### Rzut monetą – dystrybucja Bernoulliego

Przykład rzutu uczciwą monetą.

```cpp
std::bernoulli_distribution coin(0.5);
bool isHeads = coin(gen);
```

*Analiza.*  $X\sim\mathrm{Bern}(p)$: $E\[X]=p$, Var\[X]=p(1-p).
Dla $n$ rzutów błąd względny częstości maleje jak $O!\bigl(n^{-1/2}\bigr)$.

#### Rzut sześciościenną kostką

Generowanie wyrzutu kostki o sześciu ściankach.

```cpp
std::uniform_int_distribution<int> d6(1,6);
int result = d6(gen);
```

Rozkład dyskretny równomierny na ${1,\dots,6}$.
$E\[X]=3.5,; \sigma^2=\tfrac{35}{12}$.

#### Generator silnych haseł

Przykład tworzenia losowego hasła o zadanej długości.

```cpp
std::string alphabet =
    "abcdefghijklmnopqrstuvwxyz"
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "0123456789!@#$%^&*()-_=+";
std::uniform_int_distribution<size_t> pick(0, alphabet.size()-1);

auto password = [&] (size_t n) {
    std::string s;
    for(size_t i=0;i<n;++i) s+=alphabet[pick(gen)];
    return s;
};
```

Entropia hasła $H = n\log\_2 |\text{alphabet}|$.
Dla $n=12$ i $|alphabet| = 74$: $H\approx 71$ bitów.

#### Metody Monte Carlo

Demonstracja estymacji całki przy pomocy losowania.

```cpp
std::uniform_real_distribution<double> U(a,b);
double sum = 0;
for(size_t k=0;k<N;++k) sum += g(U(gen));
double I = (b-a)*sum/N;
```

Symulacyjna estymata całki:

$$
I=\int_{a}^{b}g(x)dx,
\qquad  
\hat I_N = (b-a)\frac1N\sum_{k=1}^N g(U_k),\quad U_k\sim\mathcal U(a,b).
$$

*Błąd przeciętny* $RMSE=\sigma/\sqrt N$ z $\sigma^2=Var\[g(U)]$.
**Uwaga.**  Dla funkcji silnie oscylujących warto stosować *ważoną próbę* (importance sampling) lub *stratyfikację*.

#### RNG kryptograficzne (CSPRNG)

Wymagania formalne (Goldwasser–Micali):

1. **Jednokierunkowość** – brak efektywnego algorytmu do odtworzenia seeda.
2. **Test next-bit** –

$$
\Pr[G(x)_i = 1 \mid G(x)_1, G(x)_2, \dots, G(x)_{i-1}]
= \frac{1}{2} \pm \varepsilon(\lambda).
$$

gdzie $\varepsilon$ jest zaniedbywalne względem parametru bezpieczeństwa $\lambda$.

W C++20 brak oficjalnego CSPRNG, ale popularne biblioteki (libsodium, Botan) udostępniają `randombytes_buf`, `crypto_rng`. Dla systemowego źródła entropii można użyć:

```cpp
#include <openssl/rand.h>
unsigned char buf[32];
RAND_bytes(buf, sizeof(buf)); // 256-bit
```

### Zastosowanie różnych dystrybucji

Teraz omówimy zastosowania kilku dystrybucji losowych dostępnych w bibliotece `<random>`, prezentując ich definicje, własności, implementację w C++ oraz przykłady użycia.

#### Dystrybucja równomierna

Dystrybucja równomierna generuje wartości o jednakowym prawdopodobieństwie w całym zakresie, co jest przydatne, gdy potrzebujemy równomiernie rozłożyć próbki.

Dyskretna wersja na zbiorze kolejnych liczb całkowitych ${a,\dots,b}$:

$$
\mathbb P(X=k)=\frac1{b-a+1},\qquad k=a,\dots,b
$$

Wersja ciągła na przedziale $\[a,b]$:

$$
f(x)=\frac1{b-a}\mathbf 1_{[a,b]}(x)
$$

$$
F(x)=\frac{x-a}{b-a}
$$

W poniższych wzorach przedstawiono momenty i funkcję generującą momenty (MGF), które charakteryzują tę dystrybucję:

$$
E[X]=\frac{a+b}{2}
$$

$$
Var[X]=\frac{(b-a)^2}{12}
$$

$$
M_X(t)=\frac{e^{tb}-e^{ta}}{t(b-a)}\;(t\ne 0)
$$

**Implementacja**

```cpp
std::mt19937 gen(std::random_device{}());
std::uniform_int_distribution<int> U(a,b);
int k = U(gen);
```

> **Rada.**  Generator wywołuj **raz** i przekazuj referencję; kosztowna inicjalizacja `std::random_device{}` nie powinna znajdować się w pętli.

##### Przykład: 10 liczb w zakresie $\[1,100]$

Poniżej przykład wylosowania dziesięciu liczb z przedziału \[1,100]:

```cpp
std::cout << "Uniform[1,100]: ";
for(int i=0;i<10;++i) std::cout << U(gen) << ' ';
```

#### Dystrybucja normalna (Gaussa)

Rozkład normalny, zwany też Gaussa, opisuje zmienną losową o gęstości dzwonowej i jest uzywany w statystyce ze względu na centralne twierdzenie graniczne.

$$
f(x)=\frac1{\sqrt{2\pi}\sigma}\exp\!\Bigl[-\frac{(x-\mu)^2}{2\sigma^2}\Bigr],
\quad x\in\mathbb R
$$

##### Parametry

Podstawowe parametry wpływające na położenie i rozrzut rozkładu przedstawiono poniżej:

$$
E[X]=\mu
$$

$$
Var[X]=\sigma^{2}
$$

$$
M_X(t)=\exp\!\left(\mu t+\tfrac12\sigma^{2}t^{2}\right)
$$

Suma niezależnych $X\_i\sim\mathcal N(\mu\_i,\sigma\_i^2)$ jest również normalna:

$$
\sum_i X_i \sim \mathcal N\!\Bigl(\sum \mu_i,\;\sum\sigma_i^2\Bigr)
$$

**Implementacja**

```cpp
std::normal_distribution<double> N(mu, sigma);
double x = N(gen);
```

Przykład generowania próbek z rozkładu normalnego o zadanych parametrach:

```cpp
std::cout << "Normal(50,10): ";
for(int i=0;i<10;++i) std::cout << N(gen) << ' ';
```

> **Weryfikacja.**  Aby sprawdzić poprawność generatora, warto przeprowadzić prostą weryfikację statystyczną:
>
> 1. zbuduj histogram,
> 2. oblicz statystykę K–S $D\_n=\sup\_x|F\_n(x)-\Phi\_{\mu,\sigma}(x)|$,
> 3. odrzucaj generator jeśli $D\_n>D\_{\alpha,n}$ dla wybranego poziomu $\alpha$.

#### Dystrybucja Bernoulliego

Dystrybucja Bernoulliego modeluje zdarzenie dychotomiczne, zwracając 1 z prawdopodobieństwem $p$ lub 0 z prawdopodobieństwem $1-p$.

$$
\mathbb P(X=1)=p,\qquad \mathbb P(X=0)=1-p,\quad 0<p<1.
$$

##### Parametry

$$
E[X]=p
$$

$$
Var[X]=p(1-p)
$$

$$
M_X(t)=1-p+pe^{t}
$$

**Związek z rozkladem dwumianowym.**  Suma prób Bernoulliego prowadzi do rozkładu dwumianowego, co ilustruje związek pomiędzy tymi rozkładami:

$$
\sum_{i=1}^{n}X_i \sim \mathrm{Bin}(n,p).
$$

**Implementacja**

```cpp
double p = 0.3;
std::bernoulli_distribution B(p);
bool success = B(gen);
```

**Przykład: 10 losowań, $p=0,3$**

Przykład wykonania dziesięciu niezależnych prób Bernoulliego:

```cpp
for(int i=0;i<10;++i) std::cout << B(gen) << ' ';
```

> **Analiza częstości.**  Analiza częstościowa pozwala na ocenę zbieżności częstości względnej do $p$ oraz wyznaczenie przedziału ufności 95 %:
>
> $\hat p \pm 1.96\sqrt{p(1-p)/n}$

Tabela poniżej zestawia informacje o omawianych dystrybucjach, umożliwiając szybkie porównanie:

| Rozkład              | Kod dystr. `<random>`           | Parametry      | $E\[X]$          | $Var\[X]$                 | Typ danych    |
| -------------------- | ------------------------------- | -------------- | ------------------ | --------------------------- | ------------- |
| Równomierny (dyskr.) | `std::uniform_int_distribution` | $a,b$        | $\tfrac{a+b}{2}$ | $\tfrac{(b-a+1)^2-1}{12}$ | całkowite     |
| Normalny             | `std::normal_distribution`      | $\mu,\sigma$ | $\mu$            | $\sigma^2$                | zmiennoprzec. |
| Bernoulli            | `std::bernoulli_distribution`   | $p$          | $p$              | $p(1-p)$                  | bool/int      |

### Zalety i wady różnych metod

Teraz porównamy najpopularniejsze metody generowania liczb losowych w C++, omawiając ich zalety oraz ograniczenia w różnych zastosowaniach.

#### `std::random` (C++11)

Biblioteka `<random>` w C++11 dostarcza elastyczny interfejs „generator + dystrybucja” bazujący domyślnie na `std::mt19937`. Poniżej przyjrzymy się matematycznemu modelowi Mersenne Twistera wraz z jego mocnymi i słabymi stronami.

**Model matematyczny**

Domyślny wybór – `std::mt19937` – jest implementacją algorytmu Mersenne Twistera:

$$
\begin{aligned}
x_{k+n} &= x_{k+m}\oplus\Bigl((x_k^{u}\parallel x_{k+1}^{\ell})A\Bigr),\\
n&=624,\;m=397,\\
\text{okres}&=2^{19937}-1\approx 10^{6001},\\
d_{\max}&=623\quad\text{(wymiar równomierności).}
\end{aligned}
$$

*Spektralny test równoległości* daje wynik rzędu $2^{-2018}$ – przy wielu zastosowaniach symulacyjnych uznaje się to za „praktycznie idealne”.

**Zalety**

| Aspekt                    | Wartość dodana                       | Komentarz matematyczny                                                    |
| ------------------------- | ------------------------------------ | ------------------------------------------------------------------------- |
| **Okres**                 | $2^{19937}-1$                      | eliminuje cykliczność w trwałych symulacjach                              |
| **Równomierność**         | 623-wymiarowa                        | równy rozkład punktów w hipersześcianie $\[0,1)^{623}$                   |
| **Bogactwo dystrybucji**  | normalna, Poissona, gamma…           | każda dystrybucja to transformacja $X=F^{-1}(U)$ lub specjalny algorytm |
| **Konfigurowalne ziarno** | deterministyczne lub `random_device` | replikowalność lub entropia systemowa                                     |
| **Przenośność**           | zdefiniowane przez ISO/IEC 14882     | identyczna sekwencja dla tego samego seeda na wszystkich kompilatorach    |

**Wady**

1. Trzeba rozumieć dwustopniowy model: *generator + dystrybucja*.
2. **Brak odporności kryptograficznej** – Mersenne Twister jest liniowy nad \$\mathbb F\_2\$; stan generatora (19937 bitów) można odtworzyć na podstawie 19937 kolejnych wyjść.
3. **Koszt inicjalizacji** – `std::random_device` może być wolny (blokuje podczas odczytu z `/dev/urandom`).
4. **Rozmiar stanu** – 2,5 KB dla `mt19937`; przy wielu wątkach oznacza to znaczną ilość pamięci.

#### `rand()` – klasyczny LCG

Funkcja `rand()` to prosty liniowy kongruentny generator (LCG) o minimalnym API, często używany dla szybkiego startu, ale z istotnymi ograniczeniami.

**Model matematyczny**

Większość implementacji to **liniowy generator**:

$$
x_{n+1} = (ax_n + c)\;\bmod m,
$$

typowe stałe (glibc, MSVC):

$$
a=1103515245,\;c=12345,\;m=2^{31}.
$$

Okres ≤ $m=2^{31};(\approx2.1\cdot10^9)$. Najmłodszy bit ma okres 2, co czyni go bezużytecznym w symulacjach binarnych.

**Zalety**

| Aspekt            | Argument                            | Uwaga                                                    |
| ----------------- | ----------------------------------- | -------------------------------------------------------- |
| **Minimalne API** | `int r = rand();`                   | brak szablonów ↔ szybki start                            |
| **Dostępność**    | C89 / C++98                         | działanie na wbudowanych systemach, bibliotece `libc`    |
| **Przepustowość** | jedna operacja mnożenia + dodawania | przeciętnie 2–3× szybciej od `mt19937` (zależnie od CPU) |

**Wady**

1. **Krótki okres generacji** – przy prędkości 10⁸ liczb/s pełny cykl wyczerpuje się w ok. 21 s.
2. **Słabe własności spektralne** – pojawiają się korelacje w przestrzeni 3D w symulacjach Monte Carlo.
3. **Niejednorodność implementacji** – różne kompilatory używają odmiennych stałych.
4. **Brak wbudowanych rozkładów** – konieczne ręczne przekształcenia (np. metoda Box–Mullera).
5. **Łamliwość kryptograficzna** – na podstawie zaledwie trzech wyjść można odzyskać parametry generatora.

#### Zestawienie porównawcze

Poniżej tabela podsumowująca różnice między `std::mt19937` a `rand()`:

| Kryterium                   | `std::mt19937`       | `rand()` (LCG) |
| --------------------------- | -------------------- | -------------- |
| Okres                       | $2^{19937}-1$      | ≤ $2^{31}$   |
| Równomierność $d\_{\max}$ | 623                  | ≤ 5            |
| Koszt generacji             | \~10 ns              | \~5 ns         |
| Rozmiar stanu               | 2,5 KB               | 4 B            |
| Kryptografia                | ❌ (liniowość)        | ❌              |
| Wbudowane dystrybucje       | ✔ (\~20)             | ❌              |
| Standaryzacja seeda         | ✔ (deterministyczna) | ❌              |
| Łatwość użycia              | umiarkowana          | wysoka         |

