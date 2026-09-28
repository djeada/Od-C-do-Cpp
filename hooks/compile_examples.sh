#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
BUILD_DIR="$(mktemp -d)"
trap 'rm -rf "$BUILD_DIR"' EXIT

compile_one() {
    local compiler="$1"
    local standard="$2"
    local file="$3"
    local object="$BUILD_DIR/$(echo "$file" | tr '/ ' '__').o"

    echo "Compiling $file"
    "$compiler" "$standard" -Wall -Wextra -Wpedantic -Werror -c "$ROOT/$file" -o "$object"
}

while IFS= read -r -d '' file; do
    relative="${file#"$ROOT/"}"
    compile_one gcc -std=c11 "$relative"
done < <(find "$ROOT/src" -type f -name '*.c' -size +0c -print0 | sort -z)

while IFS= read -r -d '' file; do
    relative="${file#"$ROOT/"}"
    compile_one g++ -std=c++17 "$relative"
done < <(find "$ROOT/src" -type f \( -name '*.cpp' -o -name '*.cc' -o -name '*.cxx' \) -size +0c -print0 | sort -z)

echo "Linking multi-file examples"

g++ -std=c++17 -Wall -Wextra -Wpedantic -Werror     "$ROOT/src/cpp/04_klasy/02_pracownik/main.cpp"     "$ROOT/src/cpp/04_klasy/02_pracownik/pracownik.cpp"     -o "$BUILD_DIR/pracownik"

g++ -std=c++17 -Wall -Wextra -Wpedantic -Werror     "$ROOT/src/cpp/04_klasy/03_liczba_zespolona/main.cpp"     "$ROOT/src/cpp/04_klasy/03_liczba_zespolona/zespolona.cpp"     -o "$BUILD_DIR/zespolona"

g++ -std=c++17 -Wall -Wextra -Wpedantic -Werror     "$ROOT/src/cpp/04_klasy/05_lista_obiektow/main.cpp"     "$ROOT/src/cpp/04_klasy/05_lista_obiektow/lista.cpp"     "$ROOT/src/cpp/04_klasy/05_lista_obiektow/student.cpp"     -o "$BUILD_DIR/lista_obiektow"

g++ -std=c++17 -Wall -Wextra -Wpedantic -Werror     "$ROOT/src/cpp/12_struktury_danych/01_stos/main.cpp"     "$ROOT/src/cpp/12_struktury_danych/01_stos/stos.cpp"     -o "$BUILD_DIR/stos"

g++ -std=c++17 -Wall -Wextra -Wpedantic -Werror     "$ROOT/src/cpp/12_struktury_danych/02_tablica_mieszajaca/main.cpp"     "$ROOT/src/cpp/12_struktury_danych/02_tablica_mieszajaca/hash.cpp"     -o "$BUILD_DIR/hash"

echo "All source files compile successfully."
