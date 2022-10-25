==================================

    Trabalho 1 - INF 310

Nome: Caio Von Rondow Morais
Matrícula: 102029

==================================

Arquivo de teste:

Na primeira linha fica o tamanho do 
buffer com N>0

Nas linhas subsequentes indique com
'p' se quer produzir e 'c' se quer
consumir

Na última linha coloque um '.' 
para indicar a finalização

----------------------------------

EX:

4
p
c
.

----------------------------------

Casos de teste:

1) A solução deve ter pelo menos 1 
produtor e 1 consumidor, cada um 
implementado por uma thread.

case1.txt

----------------------------------

2) Se o buffer estiver cheio, 
a operação produzir deve bloquear 
o produtor até que a operação possa 
ser concluída corretamente;

case2.txt

----------------------------------

3) Se o buffer estiver vazio, a 
operação consumir deve bloquear 
o consumidor até que a operação 
possa ser concluída corretamente;

case3.txt

----------------------------------

4) Se o buffer não estiver cheio 
nem vazio, tanto produtor quanto 
consumidor devem poder acessá-lo;

case4.txt

==================================