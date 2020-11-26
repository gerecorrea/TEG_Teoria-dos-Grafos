# include "estruturasdedados.h"

#ifndef INTERFACE_H_INCLUDED
#define INTERFACE_H_INCLUDED

    // Defines



// Declaração de funções

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
    /* OBJETIVO: essa função gera um vetor que contém os rótulos dos vértices do grafo na mesma ordem em que os vértices
    tiveram seus vértices adjacentes listados no arquivo de entrada.
    RETORNO: 1, caso a função seja bem-sucedida; 0, caso contrário.
    PARÂMETROS:
    1) FILE *ptr: ponteiro para manipular o arquivo de entrada, que deve conter o grafo.
    2) int **V: endereço de memória de um ponteiro para vetor. Esse ponteiro servirá para manipular o vetor, produzido durante
    a execução da função, que conterá os rótulos dos vértices do grafo.
    */

    /// int grafoComplementarAdj (FILE *ptr, int ***matrizComplemento);
    /* OBJETIVO: essa função gera a matriz de adjacência do grafo complementar ao grafo representado no arquio de entrada.
    RETORNO: 1, caso a função seja bem-sucedida; 0, caso contrário.
    PARÂMETROS:
    1) FILE *ptr: ponteiro para manipular o arquivo de entrada, que deve conter o grafo.
    2) int ***matrizComplemento: é o endereço de memória de um ponteiro para ponteiro para inteiros. Esse ponteiro para ponteiro
    servirá, ao término da execução da função, para manipular a matriz de adjacência gerada.
    */

    /// int grafoComplementarArq (FILE *ptr);
    /* OBJETIVO: essa função produz um arquivo representando o grafo complementar àquele representado no arquivo de entrada.
    O arquivo produzido estará na pasta padrão do programa com o nome 'Grafo_Complementar.txt'.
    RETORNO: 1, caso a função seja bem-sucedida; 0, caso contrário.
    PARÂMETROS:
    1) FILE *ptr: ponteiro para manipular o arquivo de entrada, que deve conter o grafo.
    */

    /// int gerarVetorAdj (FILE *ptr, int **vetorGraus, int **vetorAdj);
    /* OBJETIVO: essa função gera o vetor de adjacência de um grafo para que ele possa ser utilizado como se queira.
    RETORNO: 1, caso a função seja bem-sucedida; 0, caso contrário.
    PARÂMETROS:
    1) FILE *ptr: ponteiro para manipular o arquivo de entrada, que deve conter o grafo.
    2) int **vetorGraus: endereço de memória de um ponteiro para um vetor. Esse vetor, a ser produzido durante a
    execução da função, conterá os graus dos vértices do grafo.
    3) int **vetorAdj: endereço de memória de um ponteiro para um vetor. Esse vetor, igualmente produzido durante
    a execução da função, conterá os vértices adjacentes a cada um dos vértices do grafo.
    */

    /// void imprimirVetorAdj (FILE *ptr, int *vetorGraus, int *vetorAdj);
    /* OBJETIVO: essa função imprime o vetor de adjacência de um grafo.
    RETORNO: nenhum.
    PARÂMETROS:
    1) FILE *ptr: ponteiro para manipular o arquivo de entrada, que deve conter o grafo.
    2) int *vetorGraus: é o endereço de memória de um vetor que contenha os graus dos vértices do grafo.
    3) int *vetorAdj: é o endereço de memória de um vetor que contenha os vértices adjacentes de cada um dos vértices do grafo.
    */

    /// int somaGrausVertices (int **vetorGraus, int numVertices);
    /* OBJETIVO: essa função é apenas uma função de apoio para outras funções. Ela realiza a soma dos graus dos vértices do
    grafo.
    RETORNO: um número inteiro correspondente à soma dos graus dos vértices do grafo.
    PARÂMETROS:
    1) int **vetorGraus: é o endereço de memória do ponteiro do vetor que armazena os valores dos graus de cada um dos
    vértices.
    2) int numVertices: corresponde ao número de vértices do grafo.
    */

#endif // INTERFACE_H_INCLUDED
