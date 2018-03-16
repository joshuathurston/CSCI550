#!/bin/bash

#author: Joshua David Edward Thurston
#date: 9-8-17
#version: 1.1
#notes: Project executable must be labeled proj followed by a number "ex proj1"
#       Every '.in' test must have an '.out' test with the same name
#       All tests must be in the folder called tests in project folder
#brief: script for theory projects to compare text in and out tests

sourceFile=($(ls | egrep '^proj[1-9]$'))

[[ -z $sourceFile ]] && exit 1

infiles=($(ls tests/*.in))
outfiles=($(ls tests/*.out))

for i in "${!infiles[@]}"
do
  echo "test: ${infiles[$i]}"
  test1=$(./$sourceFile < ${infiles[$i]})
  test1ref=$(cat ${outfiles[$i]})
  echo $test1
  echo $test1ref
  if [ "$test1" == "$test1ref" ]
  then
    echo "Passed"
  else
    echo "Failed"
  fi
done

