#!/usr/bin/env bash

clang_formatter.sh .
remove_carriage_return.sh .
correct_file_names.sh .
remove_diacritics.sh .

