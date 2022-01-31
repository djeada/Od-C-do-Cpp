#!/usr/bin/env bash

remove_diactrics ()
{
    sed -i 'y/aaaaaceeeeeiiiilnooooosuuuuüüüüzzAAAAACEEEEEIIIILNOOOOOSUUUUÜÜÜÜZZ/aaaaaceeeeeiiiilnooooosuuuuüüüüzzAAAAACEEEEEIIIILNOOOOOSUUUUÜÜÜÜZZ/' $1
}

main() {

    if [ $# -eq 0 ]; then
        echo "Must provide a path!"
        exit 1
    fi

    if [ $1 == '.' ] || [ -d "${1}" ]; then
        for file in $(find $1 -maxdepth 10 -type f)
        do
            remove_diactrics $file
        done
    elif [ -f "${1}" ]; then
        remove_diactrics $1
    else
        echo "$1 is not a valid path!"
    fi

}

main "$@"
