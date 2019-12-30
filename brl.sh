#!/usr/bin/env bash

mkdir -p build
cd build || exit 1
if [ "$1" = "r" ]; then
	read -p "Are you sure? " -n 1 -r
	echo
	rm -rf ./*
	cmake  -DCMAKE_BUILD_TYPE=Release ..
fi
make
