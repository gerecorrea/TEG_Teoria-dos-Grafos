# include "estruturasdedados.h"

#ifndef INTERFACE_H_INCLUDED
#define INTERFACE_H_INCLUDED

    // Defines



// Declara��o de fun��es

    void verArquivo (FILE *ptr);
    int gerarMatrizAdj (FILE *ptr, int ***matriz);
    void imprimirMatrizAdj (FILE *ptr, int **matriz);
    int gerarMatrizIncid (FILE *ptr, int ***matriz, int tipoGrafo);
    void imprimirMatrizIncid (FILE *ptr, int **matriz, int tipoGrafo);
    int qtdeVertices (FILE *ptr);
    int qtdeArestas (FILE *ptr, int tipoGrafo);
    int arestasParalelas (FILE *ptr);
    int grauVertice (FILE *ptr, int vertice);
    int grauEntradaVertice (FILE *ptr, int vertice);
    int grauSaidaVertice (FILE *ptr, int vertice);
    void grauTodos (FILE *ptr, int **vetorGrau, int tipoGrafo);
    void grauTodosCompleto (FILE *ptr, int **vetorGrauEntrada, int **vetorGrauSaida, int **vetorGrau);
    void grauEntradaTodos (FILE *ptr, int **vetorGrauEntrada);
    void grauSaidaTodos (FILE *ptr, int **vetorGrauSaida);
    int inserirVertice (FILE *ptr);
    int removerVertice (FILE *ptr, int vertRemover);
    int inserirAresta (FILE *ptr, int vertice1, int vertice2, int tipoGrafo);
    int removerAresta (FILE *ptr, int vertice1, int vertice2, int tipoGrafo);
    int gerarListaAdj (FILE *ptr, LDDE **lista, int tipoGrafo);
    int gerarListaSucessores (FILE *ptr, LDDE **lista);
    void imprimirMultilista (FILE *ptr, LDDE *lista);
    void imprimirLDDE (LDDE *lista);
    void imprimirFDDE (FDDE *fila);
    int qtdeComponentes (FILE *ptr);
    int grafoEuleriano (FILE *ptr, int tipoGrafo);
    int buscaEmProfundidade (FILE *ptr, int **tempoEntrada, int **tempoSaida, int **pais, LDDE **arestas);
    int procBFS (FILE *ptr, int vertAtual, int *tempoFornecido, int **tempoEntrada, int **tempoSaida, int **pais, LDDE **arestas);
    void imprimirResultadosBFS (FILE *ptr, int **tempoEntrada, int **tempoSaida, int **pais, LDDE **arestas);
    int grafoDirecionado (FILE *ptr);
    int gerarVetorAdj (FILE *ptr, int **vetorGraus, int **vetorAdj, int tipoGrafo);
    void imprimirVetorAdj (FILE *ptr, int *vetorGraus, int *vetorAdj);
    int somaGrausVertices (int **vetorGraus, int numVertices);
    int grafoComplementarArq (FILE *ptr);
    int grafoComplementarAdj (FILE *ptr, int ***matrizComplemento);
    int rotulosVertices (FILE *ptr, int **V);
    int gerarListaArestas (FILE *ptr, LDDE **lista, int tipoGrafo);
    void imprimirListaArestas (LDDE *listaArestas);
    int fechoDireto (FILE *ptr, LDDE** lista);
    int removerSentidos (FILE *ptr);
    int matAdjParaArq (int ***matrizAdjacencia, int dimensao, int **vetorRotulos);
    int posicaoVertice (int **rotulos, int qtdeVertices, int vertice);
    int posicaoVerticeArq (FILE *ptr, int vertice);


    /// int rotulosVertices (FILE *ptr, int **V);
    /* OBJETIVO: essa fun��o gera um vetor que cont�m os r�tulos dos v�rtices do grafo na mesma ordem em que os v�rtices
    tiveram seus v�rtices adjacentes listados no arquivo de entrada.
    RETORNO: 1, caso a fun��o seja bem-sucedida; 0, caso contr�rio.
    PAR�METROS:
    1) FILE *ptr: ponteiro para manipular o arquivo de entrada, que deve conter o grafo.
    2) int **V: endere�o de mem�ria de um ponteiro para vetor. Esse ponteiro servir� para manipular o vetor, produzido durante
    a execu��o da fun��o, que conter� os r�tulos dos v�rtices do grafo.
    */

    /// int grafoComplementarAdj (FILE *ptr, int ***matrizComplemento);
    /* OBJETIVO: essa fun��o gera a matriz de adjac�ncia do grafo complementar ao grafo representado no arquio de entrada.
    RETORNO: 1, caso a fun��o seja bem-sucedida; 0, caso contr�rio.
    PAR�METROS:
    1) FILE *ptr: ponteiro para manipular o arquivo de entrada, que deve conter o grafo.
    2) int ***matrizComplemento: � o endere�o de mem�ria de um ponteiro para ponteiro para inteiros. Esse ponteiro para ponteiro
    servir�, ao t�rmino da execu��o da fun��o, para manipular a matriz de adjac�ncia gerada.
    */

    /// int grafoComplementarArq (FILE *ptr);
    /* OBJETIVO: essa fun��o produz um arquivo representando o grafo complementar �quele representado no arquivo de entrada.
    O arquivo produzido estar� na pasta padr�o do programa com o nome 'Grafo_Complementar.txt'.
    RETORNO: 1, caso a fun��o seja bem-sucedida; 0, caso contr�rio.
    PAR�METROS:
    1) FILE *ptr: ponteiro para manipular o arquivo de entrada, que deve conter o grafo.
    */

    /// int gerarVetorAdj (FILE *ptr, int **vetorGraus, int **vetorAdj);
    /* OBJETIVO: essa fun��o gera o vetor de adjac�ncia de um grafo para que ele possa ser utilizado como se queira.
    RETORNO: 1, caso a fun��o seja bem-sucedida; 0, caso contr�rio.
    PAR�METROS:
    1) FILE *ptr: ponteiro para manipular o arquivo de entrada, que deve conter o grafo.
    2) int **vetorGraus: endere�o de mem�ria de um ponteiro para um vetor. Esse vetor, a ser produzido durante a
    execu��o da fun��o, conter� os graus dos v�rtices do grafo.
    3) int **vetorAdj: endere�o de mem�ria de um ponteiro para um vetor. Esse vetor, igualmente produzido durante
    a execu��o da fun��o, conter� os v�rtices adjacentes a cada um dos v�rtices do grafo.
    */

    /// void imprimirVetorAdj (FILE *ptr, int *vetorGraus, int *vetorAdj);
    /* OBJETIVO: essa fun��o imprime o vetor de adjac�ncia de um grafo.
    RETORNO: nenhum.
    PAR�METROS:
    1) FILE *ptr: ponteiro para manipular o arquivo de entrada, que deve conter o grafo.
    2) int *vetorGraus: � o endere�o de mem�ria de um vetor que contenha os graus dos v�rtices do grafo.
    3) int *vetorAdj: � o endere�o de mem�ria de um vetor que contenha os v�rtices adjacentes de cada um dos v�rtices do grafo.
    */

    /// int somaGrausVertices (int **vetorGraus, int numVertices);
    /* OBJETIVO: essa fun��o � apenas uma fun��o de apoio para outras fun��es. Ela realiza a soma dos graus dos v�rtices do
    grafo.
    RETORNO: um n�mero inteiro correspondente � soma dos graus dos v�rtices do grafo.
    PAR�METROS:
    1) int **vetorGraus: � o endere�o de mem�ria do ponteiro do vetor que armazena os valores dos graus de cada um dos
    v�rtices.
    2) int numVertices: corresponde ao n�mero de v�rtices do grafo.
    */

#endif // INTERFACE_H_INCLUDED
