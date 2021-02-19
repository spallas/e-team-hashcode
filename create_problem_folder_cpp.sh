#!/bin/bash
name=$1
if [ -z "$name" ]
then
  echo "name of project is empty"
else
  mkdir "$name"_cpp
  mkdir "$name"_cpp/inputs
  mkdir "$name"_cpp/outputs
  cp hash_code_lib_cpp/FileManager.hpp "$name"_cpp/
  cp hash_code_lib_cpp/main.cpp "$name"_cpp/
  cp hash_code_lib_cpp/build.sh "$name"_cpp/
  cp hash_code_lib_cpp/clean.sh "$name"_cpp/
  cp hash_code_lib_cpp/make_src.sh "$name"_cpp/
fi
