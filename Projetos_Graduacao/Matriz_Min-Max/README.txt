----Funcionamento----
Ao inserir um arquivo tsx contendo uma matriz quadrada de elementos (máximo = 64) com pelo menos um espaço separando cada um deles (sem espaço no final da linha), o programa retorna, em um arquivo de saída, os valores e coordenadas dos elementos mínimo e máximo. Caso haja empate, é priorizado o elemento de menor linha, em primeira instância, e o elemento de menor coluna, em segunda instância.

----Objetivo----
Programa em linguagem C que implementa um algoritmo utilizando recursão e divisão e conquista para identificar a coordenada e o valor do pixel (representado por um número entre 0 e 255) mais escuro (menor valor) e a coordenada e o valor do pixel mais claro (maior valor) em uma imagem digital em nível de cinza representada em uma matriz quadrada Mnxn sendo n uma potência de 2.

----Execução no Linux----
$./<nome_arquivo_compilável.c> <quantidade_elementos_matriz> <entrada.txt> <saida.txt>

----Exemplo de execução----
$./matriz_min_max.c 64 <teste_entrada.txt> <teste_saida.txt>

----Habilidades Praticadas----
Tratamento de comandos via linha de comando (argc e argv);leitura, manipulação e criação de arquivos via código; alocação dinâmica de memória; programação orientada a funções; criação, manipulação e tratamento de matriz; técnicas de recursividade; técnicas de divisão e conquista; manipulação de ponteiros; lógica computacional.