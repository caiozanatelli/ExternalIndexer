#include "Register.h"
#include <string.h>
#include <stdio.h>

// Implementa um operador para comparação de registros
int compareRegisters(Register *regA, Register *regB) {
	int cmp = strcmp(regA->word, regB->word);

	// Se as palavras forem iguais, identifica o menor registro
	// com base nos outros critérios (documento e posição)
	if (cmp == 0) {
		if (regA->document != regB->document) {
			return (regA->document < regB->document) ? -1 : 1;
		}
		else {
			return (regA->position < regB->position) ? -1 : 1;
		}
	}

	// Se as palavras não forem iguais, retorna a ordem correta
	return (cmp < 0) ? -1 : 1;
}

// Inicializa um novo registro
void newRegister(Register *reg) {
	memset(reg->word, 0, sizeof(reg->word));
	reg->word[MAX_SIZE_WORD - 1] = '\0';
	reg->document = 0;
	reg->frequency = 0;
	reg->position = 0;
}