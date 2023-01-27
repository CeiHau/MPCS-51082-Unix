#!/bin/bash

#Cite: https://stackoverflow.com/questions/369758/how-to-trim-whitespace-from-a-bash-variable
trim() {
    local var="$*"
    # remove leading whitespace characters
    var="${var#"${var%%[![:space:]]*}"}"
    # remove trailing whitespace characters
    var="${var%"${var##*[![:space:]]}"}"
    printf '%s' "$var"
}

clear


if [ $1 = "-o" ]; then
    target="OTHER"
elif [ $1 = "-r" ]; then
    target="REPUBLICAN"
elif [ $1 = "-d" ]; then
    target="DEMOCRAT"   
elif [ $1 = "-l" ]; then
    target="LIBERTARIAN"  
fi

echo $target

while read -r line; do
    var=$(echo "$(trim $line)" | cut -f3 -d" ")
    if [ $var = $target ]; then
        echo "$line"
    fi
done < <(paste -d" " <(cut -f1 -d, data/elections.csv) <(cut -f15 -d, data/elections.csv) | sort | uniq -c | head -n -1)
