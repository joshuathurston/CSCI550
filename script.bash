#!/bin/bash

#author: Joshua David Edward Thurston
#date: 9-8-17
#version: 1.0

infiles=($(ls tests/*.in))
outfiles=($(ls tests/*.out))

for i in "${!infiles[@]}"
do
  echo "test: ${infiles[$i]}"
  test1=$(./proj1 < ${infiles[$i]})
  test1ref=$(cat ${outfiles[$i]})
  if [ $test1 == $test1ref ]
  then
    echo "Passed"
  else
    echo "Failed"
  fi
done

