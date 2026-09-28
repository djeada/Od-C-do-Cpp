#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
BUILD_DIR="$(mktemp -d)"
trap 'rm -rf "$BUILD_DIR"' EXIT

CFLAGS=(-std=c11 -Wall -Wextra -Wpedantic -Werror -g -fno-omit-frame-pointer -fsanitize=address,undefined)
CXXFLAGS=(-std=c++17 -Wall -Wextra -Wpedantic -Werror -g -fno-omit-frame-pointer -fsanitize=address,undefined)

build_run_c() {
  local name="$1"
  local source="$2"
  gcc "${CFLAGS[@]}" "$ROOT/$source" -o "$BUILD_DIR/$name"
  "$BUILD_DIR/$name"
}

build_run_cpp() {
  local name="$1"
  shift
  local sources=()
  for source in "$@"; do
    sources+=("$ROOT/$source")
  done
  g++ "${CXXFLAGS[@]}" "${sources[@]}" -pthread -o "$BUILD_DIR/$name"
  "$BUILD_DIR/$name"
}

build_run_c malloc_i_free src/c/02_wskazniki/08_malloc_i_free/main.c
build_run_c modyfikacja_napisow src/c/03_napisy/02_modyfikacja_napisow/main.c
build_run_c maski src/c/04_binarka/05_maski/main.c
build_run_c bst src/c/06_struktury_danych/02_binarne_drzewo_poszukiwan/main.c

gcc "${CFLAGS[@]}" "$ROOT/src/c/06_struktury_danych/01_lista_polaczona/main.c"   -o "$BUILD_DIR/lista_c"
printf '1\n2\n3\n' | "$BUILD_DIR/lista_c"

gcc "${CFLAGS[@]}" -pthread   "$ROOT/src/c/07_przetwarzanie_wspolbiezne/05_rownolegle_sortowanie/main.c"   -o "$BUILD_DIR/sortowanie_rownolegle"
"$BUILD_DIR/sortowanie_rownolegle"

build_run_cpp malloc_vs_new src/cpp/02_wskazniki/01_malloc_vs_new/main.cpp
build_run_cpp move src/cpp/04_klasy/04_konstruktor_przenoszacy/main.cpp
build_run_cpp wektor src/cpp/07_raii/03_wektor/main.cpp
build_run_cpp lista_cpp src/cpp/12_struktury_danych/03_lista_polaczona/main.cpp
build_run_cpp stos   src/cpp/12_struktury_danych/01_stos/main.cpp   src/cpp/12_struktury_danych/01_stos/stos.cpp
build_run_cpp lista_obiektow   src/cpp/04_klasy/05_lista_obiektow/main.cpp   src/cpp/04_klasy/05_lista_obiektow/lista.cpp   src/cpp/04_klasy/05_lista_obiektow/student.cpp

echo "Sanitizer smoke tests passed."
