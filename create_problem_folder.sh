#!/bin/bash
name=$1
if [ -z "$name" ]
then
  echo "name of project is empty"
else
  mkdir "$name"
  mkdir "$name"/inputs
  mkdir "$name"/outputs
  cp preset/parse.py preset/solve.py "$name"/
fi
