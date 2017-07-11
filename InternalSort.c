#include "InternalSort.h"
#include "Register.h"

// Implementação do Insertion Sort
void insertionSort(Register *array, int size) {
	Register currentReg;
	int i, j;

	for (i = 1; i < size; i++) {
		currentReg = array[i];
		j = i - 1;

		while (j >= 0 && compareRegisters(&currentReg, &array[j]) < 0) {
			array[j + 1] = array[j];
			j--;
		}
		array[j + 1] = currentReg;
	}
}

// Função principal do QuickSort interno. Ordena as partições recursivamente
void internalQuickSort(Register *array, int left, int right) {
	if (left < right) {
		int p = internalQuickSortPartition(array, left, right);
		internalQuickSort(array, left, p - 1);
		internalQuickSort(array, p + 1, right);
	}
}

// Faz o particionamento e ordena as partições nos padrões do QuickSort
int internalQuickSortPartition(Register *array, int left, int right) {
	int i, j;
	i = left - 1;

	swap(&array[(left + right) / 2], &array[right]);

	for (j = left; j < right; j++) {
		if (compareRegisters(&array[j], &array[right]) <= 0) {
			i++;
			swap(&array[i], &array[j]);
		}
	}
	swap(&array[right], &array[i + 1]);

	return i + 1;
}

// Troca o conteúdo de dois registros
void swap(Register *regA, Register *regB) {
	Register temp = *regA;
	*regA = *regB;
	*regB = temp;
}