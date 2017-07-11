#ifndef REGISTER_H
#define REGISTER_H

#define	MAX_SIZE_WORD	20

// Estrutura que define um registro nos padrões <w, d, f, p>
typedef struct {
	char word[MAX_SIZE_WORD];
	int document;
	int frequency;
	int position;
} Register;

/*------------------------------------------------------------------------------
 Função:	compara dois registros, tendo como primeiro critério a palavra, e em
			seguida os campos documento e posição, respectivamente.
 Entrada:	os dois registros a serem comparados.
 Saída:		-1, se regA < reg; 0, se regA = regB e 1, se regA > regB.
------------------------------------------------------------------------------*/
int compareRegisters(Register *regA, Register *regB);


/*------------------------------------------------------------------------------
 Função:	inicializa os campos de um novo registro.
 Entrada:	o registro a ser inicializado.
 Saída:		sem retorno.
------------------------------------------------------------------------------*/
void newRegister(Register *reg);

#endif

