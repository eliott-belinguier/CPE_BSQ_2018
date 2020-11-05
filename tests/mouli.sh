#!/bin/bash

if [ $# -ne 1 ]; then
    echo -e "\033[91m[ ERROR ]\033[0m"
    exit 84
fi

for fileName in ./resource/mouli_maps/*; do
    name=${fileName##*/}
    ../$1 $fileName > tmp.txt
    if [[ -z $(diff tmp.txt ./resource/mouli_maps_solved/$name) ]]; then
        echo -e "\033[92m[ TEST ]\033[0m" $name
    else
        echo -e "\033[91m[ ERROR TEST ]\033[0m" $name
    fi
done
rm -f tmp.txt
