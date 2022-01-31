#!/usr/bin/env bash

paths=(c cpp)
for path in "${paths[@]}"; do
    hooks/clang_format.sh $path
    hooks/remove_carriage_return.sh $path
    hooks/correct_file_names.sh $path
    hooks/remove_diacritics.sh $path
done


