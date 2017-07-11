#include "ExternalSort.h"
#include "InternalSort.h"
#include "Register.h"
#include <stdlib.h>
#include <string.h>

// Inicializa o buffer e aloca memória disponível
void initBuffer(Buffer *buffer, int maxMemory) {
	buffer->capacity = maxMemory / sizeof(Register);
	buffer->size = 0;
	buffer->data = (Register*) calloc(buffer->capacity, sizeof(Register));
}

// Libera memória utilizada pelo buffer
void freeBuffer(Buffer *buffer) {
	free(buffer->data);
}

// Chamada do algoritmo QuickSort Externo para a ordenação de um arquivo
void externalSort(char *inputFileDir, int maxMemory, int numRegs) {
	// Inicializa ponteiros de leitura/escrita inferior e superior
	FILE *bottomRead  = fopen(inputFileDir, "r+b"); if(!bottomRead)  { printf("Erro. Arquivo inexistente\n"); exit(1);}
	FILE *topRead 	  = fopen(inputFileDir, "r+b"); if(!topRead)     { printf("Erro. Arquivo inexistente\n"); exit(1);}
	FILE *bottomWrite = fopen(inputFileDir, "r+b"); if(!bottomWrite) { printf("Erro. Arquivo inexistente\n"); exit(1);}
	FILE *topWrite    = fopen(inputFileDir, "r+b"); if(!topWrite)    { printf("Erro. Arquivo inexistente\n"); exit(1);}

	// Aloca memória interna para a ordenação
	Buffer buffer;
	initBuffer(&buffer, maxMemory);

	// Chamada do Quicksort externo
	externalQuicksort(numRegs - 1, 0, &bottomRead, &topRead, &bottomWrite, &topWrite, &buffer);

	// Fecha os arquivos utilizados
	fclose(bottomRead);
	fclose(topRead);
	fclose(bottomWrite);
	fclose(topWrite);

	// Desaloca a memória utilizada pelo buffer
	freeBuffer(&buffer);
}

// Método com chamadas recursivas para a ordenação das partições esquerda e direita do QuickSort Externo
void externalQuicksort(int right, int left, FILE **bottomRead, FILE **topRead, FILE **bottomWrite, FILE **topWrite, Buffer *buffer) {
	int i, j;

	// Se for uma partição inválida
	if (right - left < 1) return;

	// A partição atual é ordenada
	externalPartition(left, right, bottomRead, topRead, bottomWrite, topWrite, buffer, &i, &j);

	// Chamadas recursivas para as partições da direita e da esquerda
	externalQuicksort(i, left, bottomRead, topRead, bottomWrite, topWrite, buffer);
	externalQuicksort(right, j, bottomRead, topRead, bottomWrite, topWrite, buffer);
}

// Lẽ um registro do arquivo utilizando o ponteiro de leitura superior
void readTop(FILE **file, int *pos, Register *reg, int *alternateLeftRight) {
	newRegister(reg);
	fseek(*file, *pos * sizeof(Register), SEEK_SET);
	fread(reg, sizeof(Register), 1, *file);
	*pos = *pos - 1;
	*alternateLeftRight = BOTTOM_ID;
}

// Lê um registro do arquivo utilizando o ponteiro de leitura inferior
void readBottom(FILE **file, int *pos, Register *reg, int *alternateLeftRight) {
	newRegister(reg);
	fread(reg, sizeof(Register), 1, *file);
	*pos = *pos + 1;
	*alternateLeftRight = TOP_ID;
}

// Grava um registro no arquivo utilizando o ponteiro de escrita superior
void writeMax(FILE **topFile, Register *reg, int *posTopWrite) {
	fseek(*topFile, *posTopWrite * sizeof(Register), SEEK_SET);
	fwrite(reg, sizeof(Register), 1, *topFile);
	*posTopWrite = *posTopWrite - 1;
}

// Grava um registro no arquivo utilizando o ponteiro de escrita inferior
void writeMin(FILE **bottomFile, Register *reg, int *posBottomWrite) {
	fwrite(reg, sizeof(Register), 1, *bottomFile);
	*posBottomWrite = *posBottomWrite + 1;
}

// Preenche buffer com registros do arquivo
void fillBuffer(FILE **bottomFile, FILE **topFile, Buffer *buffer, int *altRead, int *posBottom, int *posTop) {
	// Enquanto exiter espaço disponível no buffer (memória) e registros para serem lidos
	while (buffer->size < buffer->capacity && *posTop >= *posBottom) {
		// Lê alternadamente registro de cima e de baixo
		if (*altRead == BOTTOM_ID) {
			readBottom(bottomFile, posBottom, &buffer->data[buffer->size], altRead);
		}
		else {
			readTop(topFile, posTop, &buffer->data[buffer->size], altRead);
		}
		buffer->size++;
	}
}

// Faz o swap de um registro do buffer por um registro do arquivo
void swapRegisterBuffer(FILE **writeFile, int pos, Register *currentReg, Buffer *buffer, int *posWrite) {
	// Escreve o mínimo ou o máximo
	if (pos == BOTTOM_ID) {
		writeMin(writeFile, &buffer->data[pos], posWrite);
	}
	else {
		writeMax(writeFile, &buffer->data[pos], posWrite);
	}

	// Substitui o registro de menor valor (do buffer) pelo registro que está sendo lido atualmente
	buffer->data[pos] = *currentReg;
}

// Faz o particionamento do QuickSort Externo
void externalPartition(int left, int right, FILE **bottomRead, FILE **topRead, FILE **bottomWrite, FILE **topWrite, Buffer *buffer, int *i, int *j) {
	// Ajuste de variáveis para caminhamento nos arquivos, de acordo com leitura e escrita
	int posBottomRead = left;
	int posTopRead = right;
	int posBottomWrite = left;
	int posTopWrite = right;

	// Identifica quantos registros estão presentes no buffer (memória)
	buffer->size = 0;

	// Ajusta os ponteiros inferiores do arquivo para a posição correta
	fseek(*bottomWrite, posBottomWrite * sizeof(Register), SEEK_SET);
	fseek(*bottomRead, posBottomRead * sizeof(Register), SEEK_SET);

	int alternateLeftRight = BOTTOM_ID;
	Register currentReg;

	// Ajusta os ponteiros para caso não seja criada uma nova partição
	*i = left - 1;
	*j = right + 1;

	// Preenche o buffer e ordena seus registros
	fillBuffer(bottomRead, topRead, buffer, &alternateLeftRight, &posBottomRead, &posTopRead);
	internalQuickSort(buffer->data, 0, buffer->size - 1);

	// Enquanto existir registro para ser lido
	while (posTopRead >= posBottomRead) {
		newRegister(&currentReg);

		// Faz a leitura do próximo registro, evitando a sobrescrita de registros
		if (posTopRead == posTopWrite) {
			readTop(topRead, &posTopRead, &currentReg, &alternateLeftRight);
		}
		else if (posBottomRead == posBottomWrite) {
			readBottom(bottomRead, &posBottomRead, &currentReg, &alternateLeftRight);
		}
		else if (alternateLeftRight == BOTTOM_ID) {
			readBottom(bottomRead, &posBottomRead, &currentReg, &alternateLeftRight);
		}
		else {
			readTop(topRead, &posTopRead, &currentReg, &alternateLeftRight);
		}

		// Se o registro vem antes do mínimo presente no buffer
		if (compareRegisters(&currentReg, &buffer->data[0]) < 0) {
			// Sinaliza uma partição e escreve o mínimo no arquivo
			*i = posBottomWrite;
			writeMin(bottomWrite, &currentReg, &posBottomWrite);
		}
		// Se o registro vem depois do máximo presente no buffer
		else if (compareRegisters(&currentReg, &buffer->data[buffer->size - 1]) > 0) {
			*j = posTopWrite;
			writeMax(topWrite, &currentReg, &posTopWrite);
		}
		// Se o registro vem entre o mínimo e o máximo presente no buffer
		else {

			// Se o apontador de escrita superior andou mais até o momento
			if (posBottomWrite - left < right - posTopWrite) {
				swapRegisterBuffer(bottomWrite, 0, &currentReg, buffer, &posBottomWrite);
			}
			// Se o apontador de escrita inferior andou mais até o momento
			else {
				swapRegisterBuffer(topWrite, buffer->size - 1, &currentReg, buffer, &posTopWrite);
			}

			// Ordena o buffer novamente, pois registros foram trocados na memória
			insertionSort(buffer->data, buffer->size);
		}
	}

	int k;

	// Descarrega o restante do buffer no arquivo
	for (k = 0; k < buffer->size; k++) {
		writeMin(bottomWrite, &buffer->data[k], &posBottomWrite);
	}

	// Atualiza os arquivos
	fflush(*bottomRead);
	fflush(*topRead);
	fflush(*bottomWrite);
	fflush(*topWrite);
}
