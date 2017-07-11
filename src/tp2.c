////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                   UNIVERSIDADE FEDERAL DE MINAS GERAIS                     //
//                                                                            //
// Trabalho Prático 2 - Algoritmos e Estruturas de Dados III                  //
//                                                                            //
// Nome:        Caio Felipe Zanatelli                                         //
// Matrícula:   2016006310                                                    //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#include "InvertedIndex.h"
#include "Register.h"
#include <stdlib.h>
#include <stdio.h>

int main() {
	char dirInput[MAX_SIZE_DIR];
	char dirOutput[MAX_SIZE_DIR];
	int numDocs, maxMemory;

	scanf("%d %d %s %s", &numDocs, &maxMemory, dirInput, dirOutput);
	createInvertedIndex(numDocs, maxMemory, dirInput, dirOutput);
	
	return 0;
}

