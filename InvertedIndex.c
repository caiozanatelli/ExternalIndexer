#include "InvertedIndex.h"
#include "ExternalSort.h"
#include "Register.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Função acessada pelo usuário para criação do índice invertido
void createInvertedIndex(int numDocs, int maxMem,  char *inputDir, char *outputDir) {
	int numRegs = mergeInitialFiles(numDocs, inputDir);
	externalSort(INITIAL_FILE_DIR, maxMem, numRegs);
	createFrequenciesFile(outputDir);
}

// Une os documentos da coleção em um único arquivo binário
int mergeInitialFiles(int numDocs, char *inputDir) {
	FILE *out = fopen(INITIAL_FILE_DIR, "wb");
	if(!out) { 
		printf("Erro. Arquivo inexistente\n");
		exit(1);
	}

	char inFileDir[MAX_SIZE_DIR];
	FILE *in;
	Register reg;
	int i, numRegs = 0;

	// Abre os arquivos da coleção
	for (i = 1; i <= numDocs; i++) {
		sprintf(inFileDir, "%s%d", inputDir, i);
		in = fopen(inFileDir, "r");
		if(!in) { 
			printf("Erro. Arquivo inexistente\n");
			exit(1);
		}
		
		// Inicializa um registro
		newRegister(&reg);
		reg.document = i;
		reg.frequency = 1;

		// Enquanto existir palavra no documento i, grava no arquivo binário
		while (fscanf(in, "%s", reg.word) == 1) {
			reg.position = ftell(in) - strlen(reg.word);
			fwrite(&reg, sizeof(reg), 1, out);
			numRegs++;
		}
		fclose(in);
	}
	
	fclose(out);

	return numRegs;
}

// Atualiza a frequência de uma ocorrência gravando diretamente no arquivo final (índice invertido)
void fillWordOcurrence(FILE *in, FILE *out, long int posFirstOcurr, long int posCurrentOcurr, Register *reg) {
	fseek(in, posFirstOcurr, SEEK_SET);
	int i;
	int frequency = reg->frequency;
	Register auxReg;

	// Encontra todas as ocorrências e grava no arquivo, já atualizando a frequência
	for (i = 0; i < frequency; i++) {
		fread(&auxReg, sizeof(Register), 1, in);
		auxReg.frequency = frequency;
		fprintf(out, "%s,%d,%d,%d\n", auxReg.word, auxReg.document, auxReg.frequency, auxReg.position);
	}

	fseek(in, posCurrentOcurr, SEEK_SET);
}

// Com o arquivo ordenado, o índice invertido é gerado já com as frequências atualizadas
void createFrequenciesFile(char *outputDir) {
	char outFileDir[MAX_SIZE_DIR];
	sprintf(outFileDir, "%s%s", outputDir, FINAL_FILE_NAME);

	FILE *in = fopen(INITIAL_FILE_DIR, "rb");
	FILE *out = fopen(outFileDir, "w");

	Register reg, auxReg;
	int isNewWord = 1;

	long int pointerFirstOcurrence;
	long int pointerCurrentOcurrence;

	// Enquanto existir registros para ler
	while (fread(&reg, sizeof(Register), 1, in) == 1) {
		// Identifica que uma ocorrência iniciou
		if (isNewWord) {
			auxReg = reg;
			isNewWord = 0;
			pointerFirstOcurrence = ftell(in) - sizeof(Register);
		}
		// Contabiliza a frequência da ocorrência iniciada
		else if (strcmp(reg.word, auxReg.word) == 0 && reg.document == auxReg.document) {
			auxReg.frequency++;
		}
		// Se a repetição do registro terminou, atualiza a frequência diretamente no índice invertido
		else {
			pointerCurrentOcurrence = ftell(in);
			fillWordOcurrence(in, out, pointerFirstOcurrence, pointerCurrentOcurrence, &auxReg);
			pointerFirstOcurrence = ftell(in) - sizeof(Register);
			auxReg = reg;
		}
	}

	// Atualiza o índice invertido para os registros remanescentes
	if (!isNewWord) {
		fillWordOcurrence(in, out, pointerFirstOcurrence, pointerCurrentOcurrence, &auxReg);
	}

	fclose(in);
	fclose(out);
}
