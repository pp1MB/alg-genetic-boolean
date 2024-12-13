# N-SAT Genético
### [Video da apresentação](https://youtu.be/sZxT2KXBwtc)

## Problema da Satisfabilidade Booleana (SAT)
O problema de satisfatibilidade booliana (SAT) é um dos problemas fundamentais da teoria da complexidade computacional, sendo o primeiro identificado como NP-completo. Ele consiste em determinar se existe uma atribuição de valores de verdade para as variáveis de uma fórmula booliana que torne a fórmula verdadeira. Por exemplo, para uma fórmula como $(x_{1}+ \neg x_{3}+x_{4}) \cdot (\neg x_{2}+x_{3}+ \neg x_{4})$, o objetivo é encontrar (ou verificar a inexistência de) valores para $x_{1}$, $x_{2}$, $x_{3}$, $x_{4}$​ que satisfaçam a fórmula. Caso exista, a fórmula é considerada satisfatível; caso contrário, é insatisfatível.

## Algoritimo genético
### O que é um algoritimo genético
Um Algoritmo Genético (AG) é uma técnica de busca e otimização inspirada no processo de evolução natural, baseada nos princípios de seleção natural, mutação e reprodução. Ele é usado para resolver problemas complexos, onde encontrar uma solução exata pode ser inviável, como no caso dos problemas NP-completos.
Os AGs trabalham com uma população de soluções candidatas (chamadas de indivíduos), representadas geralmente como cromossomos. Cada cromossomo é avaliado por uma função de fitness, que mede a qualidade da solução que ele representa.
### Função de fitness
No caso do SAT, a função de avaliação do fitness consiste da quantidade de cláusulas que um determinado cromossomo consegue satisfazer (ou seja, são iguais a 1).
### Método de reprodução
O código utiliza o método de single point crossover, que consiste de selecionar um ponto aleatório do cromossomo, e mudar todos os genes subsequêntes pelos genes do melhor indivíduo.
### Mutação
Para a mutação, quando um novo indivíduo é criado, existe uma chance de 5% de qualquer gene ser negado (x = !x).

## Como rodar
A aplicação utiliza as seguintes bibliotecas para funcionar:
- GNUplot
- Tkinter
Para instalar elas basta utilizar os comandos
```
pip install tkinter
sudo apt-get install gnuplot
```

Após instaladas, o programa pode ser utilizado com o comando
```
python3 interface.py
```

## Como gerar casos teste
Para gerar casos teste para o caso de N cláusulas, M variáveis, use o bashScript na pasta CASOS_TESTE:
```
chmod +x geraCasos.sh
./geraCasos.sh
```
Os casos serão salvos na pasta "entradas", dentro da pasta CASOS_TESTE.

## Autores
- Dante Brito Lourenço - 15447326
- João Gabriel Pieroli da Silva - 15678578
- Juan Marque Jordão - 
- Pedro Henrique de Sousa Preste - 15507819
- Pedro Lunkes Villela - 15484287
