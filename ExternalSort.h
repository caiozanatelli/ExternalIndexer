#ifndef EXTERNAL_SORT_H
#define EXTERNAL_SORT_H

#include "Register.h"
#include <stdlib.h>
#include <stdio.h>

// Configurações do módulo
#define MAX_SIZE_DIR    255
#define SIZE_REG        32
#define TOP_ID          1
#define BOTTOM_ID       0

// Estrutura que define um tipo para armazenar as informações (registros) que cabem em memória primária
typedef struct {
    Register *data;
    int capacity;
    int size;
} Buffer;

/*--------------------------------------------------------------------------------
Função:    inicializa um buffer, alocando a  memória disponível e configurando  os
           controladores de tamanho e capacidade. O  número de  elementos alocados
           para  o buffer é  M (em bytes) / 32 (tamanho  do registro), onde M  é a
           memória disponível, a qual é informada pelo usuário e passado para esta 
           função através do parâmetro capacidade.
Entrada:   o buffer a ser inicializado e a capacidade que será definida.
Saída:     sem retorno.
--------------------------------------------------------------------------------*/
void initBuffer(Buffer *buffer, int capacity);


/*-------------------------------------------------------------------------------
Função:    libera a memória alocada para o buffer.
Entrada:   o buffer a ser desalocado.
Saída:     sem retorno.
--------------------------------------------------------------------------------*/
void freeBuffer(Buffer *buffer);


/*-------------------------------------------------------------------------------
Função:    função acessada pelo usuário para executar a ordenação externa, a qual
           inicializa (e posteriormente fecha) os ponteiros de leitura e  escrita 
           utilizados pelo quicksort externo, além de chamar as funções 
           necessárias para a ordenação do arquivo.
Entrada:   uma string  referente ao diretório  do arquivo a ser ordenado, e  dois 
           inteiros, os quais  indicam a memória máxima, em bytes, permitida para
           o programa e o número de registradores que existem no arquivo, 
           respectivamente.
Saída:     sem retorno.
--------------------------------------------------------------------------------*/
void externalSort(char *inputFileDir, int maxMemory, int numRegs);


/*-------------------------------------------------------------------------------
Função:    função que implementa o quicksort  externo. Chama a função de  criação
           das partições  e faz chamadas recursivas para  ordenar as partições da
           esquerda e da direita.

Entrada:   dois inteiros, representando os índices das partições da esquerda e da
           direita. Recebe também quatro  objetos FILE, os quais são os ponteiros
           de leitura inferior e superior e escrita inferior e superior. Por fim,
           recebe o  buffer que será  utilizado para  armazenar os registros  em 
           memória principal.
Saída:     sem retorno.
--------------------------------------------------------------------------------*/
void externalQuicksort(int right, int left, FILE **bottomRead, FILE **topRead, FILE **bottomWrite, FILE **topWrite, Buffer *buffer);


/*--------------------------------------------------------------------------------
Função:    faz o  particionamento do quicksort  externo. Preenche o buffer com  os
           registros do arquivo, se  limitando a no  máximo a  capacidade definida
           pelo usuário. Ordena  os registros da memória principal e faz gravações
           e trocas de registros entre o  buffer e o arquivo, de forma a ordenar a
           partição  atual em memória secundária. Uma vez descarregado o buffer em
           memória externa, essa partição nunca é avaliada novamente.
Entrada:   quatro inteiros, indicando o início e fim da  partição atual e início e
           fim  de uma nova  partição criada. Recebe  também os ponteiros FILE  de
           leitura  inferior e  superior e escrita  inferior e superior. Por  fim,
           recebe também o buffer que armazenará os registros do arquivo.
Saída:     sem retorno.
--------------------------------------------------------------------------------*/
void externalPartition(int left, int right, FILE **bottomRead, FILE **topRead, FILE **bottomWrite, FILE **topWrite, Buffer *buffer, int *i, int *j);


/*------------------------------------------------------------------------------
Função:    traz um registro do arquivo para a memória e grava o maior ou o menor
           registro do  buffer no arquivo. A escolha de gravação/leitura é feita
           com base na utilização dos ponteiros inferior e superior, de forma  a
           balancear o acesso ao arquivo.
Entrada:   ponteiro de escrita, podendo  ser inferior ou superior, de acordo com
           a utilização desses ponteiros. Recebe  também dois inteiros, os quais
           indicam a posição do buffer a ser substituída e a posição do  arquivo
           onde  será gravado o registro do buffer. Recebe também um ponteiro do
           registro do arquivo que será gravado no buffer.
Saída:     sem retorno.
-------------------------------------------------------------------------------*/
void swapRegisterBuffer(FILE **writeFile, int pos, Register *currentReg, Buffer *buffer, int *posWrite);


/*-------------------------------------------------------------------------------
Função:    lê um registro do arquivo utilizando o ponteiro de leitura superior.
Entrada:   ponteiro de leitura superior, inteiro contendo a posição de leitura, 
           variável do tipo Register que armazenará os dados da leitura e um 
           ponteiro para um inteiro, responsável por gerenciar o balanceamento de 
           leitura dos ponteiros inferior e superior.
Saída:     sem retorno.
--------------------------------------------------------------------------------*/
void readTop(FILE **file, int *pos, Register *reg, int *alternateLeftRight);



/*-------------------------------------------------------------------------------
Função:    lê um registro do arquivo utilizando o ponteiro de leitura inferior.
Entrada:   ponteiro  de leitura inferior, inteiro  contendo a posição de  leitura, 
           variável do  tipo Register  que armazenará  os dados  da leitura e  um 
           ponteiro para um inteiro, responsável por gerenciar o balanceamento de 
           leitura dos ponteiros inferior e superior.
Saída:     sem retorno.
--------------------------------------------------------------------------------*/
void readBottom(FILE **file, int *pos, Register *reg, int *alternateLeftRight);


/*---------------------------------------------------------------------------------
Função:    escreve um registro no arquivo utilizando o ponteiro de escrita superior.
Entrada:   ponteiro de  escrita  superior, inteiro  contendo  a posição de  escrita, 
           variável  do tipo  Register  que contém os  dados a serem  escritos e um 
           ponteiro para um inteiro, responsável  por gerenciar o  balanceamento de 
           escrita dos ponteiros inferior e superior.
Saída:     sem retorno.
--------------------------------------------------------------------------------*/
void writeMax(FILE **topFile, Register *reg, int *posTopWrite);

/*---------------------------------------------------------------------------------
Função:    escreve um registro no arquivo utilizando o ponteiro de escrita inferior.
Entrada:   ponteiro  de escrita  inferior, inteiro  contendo a  posição de  escrita, 
           variável do  tipo Register  que contém  os dados  a serem escritos e  um 
           ponteiro para um  inteiro, responsável por gerenciar o  balanceamento de 
           escrita dos ponteiros inferior e superior.
Saída:     sem retorno.
--------------------------------------------------------------------------------*/
void writeMin(FILE **bottomFile, Register *reg, int *posBottomWrite);

/*--------------------------------------------------------------------------------
Função:    lê registros do arquivo e preenche os registros do buffer, limitando-se
           à capacidade do buffer.
Entrada:   ponteiros de  leitura inferior e superior, para  balancear a leitura no
           arquivo, ponteiro  para  um  inteiro, responsável  por  controlar  esse 
           balanceamento, e dois inteiros que fornecem as posições de escrita para
           os ponteiros de escrita inferior e superior.
Saída:     sem retorno.
--------------------------------------------------------------------------------*/
void fillBuffer(FILE **bottomFile, FILE **topFile, Buffer *buffer, int *altRead, int *posBottom, int *posTop);

#endif

