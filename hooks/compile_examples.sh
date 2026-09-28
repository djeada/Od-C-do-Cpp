#!/usr/bin/env bash
set -uo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
BUILD_DIR="$(mktemp -d)"
trap 'rm -rf "$BUILD_DIR"' EXIT

failures=0

while IFS= read -r -d '' file; do
    relative="${file#"$ROOT/"}"
    echo "::error file=$relative::Source file is empty"
    failures=$((failures + 1))
done < <(find "$ROOT/src" -regextype posix-extended -type f -empty -regex '.*\\.(c|cpp|cc|cxx|h|hpp)' -print0)

compile_one() {
    local compiler="$1"
    local standard="$2"
    local file="$3"
    local object="$BUILD_DIR/$(echo "$file" | tr '/ ' '__').o"

    echo "::group::Compiling $file"
    if ! "$compiler" "$standard" -Wall -Wextra -Wpedantic -Werror         -c "$ROOT/$file" -o "$object"; then
        echo "::error file=$file::Compilation failed"
        failures=$((failures + 1))
    fi
    echo "::endgroup::"
}

link_standalone() {
    local compiler="$1"
    local standard="$2"
    local file="$3"
    local binary="$BUILD_DIR/standalone_$(echo "$file" | tr '/ ' '__')"

    echo "::group::Linking standalone $file"
    if ! "$compiler" "$standard" -Wall -Wextra -Wpedantic -Werror -pthread         "$ROOT/$file" -o "$binary"; then
        echo "::error file=$file::Standalone linking failed"
        failures=$((failures + 1))
    fi
    echo "::endgroup::"
}

link_example() {
    local name="$1"
    shift

    echo "::group::Linking $name"
    if ! g++ -std=c++17 -Wall -Wextra -Wpedantic -Werror -pthread "$@"         -o "$BUILD_DIR/$name"; then
        echo "::error::Linking $name failed"
        failures=$((failures + 1))
    fi
    echo "::endgroup::"
}

while IFS= read -r -d '' file; do
    relative="${file#"$ROOT/"}"
    compile_one gcc -std=c11 "$relative"
    link_standalone gcc -std=c11 "$relative"
done < <(find "$ROOT/src" -type f -name '*.c' -size +0c -print0 | sort -z)

while IFS= read -r -d '' file; do
    relative="${file#"$ROOT/"}"
    compile_one g++ -std=c++17 "$relative"

    case "$relative" in
      src/cpp/04_klasy/02_pracownik/main.cpp|      src/cpp/04_klasy/03_liczba_zespolona/main.cpp|      src/cpp/04_klasy/05_lista_obiektow/main.cpp|      src/cpp/12_struktury_danych/01_stos/main.cpp|      src/cpp/12_struktury_danych/02_tablica_mieszajaca/main.cpp)
        ;;
      *)
        if grep -qE '(^|[[:space:]])int[[:space:]]+main[[:space:]]*\(' "$ROOT/$file"; then
          link_standalone g++ -std=c++17 "$relative"
        fi
        ;;
    esac
done < <(find "$ROOT/src" -type f \( -name '*.cpp' -o -name '*.cc' -o -name '*.cxx' \) -size +0c -print0 | sort -z)

link_example pracownik     "$ROOT/src/cpp/04_klasy/02_pracownik/main.cpp"     "$ROOT/src/cpp/04_klasy/02_pracownik/pracownik.cpp"

link_example zespolona     "$ROOT/src/cpp/04_klasy/03_liczba_zespolona/main.cpp"     "$ROOT/src/cpp/04_klasy/03_liczba_zespolona/zespolona.cpp"

link_example lista_obiektow     "$ROOT/src/cpp/04_klasy/05_lista_obiektow/main.cpp"     "$ROOT/src/cpp/04_klasy/05_lista_obiektow/lista.cpp"     "$ROOT/src/cpp/04_klasy/05_lista_obiektow/student.cpp"

link_example stos     "$ROOT/src/cpp/12_struktury_danych/01_stos/main.cpp"     "$ROOT/src/cpp/12_struktury_danych/01_stos/stos.cpp"

link_example hash     "$ROOT/src/cpp/12_struktury_danych/02_tablica_mieszajaca/main.cpp"     "$ROOT/src/cpp/12_struktury_danych/02_tablica_mieszajaca/hash.cpp"

if (( failures > 0 )); then
    echo "$failures compilation/linking checks failed."
    exit 1
fi

echo "All source files compile and link successfully."
