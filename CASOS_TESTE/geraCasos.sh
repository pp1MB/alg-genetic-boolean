#!/bin/bash

if [ ! -d "entradas" ]; then
    mkdir entradas
else
    rm -rf entradas
    mkdir entradas
fi

if [ ! -f "c" ]; then
    gcc generator.c -o c
fi

echo "Quantos casos testes serão criados: "
read QUANT

echo "Quantas variáveis os testes terão (de x1 a xn): "
read VAR

echo "Quantas cláusulas os testes devem ter: "
read AND

echo "Quantos termos os testes devem ter: "
read OR

./c $QUANT $VAR $AND $OR

rm c
