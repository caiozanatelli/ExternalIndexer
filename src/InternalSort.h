#ifndef INTERNAL_SORT_H
#define INTERNAL_SORT_H

#include "Register.h"

/*--------------------------------------------------------------------------------
 Função:    ordena um vetor utilizando o algoritmo de ordenação interna Insertion
            Sort.
 Entrada:   vetor do tipo Register, o qual será ordenado, e seu tamanho.
 Saída:     sem retorno.
--------------------------------------------------------------------------------*/
void insertionSort(Register *array, int size);


/*--------------------------------------------------------------------------------
 Função:    ordena um vetor utilizando o algoritmo de ordenação interna QuickSort.
 Entrada:   vetor do tipo Register, o qual será ordenado, e as posições de início
            e fim da partição atual.
 Saída:     sem retorno.
--------------------------------------------------------------------------------*/
void internalQuickSort(Register *array, int left, int right);


/*---------------------------------------------------------------------------------
 Função:    faz o particionamento do vetor para as chamadas recursivas de ordenação
            do QuickSort.
 Entrada:   vetor do tipo Register, o qual será ordenado, e suas posições de início
            e fim referentes à partição atual.
 Saída:     inteiro sinalizando o divisor das partições criadas.
---------------------------------------------------------------------------------*/
int internalQuickSortPartition(Register *array, int left, int right);


/*---------------------------------------------------------------------------------
 Função:    função auxiliar responsável por trocar o conteúdo de dois registros.
 Entrada:   duas variávels do tipo Register, as quais terão seus conteúdos trocados.
 Saída:     sem retorno.
---------------------------------------------------------------------------------*/
void swap(Register *regA, Register *regB);

#endif

