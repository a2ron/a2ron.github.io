#!/bin/sh
ord() {
  printf %d "'$1"
}

echo "$@" | grep -o . | while read letter; do
    input=""
    letter=$(echo $letter | awk '{print toupper($0)}')
    code=$(ord $letter)
    if [ $code -ge $(ord A) ] && [ $code -le  $(ord Z) ]; then
        input=$letter
    elif [ $code -ge $(ord 0) ] && [ $code -le  $(ord 9) ]; then
        input=$(($letter + 7))
    else #blank space
        input="62"
    fi
    echo "$letter-$code-$input"
    input keyevent "$input"
done