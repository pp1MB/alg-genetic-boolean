#!/bin/bash
A=$@

if [ ! -d "entradas" ]; then
    mkdir entradas
else
    rm -rf entradas
    mkdir entradas
fi

if [ ! -f "c" ]; then
    gcc generator.c -o c
fi

./c $A

rm c
