// Wiele funkcji z algorithm dostepne jest jako metody w wielu strukturach
// danych Nieraz uzywanie metod dla dostepnych struktur danych jest
// niejednokrotnie szybsze niz alternatywy z algorithm

unordered_set<int> s = {2, 4, 1, 8, 5, 9};

// O(1)
auto itr = s.find(4);

// O(n)
itr = find(s.begin(), s.end(), 4);

map<char, string> mapa = {{'p', "poniedzialek"}, {'w', "wtorek"}};

// O(logn)
auto itr_2 = mapa.find('c');

// O(n)
itr_2 = find(mapa.begin(), mapa.end(), make_pair('c', "czwartek"));

list<int> lista = {2, 1, 4, 6, 7, 8}

                  // O(n)
                  lista.remove(4);

// O(n)
remove(lista.begin(), lista.end(), 4);
