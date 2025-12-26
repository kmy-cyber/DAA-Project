#!/bin/bash

mkdir -p tests

N=${1:-100}

for ((i=1; i<=N; i++)); do
    printf -v num "%02d" $i
    bin/test $i > tests/test${num}.in
done

echo "Generated $N tests."
