#!/bin/bash

#author: Joshua David Edward Thurston
#date: 9-8-17
#version: 1.1
#notes: Project executable must be labeled proj followed by a number "ex proj1"
#       Every '.in' test must have an '.out' test with the same name
#       All tests must be in the folder called tests in project folder
#brief: script for theory projects to compare text in and out tests

sourceFile=($(ls | egrep '^proj[1-9]$'))

[[ -z $sourceFile ]] && echo "Executable file does not exist" && exit 1

infiles=($(ls tests/*.in))
outfiles=($(ls tests/*.out))

for i in "${!infiles[@]}"
do
  echo "test: ${infiles[$i]} : ${outfiles[$i]}"
  test1=$(./$sourceFile < ${infiles[$i]})
  test1ref=$(cat ${outfiles[$i]})
  if [ "$test1" == "$test1ref" ]
  then
    echo "Passed"
  else
    echo "Failed"
    echo "----------              ----------"
    echo "-Expected-              - Actual -"
    echo "----------              ----------"
    printf "%-19.19s     %-19.19s\n" "$test1" "$test1ref"
   
  fi
done
