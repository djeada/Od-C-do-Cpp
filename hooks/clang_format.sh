#!/usr/bin/env bash

main() {

    find . -regex '.*\.\(cpp\|hpp\|cu\|c\|h\)' -exec clang-format -style=file -i {} \;

}

main "$@"
