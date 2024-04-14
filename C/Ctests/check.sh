#!/bin/bash
g++ sprawdz.cpp -o sprawdz
parent_path=$( cd "$(dirname "${BASH_SOURCE[0]}")" ; pwd -P )
cd "$parent_path"
folder=("tiny" "small" "mid" "fat")
program=$1
for i in {0..3}
do
    fol="${folder[${i}]}"
    echo "$fol"
    for k in {1..500}
    do
        $($program < ./tests/${fol}/in/${k}.in > ./a.out)
        cat ./tests/${folder[${i}]}/in/${k}.in a.out ./tests/${folder[$i]}/out/${k}.out > c.out
        ./sprawdz ${k} < c.out
    done
done