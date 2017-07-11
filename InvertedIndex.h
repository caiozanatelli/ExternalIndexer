#ifndef INVERTED_INDEX_H
#define INVERTED_INDEX_H

// Configurações do módulo
#define MAX_SIZE_DIR            255
#define INITIAL_FILE_DIR        "./tmp/initial_file"
#define FINAL_FILE_NAME         "index"

/*---------------------------------------------------------------------------------
 Função:    função  acessada pelo usuário para a criação de um índice invertido no
            modelo proposto pelo trabalho.
 Entrada:   dois inteiros, indicando número de documentos presentes na coleção e a
            quantidade, em bytes, de memória  principal disponível para utilização.
            Recebe também o diretório de documentos da coleção e o diretório  onde
            o índice invertido deverá ser gravado.
 Saída:     sem retorno.
----------------------------------------------------------------------------------*/
void createInvertedIndex(int numDocs, int maxMem,  char *inputDir, char *outputDir);


/*---------------------------------------------------------------------------------
 Função:    lê os documentos da coleção e gera um único arquivo binário com a união
            do conteúdo de todos os arquivos, os quais são armazenados em blocos de
            32 bytes através do tipo Register.
 Entrada:   inteiro indicando o número de documentos da coleção e o diretório  onde
            esses arquivos estão localizados.
 Saída:     retorna o  número  de  registros  lidos, informação  necessária para  a 
            ordenação efetuada pelo QuickSort Externo.
----------------------------------------------------------------------------------*/
int mergeInitialFiles(int numDocs, char *inputDir);


/*--------------------------------------------------------------------------------
 Função:    cria o arquivo final  contendo o índice  invertido. Essa função  faz a 
            atualização  da frequência de  cada ocorrência de  palavras da coleção
            de  documentos, através do  arquivo binário  ordenado que contém  tais
            registros, gerando  um arquivo  texto com o índice invertido no fim do
            processo.
 Entrada:   diretório onde está localizado o arquivo binário ordenado que contém os
            registros de ocorrências de palavras da coleção de documentos.
 Saída:     sem retorno.
----------------------------------------------------------------------------------*/
void createFrequenciesFile(char *outputDir);


#endif

