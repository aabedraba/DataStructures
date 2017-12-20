#!/bin/bash

files=${*}
for i in $files
do
  mkdir ${i}/build/
  touch ${i}/build/.keep
  git rm -r ${i}/.idea
  git rm -r ${i}/cmake-build-debug
  git add ${i}
done
