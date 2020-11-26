# include <stdio.h>
# include <stdlib.h>
# include "Protótipos_Funções.h"
# include "estruturasdedados.h"
# include "funcoes_menu.h"

    // FUNÇÕES IMPLEMENTADAS

    struct aresta {
        int rotulo;
        int extr1;
        int extr2;
        float atributo;
    };
    typedef struct aresta aresta;

    /// ****************************************************************************************************

    int gerarListaArestas (FILE *ptr, LDDE **lista, int tipoGrafo) {

        // Declaração de variáveis
        char c;
        int vertAtual;
        int vertLido;
        LDDE *listaArestas;
        int ret;
        aresta arestaParaInserir;
        int rotuloAresta = 0;

        // Instruções

        // Criando a lista de arestas
        ret = criarLDDE (&listaArestas, sizeof (aresta));
        if (ret == FRACASSO) {
            return (FRACASSO);
        }

        // Lendo o arquivo de entrada e cadastrando as arestas
        rewind (ptr);
        while (!feof (ptr)) {
            fscanf (ptr, "%d", &vertAtual);
            c = fgetc (ptr);
            arestaParaInserir.extr1 = vertAtual;
            while ((c != '\n') && (c != EOF)) {
                fscanf (ptr, "%d", &vertLido);
                arestaParaInserir.extr2 = vertLido;
                c = fgetc (ptr);
                if (tipoGrafo == NAODIRECIONADO) {
                    if (vertAtual <= vertLido) {
                        arestaParaInserir.rotulo = rotuloAresta;
                        rotuloAresta++;
                        arestaParaInserir.atributo = 0;
                        ret = inserirFimLDDE (listaArestas, &arestaParaInserir);
                        if (ret == FRACASSO) {
                            return (FRACASSO);
                        }
                    }
                }
                else {
                    arestaParaInserir.rotulo = rotuloAresta;
                    rotuloAresta++;
                    arestaParaInserir.atributo = 0;
                    ret = inserirFimLDDE (listaArestas, &arestaParaInserir);
                    if (ret == FRACASSO) {
                        return (FRACASSO);
                    }
                }
            }
        }
        *lista = listaArestas;
        return (SUCESSO);
    }

    /// ****************************************************************************************************

    void imprimirListaArestas (LDDE *listaArestas) {

        // Declaração de variáveis
        int arestas;
        int i;
        aresta arestaAtual;
        int ret;

        // Instruções

        // Obtendo a quantidade de arestas
        arestas = tamanhoLDDE (listaArestas);

        for (i=0; i<=arestas-1; i++) {
            ret = buscarPosLogLDDE(listaArestas, &arestaAtual, i);
            if (ret == 0) {
                printf ("Falha na impressao.\n");
                return;
            }
            printf ("%d\t%d\t%d\t%g\n", arestaAtual.rotulo, arestaAtual.extr1, arestaAtual.extr2, arestaAtual.atributo);
        }
    }

    /// ****************************************************************************************************

    void verArquivo (FILE *ptr) {

        // Declaração de variáveis
        char c;

        // Instruções

        while (!feof (ptr)) {
            c = fgetc (ptr);
            while ((c != '\t') && (c != EOF)) {
                printf ("%c", c);
                c = fgetc (ptr);
            }
            printf (":\t");
            while ((c != '\n') && (c != EOF)) {
                c = fgetc (ptr);
                printf ("%c", c);
            }
        }
        printf ("\n");
    }

    /// ****************************************************************************************************

    int grafoDirecionado (FILE *ptr) {

        // Declaração de variáveis
        int **matrizAdj;
        int vertices;
        int i, j;
        int tipoGrafo;

        // Instruções

        vertices = qtdeVertices (ptr);
        gerarMatrizAdj (ptr, &matrizAdj);
        for (i=0; i<=vertices-1; i++) {
            for (j=0; j<=i; j++) {
                if (matrizAdj[i][j] != matrizAdj [j][i]) {
                    printf ("INFORMACAO: o grafo fornecido e direcionado.\n");
                    return (DIRECIONADO);
                }
            }
        }
        printf ("INFORMACAO: nao e possivel afirmar se o grafo e direcionado ou nao. \nInforme o tipo do grafo usando os "
                "codigos: (0) grafo nao-direcionado; (1) grafo direcionado.\n\n");
        printf ("RESPOSTA: ");
        do {
            scanf ("%d", &tipoGrafo);
            if ((tipoGrafo != 0) && (tipoGrafo != 1)) {
                printf ("Resposta invalida. Digite novamente sua resposta: (0) grafo nao-direcionado; (1) grafo direcionado."
                        "\n\n");
                printf ("RESPOSTA: ");
            }
        } while ((tipoGrafo != 0) && (tipoGrafo != 1));
        if (tipoGrafo == 0) {
            printf ("\nINFORMACAO: voce definiu que o grafo fornecido e nao-direcionado.\n");
        }
        else {
            printf ("\nINFORMACAO: voce definiu que o grafo fornecido e direcionado.\n");
        }
        esperarUsuario();
        return (tipoGrafo);
    }

    /// ****************************************************************************************************

    int buscaEmProfundidade (FILE *ptr, int **tempoEntrada, int **tempoSaida, int **pais, LDDE **arestas) {

        // Declaração de variáveis
        int tempo;
        int *vetorTE, *vetorTS, *vetorPais;
        int *vetorRotulos;
        int i;
        int vertices;
        LDDE *listaArestas;

        // Instruções

        // Inicialização das estruturas de dados

        tempo = 0;

        vertices = qtdeVertices (ptr);
        vetorTE = (int*) calloc (vertices, sizeof (int));
        if (!vetorTE) {
            return (FRACASSO);
        }
        vetorTS = (int*) calloc (vertices, sizeof (int));
        if (!vetorTS) {
            return (FRACASSO);
        }
        vetorPais = (int*) calloc (vertices, sizeof (int));
        if (!vetorPais) {
            return (FRACASSO);
        }
        for (i=0; i<=vertices-1; i++) {
            vetorPais[i] = -1;
        }

        listaArestas = *arestas;
        if (gerarListaArestas (ptr, &listaArestas, NAODIRECIONADO) == FRACASSO) {
            return (FRACASSO);
        }
        rotulosVertices (ptr, &vetorRotulos);

        // Execução da busca em profundidade
        for (i=0; i<=vertices-1; i++) {
            if (vetorTE[i] == 0) {
                procBFS (ptr, vetorRotulos[i], &tempo, &vetorTE, &vetorTS, &vetorPais, &listaArestas);
            }
        }

        *tempoEntrada = vetorTE;
        *tempoSaida = vetorTS;
        *pais = vetorPais;
        *arestas = listaArestas;

        return (SUCESSO);
    }

    /// ****************************************************************************************************

    int procBFS (FILE *ptr, int vertAtual, int *tempoFornecido, int **tempoEntrada, int **tempoSaida, int **pais, LDDE **arestas) {

        // Declaração de variáveis
        int *vetorTE, *vetorTS, *vetorPais;
        LDDE *listaArestas;
        LDDE *listaAdj;
        LDDE *listaVizinhos;
        int tempo;
        int posVertAtual;
        // int **matrizAdj;
        int vertices;
        int numArestas;
        int i, k;
        int *vetorRotulos;
        int numVizinhos;
        aresta arestaAtual;
        int vizinho;
        int posVizinho;

        // Instruções

        // Inicialização das estruturas de dados
        tempo = *tempoFornecido;
        vetorTE = *tempoEntrada;
        vetorTS = *tempoSaida;
        vetorPais = *pais;
        listaArestas = *arestas;
        rotulosVertices (ptr, &vetorRotulos);

        // Execução do procedimento recursivo da BFS

        numArestas = tamanhoLDDE (listaArestas);
        vertices = qtdeVertices (ptr);

        tempo++;
        posVertAtual = posicaoVertice (&vetorRotulos, vertices, vertAtual);
        vetorTE[posVertAtual] = tempo;
        gerarListaAdj (ptr, &listaAdj, NAODIRECIONADO);
        buscarPosLogLDDE (listaAdj, &listaVizinhos, posVertAtual);
        numVizinhos = tamanhoLDDE (listaVizinhos);


        for (i=0; i<=numVizinhos-1; i++) {
            buscarPosLogLDDE (listaVizinhos, &vizinho, i);
            posVizinho = posicaoVertice (&vetorRotulos, vertices, vizinho);
            if (vetorTE[posVizinho] == 0) {
                for (k=0; k<=numArestas-1; k++) {
                    buscarPosLogLDDE (listaArestas, &arestaAtual, k);
                    if (((arestaAtual.extr1 == vertAtual) && (arestaAtual.extr2 == vizinho)) ||
                        ((arestaAtual.extr1 == vizinho) && (arestaAtual.extr2 == vertAtual))) {
                        arestaAtual.atributo = 1;
                    }
                    removerPosLogLDDE(listaArestas, k);
                    inserirPosLogLDDE(listaArestas, &arestaAtual, k);
                }
                // falta visitar a aresta (foi feito acima. preciso conferir!)
                vetorPais[posVizinho] = posVertAtual;
                tempo = procBFS (ptr, vizinho, &tempo, &vetorTE, &vetorTS, &vetorPais, &listaArestas);
            }
            else if ((vetorTS[posVizinho] == 0) && (vizinho != vetorPais[posVertAtual])) {
                for (k=0; k<=numArestas-1; k++) {
                    buscarPosLogLDDE (listaArestas, &arestaAtual, k);
                    if (((arestaAtual.extr1 == vertAtual) && (arestaAtual.extr2 == vizinho)) ||
                        ((arestaAtual.extr1 == vizinho) && (arestaAtual.extr2 == vertAtual))) {
                        arestaAtual.atributo = 2;
                    }
                    removerPosLogLDDE(listaArestas, k);
                    inserirPosLogLDDE(listaArestas, &arestaAtual, k);
                }
            }
            /* else if (vetorTS[i] == 0) && (i != vetorPais[posVertAtual]) {
                falta visitar a aresta
            } */
        }
        tempo++;
        vetorTS[posVertAtual] = tempo;
        return (tempo);
    }

    /// ****************************************************************************************************

    void imprimirResultadosBFS (FILE *ptr, int **tempoEntrada, int **tempoSaida, int **pais, LDDE **arestas) {

        // Declaração de variáveis
        int *vetorTE, *vetorTS, *vetorPais;
        int *vetorRotulos;
        LDDE *listaArestas;
        int vertices;
        int numArestas;
        int i;
        int ret;
        aresta arestaAtual;

        // Instruções

        vetorTE = *tempoEntrada;
        vetorTS = *tempoSaida;
        vetorPais = *pais;
        rotulosVertices (ptr, &vetorRotulos);
        vertices = qtdeVertices (ptr);

        printf ("\nQuanto aos vertices:\n\n");
        printf ("Vert.\tEntr.\tSaida\tVertice-pai\n\n");
        for (i=0; i<=vertices-1; i++) {
            printf ("V%d\t", vetorRotulos[i]);
            printf ("%d\t", vetorTE[i]);
            printf ("%d\t", vetorTS[i]);
            if (vetorPais[i] == -1) {
                printf ("Raiz da busca\n");
            }
            else {
                printf ("%d\n", vetorRotulos[vetorPais[i]]);
            }
        }

        printf ("\n\nQuanto as arestas:\n\n");
        listaArestas = *arestas;
        numArestas = tamanhoLDDE (listaArestas);
        printf ("Rotulo\tExtremidades\tTipo de aresta\n\n");
        for (i=0; i<=numArestas-1; i++) {
            ret = buscarPosLogLDDE(listaArestas, &arestaAtual, i);
            if (ret == FRACASSO) {
                printf ("Falha na impressao.\n");
                return;
            }
            printf ("Ar%d\t{ %d, %d }\t", arestaAtual.rotulo, arestaAtual.extr1, arestaAtual.extr2);
            if (arestaAtual.atributo == 1) {
                printf ("Avanco\n");
            }
            else {
                printf ("Retorno\n");
            }
        }
        printf ("\n");
    }

    /// ****************************************************************************************************

    int posicaoVerticeArq (FILE *ptr, int vertice) {

        // Declaração de variáveis
        int *vetorRotulos;
        int i;
        int numVertices;

        // Instruções

        rotulosVertices (ptr, &vetorRotulos);
        numVertices = qtdeVertices(ptr);

        for (i=0; i<=numVertices-1; i++) {
            if (vetorRotulos[i] == vertice) {
                return (i);
            }
        }

        // Se o vértice não foi encontrado:
        return (FRACASSO_ESPECIAL);
    }

    /// ****************************************************************************************************

    int posicaoVertice (int **rotulos, int qtdeVertices, int vertice) {

        // Declaração de variáveis
        int i;
        int *vetorRotulos;

        // Instruções

        vetorRotulos = *rotulos;

        for (i=0; i<=qtdeVertices-1; i++) {
            if (vetorRotulos[i] == vertice) {
                return (i);
            }
        }

        // Se o vértice não foi encontrado:
        return (FRACASSO_ESPECIAL);
    }

    /// ****************************************************************************************************


    int fechoDireto (FILE *ptr, LDDE** lista) {

        // Declaração de variáveis
        LDDE *listaFecho = NULL;
        LDDE *listaSucessores = NULL;
        LDDE *listaProvisoria = NULL;
        LDDE **vetorPonteiros = NULL;
        FDDE *filaEspera = NULL;
        int *vetorVisitados = NULL;
        int *vetorRotulos = NULL;
        int ret;
        int i, j, k;
        int vertices;
        int posVertAtual;
        int qtdeSucessores;
        int sucessor;
        int posSucessor;

        // Instruções

        vertices = qtdeVertices (ptr);

        // Obtendo a lista dos vértices sucessores de cada vértice do grafo
        ret = gerarListaSucessores(ptr, &listaSucessores);
        if (ret == FRACASSO) {
            return (FRACASSO);
        }

        // Alocando estruturas de dados utilizadas
        vetorVisitados = calloc (vertices, sizeof (int));
        if (!vetorVisitados) {
            return (FRACASSO);
        }
        ret = criarFDDE (&filaEspera, sizeof (int));
        if (ret == FRACASSO) {
            return (FRACASSO);
        }
        ret = criarLDDE (&listaFecho, sizeof (LDDE*));
        if (ret == FRACASSO) {
            return (FRACASSO);
        }

        // Alocando vetor de ponteiros que manipularão as listas contendo os vértices do fecho transitivo direto
        vetorPonteiros = (LDDE**) calloc (vertices, sizeof (LDDE*));
        if (!vetorPonteiros) {
            return (FRACASSO);
        }

        // Criando as listas dos fechos de cada vértice
        for (i=0; i<=vertices-1; i++) {
            ret = criarLDDE (&vetorPonteiros[i], sizeof (int));
            if (ret == FRACASSO) {
                return (FRACASSO);
            }
            ret = inserirFimLDDE(listaFecho, &vetorPonteiros[i]);
            if (ret == FRACASSO) {
                return (FRACASSO);
            }
        }

        // Obtendo os rótulos dos vértices
        rotulosVertices (ptr, &vetorRotulos);

        // Construção do fecho

        for (i=0; i<=vertices-1; i++) {
            ret = inserirFimLDDE (vetorPonteiros[i], &vetorRotulos[i]);
            if (ret == FRACASSO) return (FRACASSO);
            ret = inserirElemFDDE (filaEspera, &i);
            if (ret == FRACASSO) return (FRACASSO);
            vetorVisitados[i] = 1;
            while (tamanhoFDDE(filaEspera) != 0) {
                ret = buscarComecoFDDE (filaEspera, &posVertAtual);
                if (ret == FRACASSO) return (FRACASSO);
                ret = buscarPosLogLDDE (listaSucessores, &listaProvisoria, posVertAtual);
                if (ret == FRACASSO) return (FRACASSO);
                qtdeSucessores = tamanhoLDDE (listaProvisoria);
                if (qtdeSucessores == 0) {
                    ret = removerElemFDDE (filaEspera);
                    if (ret == FRACASSO) return (FRACASSO);
                }
                else {
                    for (j=0; j<=qtdeSucessores-1; j++) {
                        ret = buscarPosLogLDDE (listaProvisoria, &sucessor, j);
                        if (ret == FRACASSO) return (FRACASSO);
                        for (k=0; k<=vertices-1; k++) {
                            if (vetorRotulos[k] == sucessor) {
                                posSucessor = k;
                            }
                        }
                        if (vetorVisitados[posSucessor] == 0) {
                            ret = inserirFimLDDE (vetorPonteiros[i], &sucessor);
                            if (ret == FRACASSO) return (FRACASSO);
                            vetorVisitados[posSucessor] = 1;
                            ret = inserirElemFDDE (filaEspera, &posSucessor);
                            if (ret == FRACASSO) return (FRACASSO);
                        }
                        if (j == qtdeSucessores-1) {
                            ret = removerElemFDDE (filaEspera);
                            if (ret == FRACASSO) return (FRACASSO);
                        }
                    }
                }
                if (tamanhoFDDE (filaEspera) == 0) {
                    for (j=0; j<=vertices-1; j++) {
                        vetorVisitados[j] = 0;
                    }
                }
            }
            if (tamanhoFDDE (filaEspera) != 0) {
                ret = reiniciarFDDE(filaEspera);
                if (ret == FRACASSO) return (FRACASSO);
            }
        }

        *lista = listaFecho;
        return (SUCESSO);
    }

    /// ****************************************************************************************************

    void imprimirFDDE (FDDE *fila) {

        // Declaração de váriaveis
        int regiaoCopia;
        int i;
        int tamanhoFila;
        int ret;
        FDDE *filaCopia;

        // Instruções

        tamanhoFila = tamanhoFDDE (fila);
        if (tamanhoFila == 0) {
            printf ("Fila vazia.\n");
            return;
        }

        ret = criarFDDE (&filaCopia, sizeof (int));
        if (ret == FRACASSO) {
            return;
        }

        for (i=0; i<=tamanhoFila-1; i++) {
            ret = buscarComecoFDDE(fila, &regiaoCopia);
            if (ret == FRACASSO) {
                return;
            }
            printf ("%d\t", regiaoCopia);
            ret = inserirElemFDDE(filaCopia, &regiaoCopia);
            if (ret == FRACASSO) {
                return;
            }
            ret = removerElemFDDE (fila);
            if (ret == FRACASSO) {
                return;
            }

        }
        printf ("\n");

        *fila = *filaCopia;

    }

    /// ****************************************************************************************************

        int grafoEuleriano (FILE *ptr, int tipoGrafo) {

        /** Função que, por meio do algoritmo de Fleury, verifica se o grafo representado no arquivo de entrada é euleriano
        e fornece o caminho euleriano */

        // Declaração de variáveis

        FILE *aux;
        /* Ponteiro para manipular os arquivos gerados a cada remoção ou inserção de arestas no grafo. */
        char c;
        /* caractere utilizado para fazer cópia do arquivo de entrada. */
        LDDE *listaSucessores;
        /* Lista que armazena os vértices sucessores de todos os vértices; */
        LDDE *lista;
        /* Ponteiro da lista que armazena os vértices adjacentes a um determinado vértice. */
        LDDE *caminho;
        /* Ponteiro da lista que armazena os vértices do caminho percorrido durante a execução do algoritmo. */
        LDDE *listaArestas;
        /* Lista de arestas do grafo inicial. */
        int *vetorRotulos;
        /* Ponteiro utilizada para manipular o vetor com os rótulos dos vértices. */
        int vertAtual;
        /* Posição (linha ou coluna) correspondente ao último vértice percorrido pelo algoritmo na matriz de adjacência. */
        int posAtual;
        /* Posição no arquivo do último vértice lido no arquivo. */
        int vertAnterior;
        /* Posição (linha ou coluna) correspondente ao penúltimo vértice percorrido pelo algoritmo na matriz de adjacência. */
        int vertInicial;
        /* Posição (linha ou coluna) correspondente do vértice de partida do algoritmo na matriz de adjacência. */
        int qtdeAdj;
        /* Quantidade de vértices adjacentes a um determinado vértice. */
        int i;
        /* Contador de loop. */
        int ret;
        /* Váriavel que armazena o valor de retorno da chamada de diversas funções. */
        int componentesAnterior, componentesAtual;
        /* Número de componentes existentes num grafo antes e depois da retirada de uma aresta, respectivamente. */
        int vertImprimir;
        /* Variável utilizada para armanzenar a posição de um vértice na matriz de adjacência quando da impressão dos vértices
        percorridos pelo algoritmo. */
        int tamanhoCaminho;
        /* Quantidade de vértices do caminho percorrido pelo algoritmo. */
        aresta arestaAtual;
        /* Struct para armazenar as informações de uma aresta. */
        int arestas;
        /* Quantidade de arestas do grafo inicial. */
        int vertices;
        /* Quantidade de vértices do grafo. */
        int todasArestasRelaxadas = VERDADEIRO;
        /* Informa se todas as arestas do grafo foram relaxadas. */
        int fechouCiclo = VERDADEIRO;
        /* Informa se o caminho euleriano foi fechado. */

        // Instruções

        // Obtendo a quantidade de vértices
        vertices = qtdeVertices (ptr);

        // Gerando vetor com os rótulos dos vértices
        rotulosVertices (ptr, &vetorRotulos);

        // Gerando lista de arestas e obtendo a quantidade de arestas
        ret = gerarListaArestas(ptr, &listaArestas, tipoGrafo);
        if (ret == FRACASSO) {
            return (-1);
        }
        arestas = tamanhoLDDE (listaArestas);

        // Criando lista para anotar os vértices adjacentes de um dado vértice
        ret = criarLDDE (&lista, sizeof (int));
        if (ret == 0) {
            return (-1);
        }

        // Criando lista para anotar os vértices percorridos durante a execução da função
        ret = criarLDDE (&caminho, sizeof (int));
        if (ret == 0) {
            return (-1);
        }

        // Copiando arquivo de entrada
        aux = fopen ("Grafo_Euleriano.txt", "w");
        if (!aux) {
            return (-1);
        }
        rewind (ptr);
        while (!feof (ptr)) {
            c = fgetc (ptr);
            if (c != EOF) {
                fprintf (aux, "%c", c);
            }
        }
        fclose (aux);

        aux = fopen ("Grafo_Euleriano.txt", "r+");
        if (!aux) {
            return (-1);
        }

        // Algoritmo de Fleury

        vertAtual = vertInicial = vetorRotulos[0];
        inserirFimLDDE (caminho, &vertAtual);
        while (1) {
            for (i=0; i<=vertices-1; i++) {
                if (vetorRotulos[i] == vertAtual) {
                    posAtual = i;
                }
            }
            gerarListaSucessores (aux, &listaSucessores);
            buscarPosLogLDDE (listaSucessores, &lista, posAtual);
            vertAnterior = vertAtual;
            qtdeAdj = tamanhoLDDE (lista);
            if (qtdeAdj == 0) {
                break;
            }
            else if (qtdeAdj == 1) {
                buscarComecoLDDE (lista, &vertAtual);
                removerAresta (aux, vertAnterior, vertAtual, tipoGrafo);
                for (i=0; i<=arestas-1; i++) {
                    buscarPosLogLDDE (listaArestas, &arestaAtual, i);
                    if ((((arestaAtual.extr1 == vertAnterior) && (arestaAtual.extr2 == vertAtual)) ||
                         ((arestaAtual.extr1 == vertAtual) && (arestaAtual.extr2 == vertAnterior)))
                            && (arestaAtual.atributo == 0)) {
                        arestaAtual.atributo = 1;
                        removerPosLogLDDE (listaArestas, i);
                        inserirPosLogLDDE (listaArestas, &arestaAtual, i);
                        break;
                    }
                }
                fclose (aux);
                remove ("Grafo_Euleriano.txt");
                rename ("Grafo_Aresta_Removida.txt", "Grafo_Euleriano.txt");
                aux = fopen ("Grafo_Euleriano.txt", "r+");
                inserirFimLDDE (caminho, &vertAtual);
                reiniciarLDDE (lista);
            }
            else if (qtdeAdj >= 2) {
                for (i=0; i<=qtdeAdj-1; i++) {
                    rewind (aux);
                    componentesAnterior = qtdeComponentes (aux);
                    buscarPosLogLDDE (lista, &vertAtual, i);
                    removerAresta(aux, vertAnterior, vertAtual, tipoGrafo);
                    fclose (aux);
                    remove ("Grafo_Euleriano.txt");
                    rename ("Grafo_Aresta_Removida.txt", "Grafo_Euleriano.txt");
                    aux = fopen ("Grafo_Euleriano.txt", "r+");
                    rewind(aux);
                    componentesAtual = qtdeComponentes (aux);
                    if ((componentesAtual > componentesAnterior) && (i != qtdeAdj-1)) {
                        inserirAresta (aux, vertAnterior, vertAtual, tipoGrafo);
                        fclose (aux);
                        remove ("Grafo_Euleriano.txt");
                        rename ("Grafo_Aresta_Inserida.txt", "Grafo_Euleriano.txt");
                        aux = fopen ("Grafo_Euleriano.txt", "r+");
                    }
                    else {
                        for (i=0; i<=arestas-1; i++) {
                            buscarPosLogLDDE (listaArestas, &arestaAtual, i);
                            if ((((arestaAtual.extr1 == vertAnterior) && (arestaAtual.extr2 == vertAtual)) ||
                             ((arestaAtual.extr1 == vertAtual) && (arestaAtual.extr2 == vertAnterior)))
                                && (arestaAtual.atributo == 0)) {
                                arestaAtual.atributo = 1;
                                removerPosLogLDDE (listaArestas, i);
                                inserirPosLogLDDE (listaArestas, &arestaAtual, i);
                                break;
                            }
                        }
                        reiniciarLDDE (lista);
                        inserirFimLDDE (caminho, &vertAtual);
                        break;
                    }
                }
            }
        }

        // Imprimindo os vértices que fazem parte do caminho percorrido
        tamanhoCaminho = tamanhoLDDE (caminho);
        printf ("Caminho percorrido (vertices):\n");
        for (i=0; i<=tamanhoCaminho-1; i++) {
            buscarPosLogLDDE (caminho, &vertImprimir, i);
            if (i == 0) {
                printf ("{ %d", vertImprimir);
            }
            else if ((i != 0) && (i != tamanhoCaminho-1)) {
                printf (", %d", vertImprimir);
            }
            else {
                printf (", %d }\n", vertImprimir);
            }
        }
        fclose (aux);

        // Verificando as condições necessárias para que o grafo seja euleriano

        // Verificando se todas as arestas foram relaxadas
        for (i=0; i<=arestas-1; i++) {
            buscarPosLogLDDE (listaArestas, &arestaAtual, i);
            if (arestaAtual.atributo == 0) {
                todasArestasRelaxadas = FALSO;
                break;
            }
        }
        if (todasArestasRelaxadas == FALSO) {
            if (tipoGrafo == NAODIRECIONADO) {
                printf ("\nAVISO: as seguintes arestas nao foram relaxadas: \n");
                for (i=0; i<=arestas-1; i++) {
                    buscarPosLogLDDE (listaArestas, &arestaAtual, i);
                    if (arestaAtual.atributo == 0) {
                        printf ("{%d, %d}\n", arestaAtual.extr1, arestaAtual.extr2);
                    }
                }
            }
            else {
                printf ("\nAVISO: as seguintes arestas nao foram relaxadas: \n");
                for (i=0; i<=arestas-1; i++) {
                    buscarPosLogLDDE (listaArestas, &arestaAtual, i);
                    if (arestaAtual.atributo == 0) {
                        printf ("(%d, %d)\n", arestaAtual.extr1, arestaAtual.extr2);
                    }
                }
            }
        }

        // Verificando se, ao término do caminho percorrido, a posição de partida do caminho é igual à posição de fim
        if (vertInicial != vertAtual) {
            printf ("\nAVISO: a posicao inicial e a posicao final do caminho percorrido sao diferentes.\n");
            fechouCiclo = FALSO;
        }
        else {
            fechouCiclo = VERDADEIRO;
        }

        // Verificando se o grafo é euleriano
        if ((todasArestasRelaxadas == VERDADEIRO) && (fechouCiclo == VERDADEIRO)) {
            return (VERDADEIRO);
        }
        else {
            return (FALSO);
        }
    }

    /// ****************************************************************************************************

    int qtdeComponentes (FILE *ptr) {

        // Declaração de variáveis
        FILE *aux;
        LDDE *listaFechos;
        LDDE *listaProvisoria;
        int *vetorAlcancados;
        int *vetorRotulos;
        int posVertAlcancado;
        int ret;
        int vertices;
        int i, j, k;
        int vertAlcancado;
        int componentes;
        int tamanhoLista;

        // Instruções

        // Transformado o grafo do arquivo em um grafo não-direcionado, caso necessário.
        ret = removerSentidos (ptr);
        if (ret == FRACASSO) {
            return (-1);
        }

        if (ret == -1) {
            aux = fopen ("Grafo.txt", "r+");
        }
        else if (ret == SUCESSO) {
            aux = fopen ("Grafo_Sem_Sentidos.txt", "r+");
        }
        if (!aux) {
            return (-1);
        }

        // Obtendo os fechos dos vértices
        ret = fechoDireto (aux, &listaFechos);
        if (ret == FRACASSO) {
            return (-1);
        }

        // Obtendo os rótulos dos vértices
        rotulosVertices (ptr, &vetorRotulos);

        // Quantidade de vértices
        vertices = tamanhoLDDE (listaFechos);

        // Criando vetor para anotar os vértices já alcançados
        vetorAlcancados = (int*) calloc (vertices, sizeof (int));
        if (!vetorAlcancados) {
            return (-1);
        }

        // Contando o número de componentes
        i = 0;
        componentes = 0;
        while (vetorAlcancados[i] == 0) {
            componentes++;
            buscarPosLogLDDE(listaFechos, &listaProvisoria, i);
            tamanhoLista = tamanhoLDDE (listaProvisoria);
            for (j=0; j<=tamanhoLista-1; j++) {
                buscarPosLogLDDE(listaProvisoria, &vertAlcancado, j);
                for (k=0; k<=vertices-1; k++) {
                    if (vetorRotulos[k] == vertAlcancado) {
                        posVertAlcancado = k;
                    }
                    vetorAlcancados[posVertAlcancado] = 1;
                }
            }
            for (j=0; j<=vertices-1; j++) {
                if (vetorAlcancados[j] == 0) {
                    i = j;
                }
            }
        }
        fclose (aux);

        return (componentes);
    }

    /// ****************************************************************************************************

    int removerSentidos (FILE *ptr) {

        // Declaração de variáveis
        int **matrizAdj;
        int ret;
        int vertices;
        int i, j;
        int houveAlteracao;
        FILE *aux;
        int *vetorRotulos;

        // Instruções

        // Obtendo a matriz de adjacência do arquivo e a quantidade de vértices
        ret = gerarMatrizAdj (ptr, &matrizAdj);
        if (ret == FRACASSO) {
            return (FRACASSO);
        }
        vertices = qtdeVertices (ptr);
        // imprimirMatrizAdj(ptr, matrizAdj);
        // printf ("\n\n");


        // Tornando a matriz adjacente simétrica, caso ainda não seja.
        for (i=0; i<=vertices-1; i++) {
            for (j=0; j<=vertices-1; j++) {
                if ((matrizAdj[i][j] != 0) && (matrizAdj[j][i] == 0)) {
                    matrizAdj[j][i] = 1;
                    matrizAdj[i][j] = 1;
                    houveAlteracao = VERDADEIRO;
                }
                else if ((matrizAdj [j][i] != 0) && (matrizAdj[i][j] == 0)) {
                    matrizAdj[i][j] = 1;
                    matrizAdj[j][i] = 1;
                    houveAlteracao = VERDADEIRO;
                }
            }
        }
        if (houveAlteracao == FALSO) {
            return (-1);
        }

        // imprimirMatrizAdj(ptr, matrizAdj);
        // printf ("\n\n");

        // Criando um novo arquivo para o grafo modificado
        aux = fopen ("Grafo_Sem_Sentidos.txt", "w");
        if (!aux) {
            return (FRACASSO);
        }

        // Escrevendo os dados do grafo modificado no seu respectivo arquivo
        rotulosVertices (ptr, &vetorRotulos);
        for (i=0; i<=vertices-1; i++) {
            fprintf (aux, "%d", vetorRotulos[i]);
            for (j=0; j<=vertices-1; j++) {
                if (matrizAdj[i][j] != 0) {
                    fprintf (aux, "\t%d", vetorRotulos[j]);
                }
            }
            if (i != vertices-1) {
                fprintf (aux, "\n");
            }
        }
        fclose (aux);

        return (SUCESSO);
    }

    /// ****************************************************************************************************

    int matAdjParaArq (int ***matrizAdjacencia, int vertices, int **vetorRotulos) {

        // Declaração de variáveis
        int **matrizAdj;
        FILE *aux;
        int *VRotulos;
        int i, j;
        int k;

        // Instruções

        // Recebendo os parâmetros
        matrizAdj = *matrizAdjacencia;
        VRotulos = *vetorRotulos;

        // Criando o arquivo
        aux = fopen ("Grafo_Matriz_Adj.txt", "w");
        if (!aux) {
            return (FRACASSO);
        }

        for (i=0; i<=vertices-1; i++) {
            fprintf (aux, "%d", VRotulos[i]);
            for (j=0; j<=vertices-1; j++) {
                k = matrizAdj[i][j];
                while (k != 0) {
                    fprintf (aux, "\t%d", VRotulos[j]);
                    k--;
                }
            }
            if (i != vertices-1) {
                fprintf (aux, "\n");
            }
        }
        fclose (aux);
        return (SUCESSO);
    }

    /// ****************************************************************************************************

    int gerarListaSucessores (FILE *ptr, LDDE **lista) {

        // Declaração de variáveis
        LDDE *listaAdj;
        LDDE **vetorAux;
        int ret;
        char c;
        int vertAtual, vertLido;
        int i;
        int vertices;

        // Instruções

        // Criando a lista de adjacência
        ret = criarLDDE (&listaAdj, sizeof (LDDE*));
        if (ret == FRACASSO) {
            return (FRACASSO);
        }

        /* Alocando memória para os ponteiros das listas de vértices adjacentes de cada um dos vértices, os quais serão
        inseridos na lista de adjacência */
        vertices = qtdeVertices (ptr);
        vetorAux = (LDDE**) calloc (vertices, sizeof (LDDE*));
        if (!vetorAux) {
            return (FRACASSO);
        }

        // Criando as listas de vértices adjacentes de cada um dos vértices e inserindo-as na lista de adjacência
        for (i=0; i<=vertices-1; i++) {
            ret = criarLDDE (&vetorAux[i], sizeof (int));
            if (ret == FRACASSO) {
                return (FRACASSO);
            }
            ret = inserirFimLDDE (listaAdj, &vetorAux[i]);
            if (ret == FRACASSO) {
                return (FRACASSO);
            }
        }

        // Leitura do arquivo de entrada e inserção dos ponteiros na lista de adjacência
        rewind (ptr);
        i = 0;
        while (!feof (ptr)) {
            fscanf (ptr, "%d", &vertAtual);
            c = fgetc (ptr);
            while ((c != '\n') && (c != EOF)) {
                fscanf (ptr, "%d", &vertLido);
                c = fgetc (ptr);
                ret = inserirFimLDDE (vetorAux[i], &vertLido);
                if (ret == FRACASSO) {
                    return (FRACASSO);
                }
            }
            //imprimirLDDE(vetorAux[i]);
            i++;
        }

        // Devolvendo o ponteiro para manipular a lista de adjacência
        *lista = listaAdj;

        return (SUCESSO);
    }

    /// ****************************************************************************************************

    int gerarListaAdj (FILE *ptr, LDDE **lista, int tipoGrafo) {

        // Declaração de variáveis
        LDDE *listaAdj;
        LDDE **vetorAux;
        int ret;
        char c;
        int vertAtual, vertLido;
        int i;
        int vertices;

        // Instruções

        // Criando a lista de adjacência
        ret = criarLDDE (&listaAdj, sizeof (LDDE*));
        if (ret == FRACASSO) {
            return (FRACASSO);
        }

        /* Alocando memória para os ponteiros das listas de vértices adjacentes de cada um dos vértices, os quais serão
        inseridos na lista de adjacência */
        vertices = qtdeVertices (ptr);
        vetorAux = (LDDE**) calloc (vertices, sizeof (LDDE*));
        if (!vetorAux) {
            return (FRACASSO);
        }

        // Criando as listas de vértices adjacentes de cada um dos vértices e inserindo-as na lista de adjacência
        for (i=0; i<=vertices-1; i++) {
            ret = criarLDDE (&vetorAux[i], sizeof (int));
            if (ret == FRACASSO) {
                return (FRACASSO);
            }
            ret = inserirFimLDDE (listaAdj, &vetorAux[i]);
            if (ret == FRACASSO) {
                return (FRACASSO);
            }
        }

        // Leitura do arquivo de entrada e inserção dos ponteiros na lista de adjacência
        rewind (ptr);
        i = 0;
        while (!feof (ptr)) {
            fscanf (ptr, "%d", &vertAtual);
            c = fgetc (ptr);
            while ((c != '\n') && (c != EOF)) {
                fscanf (ptr, "%d", &vertLido);
                c = fgetc (ptr);
                ret = inserirFimLDDE (vetorAux[i], &vertLido);
                if (ret == FRACASSO) {
                    return (FRACASSO);
                }
            }
            i++;
        }

        if (tipoGrafo == DIRECIONADO) {

            // Declaração de variáveis
            int j;
            int posVertLido;
            int *vetorRotulos;

            // Inserção dos vértices adjacentes na lista
            rotulosVertices(ptr, &vetorRotulos);

            // Inserindo os vértices antecessores na lista de adjacência
            rewind (ptr);
            while (!feof (ptr)) {
                fscanf (ptr, "%d", &vertAtual);
                c = fgetc (ptr);
                while ((c != '\n') && (c != EOF)) {
                    fscanf (ptr, "%d", &vertLido);
                    c = fgetc (ptr);
                    for (j=0; j<=vertices-1; j++) {
                        if (vetorRotulos[j] == vertLido) {
                            posVertLido = j;
                        }
                    }
                    ret = inserirFimLDDE (vetorAux[posVertLido], &vertAtual);
                    if (ret == FRACASSO) {
                        return (FRACASSO);
                    }
                }
            }
        }

        // Devolvendo o ponteiro para manipular a lista de adjacência
        *lista = listaAdj;

        return (SUCESSO);
    }

    /// ****************************************************************************************************

    void imprimirMultilista (FILE *ptr, LDDE *lista) {

        // Declaração de variáveis
        LDDE *aux;
        unsigned int i;
        int vertices;
        int *vetorRotulos;
        int ret;

        // Instruções

        // Obtendo os rótulos dos vértices
        rotulosVertices (ptr, &vetorRotulos);

        // Imprimindo a lista de adjacência
        vertices = tamanhoLDDE (lista);

        for (i=0; i<=vertices-1; i++) {
            printf ("V%d:\t", vetorRotulos[i]);
            ret = buscarPosLogLDDE (lista, &aux, i);
            if (ret == FRACASSO) {
                return;
            }
            imprimirLDDE (aux);
        }
    }

    /// ****************************************************************************************************

    void imprimirLDDE (LDDE *lista) {

        // Declaração de váriaveis
        int regiaoCopia;
        unsigned int i;
        int tamanhoLista;
        int ret;

        // Instruções

        tamanhoLista = tamanhoLDDE (lista);

        if (tamanhoLista == 0) {
            printf ("{ - }\n");
        }

        for (i=0; i<=tamanhoLista-1; i++) {
            ret = buscarPosLogLDDE (lista, &regiaoCopia, i);
            if (ret == FRACASSO) {
                return;
                // printf (" { }\n");
            }
            if (i == 0) {
                printf ("{ %d", regiaoCopia);
            }
            else {
                printf (", %d", regiaoCopia);
            }
        }
        printf (" }\n");
    }

    /// ****************************************************************************************************

    int gerarVetorAdj (FILE *ptr, int **vetorGraus, int **vetorAdj, int tipoGrafo) {

        if ((tipoGrafo != NAODIRECIONADO) && (tipoGrafo != DIRECIONADO)) {
            return (FRACASSO);
        }

        else {

            if (tipoGrafo == NAODIRECIONADO) {

                // Declaração de variáveis
                int *VGraus;
                int *VAdj;
                int somaGraus = 0;
                int vertices;
                int i = 0;
                char c;
                int vertAtual, vertLido;

                // Instruções

                /* Gerando o vetor com os graus de todos os vértices, na ordem em que eles aparecem como vértices descritos
                no arquivo de entrada */
                grauTodos (ptr, &VGraus, tipoGrafo);

                // Somando os graus de todos os vértices
                vertices = qtdeVertices (ptr);
                somaGraus = somaGrausVertices (&VGraus, vertices);

                // Alocando memória para o vetor que armazena quais são os vértices adjacentes a um determinado vértice
                VAdj = (int*) calloc (somaGraus, sizeof (int));
                if (!VAdj) {
                    return (FRACASSO);
                }

                // Armazenando os vértices adjacentes aos respectivos vértices no vetor (vetorAux)
                rewind (ptr);
                while (!feof (ptr)) {
                    fscanf (ptr, "%d", &vertAtual);
                    c = fgetc (ptr);
                    while ((c != '\n') && (c != EOF)) {
                        fscanf (ptr, "%d", &vertLido);
                        if (vertLido != vertAtual) {
                            VAdj[i] = vertLido;
                            i++;
                        }
                        else {
                            VAdj[i] = vertLido;
                            i++;
                            VAdj[i] = vertLido;
                            i++;
                        }
                        c = fgetc (ptr);
                    }
                }

                /* Devolvendo dois ponteiros: um para manipular o vetor de graus e o outro para manipular o vetor de vértices
                adjacentes */
                *vetorAdj = VAdj;
                *vetorGraus = VGraus;

                return (SUCESSO);
            }

            else { // if (tipoGrafo == DIRECIONADO) {

                // Declaração de variáveis
                int *VGE, *VGS, *VGraus;
                int *VEntrada, *VSaida, *VAdj;
                int *VIndices;
                int *VRotulos;
                int somaGrausParcial, somaGraus;
                int vertices;
                int i, j;
                char c;
                int vertAtual, vertLido;
                int posVertLido;
                int indiceVAdj, indiceVEntrada, indiceVSaida;

                /* Gerando o vetor com os graus de todos os vértices, na ordem em que eles aparecem como vértices descritos
                no arquivo de entrada */
                grauTodosCompleto (ptr, &VGE, &VGS, &VGraus);

                // Somando os graus de todos os vértices
                vertices = qtdeVertices (ptr);
                somaGrausParcial = somaGrausVertices (&VGE, vertices);
                somaGraus = 2 * somaGrausParcial;

                // Alocando memória para o vetor que armazena quais são os vértices adjacentes a um determinado vértice
                VEntrada = (int*) calloc (somaGrausParcial, sizeof (int));
                if (!VEntrada) {
                    return (FRACASSO);
                }
                VSaida = (int*) calloc (somaGrausParcial, sizeof (int));
                if (!VEntrada) {
                    return (FRACASSO);
                }
                VAdj = (int*) calloc (somaGraus, sizeof (int));
                if (!VAdj) {
                    return (FRACASSO);
                }

                /* Lendo o arquivo para preencher o vetor auxiliar de entrada. Antes, vamos gerar um vetor auxiliar de índices,
                para saber em que posição do vetor auxiliar de entrada cada elemento que for lido do arquivo deve ser inserido,
                e o vetor de rótulos dos vértices. */

                VIndices = (int*) calloc (vertices, sizeof (int));
                if (!VIndices) {
                    return (FRACASSO);
                }

                for (i=vertices-1; i>=0; i--) {
                    if (i == vertices-1) {
                        VIndices[i] = somaGrausParcial - VGE[i];
                    }
                    else {
                        VIndices[i] = VIndices[i+1] - VGE[i];
                    }
                }

                // Obtendo o vetor de rótulos
                rotulosVertices (ptr, &VRotulos);

                // Preenchendo o vetor auxiliar de entrada
                rewind (ptr);
                while (!feof (ptr)) {
                    fscanf (ptr, "%d", &vertAtual);
                    c = fgetc (ptr);
                    while ((c != '\n') && (c != EOF)) {
                        fscanf (ptr, "%d", &vertLido);
                        c = fgetc (ptr);
                        for (i=0; i<=vertices-1; i++) {
                            if (VRotulos[i] == vertLido) {
                                posVertLido = i;
                            }
                        }
                        VEntrada[VIndices[posVertLido]] = vertAtual;
                        VIndices[posVertLido]++;
                    }
                }

                // Lendo o arquivo para preencher o vetor auxiliar de saída
                rewind (ptr);
                i = 0;
                while (!feof (ptr)) {
                    fscanf (ptr, "%d", &vertAtual);
                    c = fgetc (ptr);
                    while ((c != '\n') && (c != EOF)) {
                        fscanf (ptr, "%d", &vertLido);
                        c = fgetc (ptr);
                        VSaida[i] = vertLido;
                        i++;
                    }
                }

                // Preenchendo o vetor de adjacência
                indiceVAdj = 0;
                indiceVEntrada = 0;
                indiceVSaida = 0;
                for (i=0; i<=vertices-1; i++) {
                    for (j=0; j<=VGE[i]-1; j++) {
                        VAdj[indiceVAdj] = VEntrada[indiceVEntrada];
                        indiceVAdj++;
                        indiceVEntrada++;
                    }
                    for (j=0; j<=VGS[i]-1; j++) {
                        VAdj[indiceVAdj] = VSaida[indiceVSaida];
                        indiceVAdj++;
                        indiceVSaida++;
                    }
                }

                /* Devolvendo dois ponteiros: um para manipular o vetor de graus e o outro para manipular o vetor de vértices
                adjacentes */
                *vetorAdj = VAdj;
                *vetorGraus = VGraus;

                return (SUCESSO);
            }

        }
    }

    /// ****************************************************************************************************

    void imprimirVetorAdj (FILE *ptr, int *vetorGraus, int *vetorAdj) {

        // Declaração de variáveis
        int i, j;
        int *vetorRotulos;
        int vertices;
        int somaGrausAnteriores = 0;
        int *ptrGraus;
        int *ptrAdj;

        // Instruções

        ptrGraus = vetorGraus;
        ptrAdj = vetorAdj;
        vertices = qtdeVertices (ptr);

        if ((rotulosVertices (ptr, &vetorRotulos)) == 0) {
            return;
        }
        printf ("Vert.\tGrau\tVertices adjacentes\n\n");
        for (i=0; i<=vertices-1; i++) {
            printf ("V%d\t%d\t", vetorRotulos[i], ptrGraus[i]);
            for (j=0; j<=ptrGraus[i]-1; j++) {
                if (j==0) {
                    printf ("{ %d", ptrAdj[somaGrausAnteriores+j]);
                }
                else {
                    printf (" , %d", ptrAdj[somaGrausAnteriores+j]);
                }
            }
            printf (" }\n");
            somaGrausAnteriores = somaGrausAnteriores + ptrGraus[i];
        }
    }

    /// ****************************************************************************************************

    int somaGrausVertices (int **vetorGraus, int numVertices) {

        // Declaração de variáveis
        int i;
        int soma = 0;
        int *ptrGraus;

        // Instruções

        ptrGraus = *vetorGraus;

        for (i=0; i<=numVertices-1; i++) {
            soma = soma + ptrGraus[i];
        }

        return (soma);
    }

    /// ****************************************************************************************************

    int grafoComplementarArq (FILE *ptr) {

        // Declaração de variáveis
        FILE *aux;
        int vertices;
        int *vetorRotulos;
        int **matrizCompl;
        int i, j;
        int k;

        // Instruções

        // Gerando matriz de adjacência do grafo complementar
        if (grafoComplementarAdj (ptr, &matrizCompl) == 0) {
            return (FRACASSO);
        }

        // Criando o arquivo do grafo complementar
        aux = fopen ("Grafo_Complementar.txt", "w");
        if (!aux) {
            return (FRACASSO);
        }

        // Escrevendo os dados do grafo complementar no seu respectivo arquivo
        vertices = qtdeVertices (ptr);
        rotulosVertices (ptr, &vetorRotulos);
        for (i=0; i<=vertices-1; i++) {
            fprintf (aux, "%d", vetorRotulos[i]);
            for (j=0; j<=vertices-1; j++) {
                k = matrizCompl[i][j];
                while (k != 0) {
                    fprintf (aux, "\t%d", vetorRotulos[j]);
                    k--;
                }
            }
            if (i != vertices-1) {
                fprintf (aux, "\n");
            }
        }
        fclose (aux);
        return (SUCESSO);
    }

    /// ****************************************************************************************************

    int grafoComplementarAdj (FILE *ptr, int ***matrizComplemento) {

        // Declaração de variáveis
        int **matrizFonte;
        int **matrizAux;
        int vertices;
        int i, j;

        // Instruções

        // Geração da matriz de adjacência do grafo fonte
        gerarMatrizAdj (ptr, &matrizFonte);

        // Alocação de memória para a matriz de adjacência do grafo complementar
        vertices = qtdeVertices (ptr);
        matrizAux = (int**) calloc (vertices, sizeof (int*));
        if (!matrizAux) {
            return (FRACASSO);
        }
        for (i=0; i<=vertices-1; i++) {
            matrizAux[i] = (int*) calloc (vertices, sizeof (int));
            if (!matrizAux[i]) {
                return (FRACASSO);
            }
        }

        // Preenchendo a matriz de adjacencia do grafo complementar
        for (i=0; i<=vertices-1; i++) {
            for (j=0; j<=vertices-1; j++) {
                if (matrizFonte[i][j] != 0) {
                    matrizAux[i][j] = 0;
                }
                else if ((matrizFonte[i][j] == 0) && (i != j)) {
                    matrizAux[i][j] = 1;
                }
            }
        }

        // Devolvendo o ponteiro para manipular a matriz de adjacencia
        *matrizComplemento = matrizAux;

        return (SUCESSO);
    }

    /// ****************************************************************************************************

    int removerAresta (FILE *ptr, int vertice1, int vertice2, int tipoGrafo) {

        // Declarações
        int **matrizAdj;
        FILE *aux;
        int vertices;
        int posVertice1 = -1, posVertice2 = -1;
        int i, j, k;
        int *vetorRotulos;

        // Instruções

        // Verificando se o parâmetro 'tipoGrafo' possui um valor válido
        if ((tipoGrafo != DIRECIONADO) && (tipoGrafo != NAODIRECIONADO)) {
            return (FRACASSO);
        }

        // Obtendo as posições (linhas) no arquivo dos vertices fornecidos
        rotulosVertices (ptr, &vetorRotulos);
        vertices = qtdeVertices (ptr);
        for (i=0; i<=vertices-1; i++) {
            if (vetorRotulos[i] == vertice1) {
                posVertice1 = i;
                break;
            }
        }
        for (i=0; i<=vertices-1; i++) {
            if (vetorRotulos[i] == vertice2) {
                posVertice2 = i;
                break;
            }
        }

        // Verificando se os vértices fornecidos existem
        if ((posVertice1 == -1) || (posVertice2 == -1)) {
            return (0);
        }

        // Verificando se a aresta fornecida existe e removendo a aresta da matriz de adjacência
        gerarMatrizAdj (ptr, &matrizAdj);

        if (tipoGrafo == NAODIRECIONADO) {
            if (matrizAdj[posVertice1][posVertice2] == 0) {
                return (FRACASSO);
            }
            else {
                matrizAdj[posVertice1][posVertice2]--;
                matrizAdj[posVertice2][posVertice1]--;
            }
        }
        else {
            if (matrizAdj[posVertice1][posVertice2] == 0) {
                return (FRACASSO);
            }
            else {
                matrizAdj[posVertice1][posVertice2]--;
            }
        }

        // Criando novo arquivo para o grafo
        aux = fopen ("Grafo_Aresta_Removida.txt", "w");
        if (!aux) {
            return (FRACASSO);
        }

        // Escrevendo os dados do grafo no arquivo
        for (i=0; i<=vertices-1; i++) {
            fprintf (aux, "%d", vetorRotulos[i]);
            for (j=0; j<=vertices-1; j++) {
                k = matrizAdj[i][j];
                while (k != 0) {
                    fprintf (aux, "\t%d", vetorRotulos[j]);
                    k--;
                }
            }
            if (i != vertices-1) {
                fprintf (aux, "\n");
            }
        }
        fclose (aux);

        return (SUCESSO);
    }

    /// ****************************************************************************************************

    int inserirAresta (FILE *ptr, int vertice1, int vertice2, int tipoGrafo) {

        // Declarações
        int **matrizAdj;
        FILE *aux;
        int vertices;
        int posVertice1 = -1, posVertice2 = -1;
        int vertice1Encontrado = 0, vertice2Encontrado = 0;
        int i, j, k;
        int *vetorRotulos;

        // Instruções

        // Verificando se o parâmetro 'tipoGrafo' possui um valor válido
        if ((tipoGrafo != DIRECIONADO) && (tipoGrafo != NAODIRECIONADO)) {
            return (FRACASSO);
        }

        // Verificando se os vertices fornecidos existem
        rotulosVertices (ptr, &vetorRotulos);
        vertices = qtdeVertices (ptr);
        for (i=0; i<=vertices-1; i++) {
            if (vertice1 == vetorRotulos[i]) {
                vertice1Encontrado = 1;
            }
            if (vertice2 == vetorRotulos[i]) {
                vertice2Encontrado = 1;
            }
        }
        if ((vertice1Encontrado == 0) || (vertice2Encontrado == 0)) {
            return (FRACASSO);
        }

        // Obtendo as posições (linhas) no arquivo dos vertices fornecidos
        for (i=0; i<=vertices-1; i++) {
            if (vetorRotulos[i] == vertice1) {
                posVertice1 = i;
                break;
            }
        }
        for (i=0; i<=vertices-1; i++) {
            if (vetorRotulos[i] == vertice2) {
                posVertice2 = i;
                break;
            }
        }

        // Adicionando a aresta na matriz de adjacência
        gerarMatrizAdj (ptr, &matrizAdj);
        if (tipoGrafo == NAODIRECIONADO) {
            matrizAdj[posVertice1][posVertice2]++;
            matrizAdj[posVertice2][posVertice1]++;
        }
        else {
            matrizAdj[posVertice1][posVertice2]++;
        }

        // Criando novo arquivo para o grafo
        aux = fopen ("Grafo_Aresta_Inserida.txt", "w");
        if (!aux) {
            return (FRACASSO);
        }

        // Escrevendo os dados no arquivo
        for (i=0; i<=vertices-1; i++) {
            fprintf (aux, "%d", vetorRotulos[i]);
            for (j=0; j<=vertices-1; j++) {
                k = matrizAdj[i][j];
                while (k != 0) {
                    fprintf (aux, "\t%d", vetorRotulos[j]);
                    k--;
                }
            }
            if (i != vertices-1) {
                fprintf (aux, "\n");
            }
        }
        fclose (aux);
        return (SUCESSO);
    }

    /// ****************************************************************************************************

    int inserirVertice (FILE *ptr) {

        // Declaração de variáveis
        int maiorVertice = -1;
        int vertAtual = -1;
        int vertices;
        char c;

        // Instruções

        // Lendo o arquivo para descobrir qual é o vértice com o maior rótulo
        rewind (ptr);
        while (!feof (ptr)) {
            fscanf (ptr, "%d", &vertAtual);
            if (vertAtual > maiorVertice) {
                maiorVertice = vertAtual;
            }
            c = fgetc (ptr);
            while ((c != '\n') && (c != EOF)) {
                c = fgetc (ptr);
            }
        }

        // Escrevendo o novo vértice no arquivo
        fseek (ptr, 0, SEEK_CUR);
        vertices = qtdeVertices (ptr);
        if (vertices == 0) {
            fprintf (ptr, "%d", maiorVertice+1);
        }
        else {
            fprintf (ptr, "\n%d", maiorVertice+1);
        }
        return (SUCESSO);
    }

    /// ****************************************************************************************************

    int removerVertice (FILE *ptr, int vertRemover) {

        // Declarações
        int **matrizAdj;
        int *vetorRotulos;
        FILE *aux;
        int vertices;
        int posVertRemover = -1;
        // int vertRemoverEncontrado = 0;
        int i, j, k;

        // Instruções

        // Verificando se o vértice existe
        if (rotulosVertices (ptr, &vetorRotulos) == FRACASSO) {
            return (FRACASSO);
        }

        // Encontrando a linha do vértice a ser removido na matriz de adjacencia
        vertices = qtdeVertices(ptr);
        for (i=0; i<=vertices-1; i++) {
            if (vetorRotulos[i] == vertRemover) {
                posVertRemover = i;
            }
        }

        /* Removendo as arestas que contém o vértice da matriz de adjacência */
        gerarMatrizAdj (ptr, &matrizAdj);

        for (i=0; i<=vertices-1; i++) {
            if (matrizAdj[i][posVertRemover] != 0) {
                matrizAdj[i][posVertRemover] = 0;
            }
        }
        for (i=0; i<=vertices-1; i++) {
            if (matrizAdj[posVertRemover][i] != 0) {
                matrizAdj[posVertRemover][i] = 0;
            }
        }

        // Criando arquivo para o grafo
        aux = fopen ("Grafo_Vertice_Removido.txt", "w");
        if (!aux) {
            return (FRACASSO);
        }

        // Escrevendo os dados no arquivo
        for (i=0; i<=vertices-1; i++) {
            if (i != posVertRemover) {
                fprintf (aux, "%d", vetorRotulos[i]);
            }
            for (j=0; j<=vertices-1; j++) {
                if (j != posVertRemover) {
                    k = matrizAdj[i][j];
                    while (k != 0) {
                        fprintf (aux, "\t%d", vetorRotulos[j]);
                        k--;
                    }
                }
            }
            if ((i != vertices-1) && ((i+1) != posVertRemover)) {
                fprintf (aux, "\n");
            }
        }
        fclose (aux);
        return (SUCESSO);
    }

    /// ****************************************************************************************************

    int rotulosVertices (FILE *ptr, int **V) {

        // Declarações de variáveis
        int *rotulos;
        int i = 0;
        int vertAtual;
        char c;
        // int j;

        // Instruções

        // Alocando memória para o vetor que armazenará os rótulos dos vértices
        rotulos = (int*) calloc (qtdeVertices (ptr), sizeof (int));
        if (!rotulos) {
            return (FRACASSO);
        }

        // Escrevendo os rótulos dos vértices no vetor alocado
        rewind (ptr);
        while (!feof (ptr)) {
            fscanf (ptr, "%d", &vertAtual);
            rotulos[i] = vertAtual;
            i++;
            c = fgetc (ptr);
            while ((c != '\n') && (c != EOF)) {
                c = fgetc (ptr);
            }
        }

        // Devolvendo um ponteiro para manipular o vetor
        *V = rotulos;
        return (SUCESSO);

    }

    /// ****************************************************************************************************

    void grauEntradaTodos (FILE *ptr, int **vetorGrauEntrada) {

        // Declaração de variáveis
        int vertices;
        int *GE;
        int *vetorRotulos;
        char c;
        int vertAtual;
        int vertLido, posVertLido;
        int i;

        // Instruções

        // Alocando espaço para os vetores que armazenarão os graus dos vértices
        vertices = qtdeVertices (ptr);
        GE = (int*) calloc (vertices, sizeof (int));

        // Obtendo os rótulos dos vértices
        rotulosVertices (ptr, &vetorRotulos);

        // Lendo o arquivo para contar quantas vezes cada vértice compartilha arestas com outros vértices e consigo mesmo
        rewind (ptr);
        while (!feof (ptr)) {
            fscanf (ptr, "%d", &vertAtual);
            c = fgetc (ptr);
            while ((c != '\n') && (c != EOF)) {
                fscanf (ptr, "%d", &vertLido);
                c = fgetc (ptr);
                for (i=0; i<=vertices-1; i++) {
                    if (vetorRotulos[i] == vertLido) {
                        posVertLido = i;
                    }
                }
                GE[posVertLido]++;
            }
        }

        // Devolvendo um ponteiro para manipular o vetor contendo os graus dos vértices
        *vetorGrauEntrada = GE;
    }

    /// ****************************************************************************************************

    void grauSaidaTodos (FILE *ptr, int **vetorGrauSaida) {

        // Declaração de variáveis
        int vertices;
        int *GS;
        int *vetorRotulos;
        char c;
        int vertAtual, posVertAtual;
        int vertLido;
        int i;

        // Instruções

        // Alocando espaço para os vetores que armazenarão os graus dos vértices
        vertices = qtdeVertices (ptr);
        GS = (int*) calloc (vertices, sizeof (int));

        // Obtendo os rótulos dos vértices
        rotulosVertices (ptr, &vetorRotulos);

        // Lendo o arquivo para contar quantas vezes cada vértice compartilha arestas com outros vértices e consigo mesmo
        rewind (ptr);
        while (!feof (ptr)) {
            fscanf (ptr, "%d", &vertAtual);
            c = fgetc (ptr);
            for (i=0; i<=vertices-1; i++) {
                if (vetorRotulos[i] == vertAtual) {
                    posVertAtual = i;
                }
            }
            while ((c != '\n') && (c != EOF)) {
                fscanf (ptr, "%d", &vertLido);
                c = fgetc (ptr);
                GS[posVertAtual]++;
            }
        }

        // Devolvendo um ponteiro para manipular o vetor contendo os graus dos vértices
        *vetorGrauSaida = GS;
    }

    /// ****************************************************************************************************

    void grauTodosCompleto (FILE *ptr, int **vetorGrauEntrada, int **vetorGrauSaida, int **vetorGrau) {

        // Declaração de variáveis
        int *grau;
        int *GE;
        int *GS;
        int *vetorRotulos;
        int vertices;
        char c;
        int vertAtual, posVertAtual;
        int vertLido, posVertLido;
        int i;

        // Instruções

        // Alocando espaço para os vetores que serão utilizados
        vertices = qtdeVertices (ptr);
        GE = (int*) calloc (vertices, sizeof (int));
        GS = (int*) calloc (vertices, sizeof (int));
        grau = (int*) calloc (vertices, sizeof (int));

        // Obtendo os rótulos dos vértices
        rotulosVertices(ptr, &vetorRotulos);

        // Lendo o arquivo para contar quantas vezes cada vértice compartilha arestas com outros vértices e consigo mesmo
        rewind (ptr);
        while (!feof (ptr)) {
            fscanf (ptr, "%d", &vertAtual);
            for (i=0; i<=vertices-1; i++) {
                if (vetorRotulos[i] == vertAtual) {
                    posVertAtual = i;
                }
            }
            c = fgetc (ptr);
            while ((c != '\n') && (c != EOF)) {
                fscanf (ptr, "%d", &vertLido);
                for (i=0; i<=vertices-1; i++) {
                    if (vetorRotulos[i] == vertLido) {
                        posVertLido = i;
                    }
                }
                c = fgetc (ptr);
                GE[posVertLido]++;
                GS[posVertAtual]++;
            }
        }
        for (i=0; i<=vertices-1; i++) {
            grau[i] = GE[i] + GS[i];
        }

        // Devolvendo um ponteiro para manipular o vetor contendo os graus dos vértices
        *vetorGrau = grau;
        *vetorGrauEntrada = GE;
        *vetorGrauSaida = GS;
    }

    /// ****************************************************************************************************

    void grauTodos (FILE *ptr, int **vetorGrau, int tipoGrafo) {

        // Declaração de variáveis
        int *grau;
        int *GE;
        int *GS;
        int *vetorRotulos;
        int vertices;
        char c;
        int vertAtual, posVertAtual;
        int vertLido, posVertLido;
        int i;

        // Instruções

        // Alocando espaço para os vetores que serão utilizados
        vertices = qtdeVertices (ptr);
        GE = (int*) calloc (vertices, sizeof (int));
        GS = (int*) calloc (vertices, sizeof (int));
        grau = (int*) calloc (vertices, sizeof (int));

        // Obtendo os rótulos dos vértices
        rotulosVertices(ptr, &vetorRotulos);

        // Lendo o arquivo para contar quantas vezes cada vértice compartilha arestas com outros vértices e consigo mesmo
        rewind (ptr);
        while (!feof (ptr)) {
            fscanf (ptr, "%d", &vertAtual);
            for (i=0; i<=vertices-1; i++) {
                if (vetorRotulos[i] == vertAtual) {
                    posVertAtual = i;
                }
            }
            c = fgetc (ptr);
            while ((c != '\n') && (c != EOF)) {
                fscanf (ptr, "%d", &vertLido);
                for (i=0; i<=vertices-1; i++) {
                    if (vetorRotulos[i] == vertLido) {
                        posVertLido = i;
                    }
                }
                c = fgetc (ptr);
                GE[posVertLido]++;
                GS[posVertAtual]++;
            }
        }
        if (tipoGrafo == NAODIRECIONADO) {
            for (i=0; i<=vertices-1; i++) {
                grau[i] = GS[i];
            }
        }
        else {
            for (i=0; i<=vertices-1; i++) {
                grau[i] = GE[i] + GS[i];
            }
        }

        // Devolvendo um ponteiro para manipular o vetor contendo os graus dos vértices
        *vetorGrau = grau;
    }

    /// ****************************************************************************************************

    int grauVertice (FILE *ptr, int vertice) {

        // Declaração de variáveis
        int grauEntrada, grauSaida, grau;

        // Instruções

        // Obtendo o grau de entrada e de saida do vertice. O grau 'total' é a soma do grau de entrada com o grau de saída.
        grauEntrada = grauEntradaVertice (ptr, vertice);
        if (grauEntrada == -1) {
            return (-1);
        }
        grauSaida = grauSaidaVertice (ptr, vertice);
        if (grauSaida == -1) {
            return (-1);
        }
        grau = grauEntrada + grauSaida;
        return (grau);
    }


    /// ****************************************************************************************************

    int grauEntradaVertice (FILE *ptr, int vertice) {

        // Declaração de variáveis
        char c;
        int vertAtual;
        int vertLido;
        int grauEntrada = 0;
        int verticeEncontrado = 0;

        // Instruções

        // Lendo o arquivo. Aqui procura-se se o vértice descrito em cada linha é o vertice cujo grau deseja-se saber.
        rewind (ptr);
        while (!feof (ptr)) {
            fscanf (ptr, "%d", &vertAtual);
            c = fgetc (ptr);
            if (vertAtual == vertice) {
                    verticeEncontrado = 1;
                }
            while ((c != '\n') && (c != EOF)) {
                fscanf (ptr, "%d", &vertLido);
                c = fgetc (ptr);
                if (vertLido == vertice) {
                    grauEntrada++;
                }

            }
        }
        if (verticeEncontrado == 0) {
            return (-1);
        }
        else {
            return (grauEntrada);
        }
    }

    /// ****************************************************************************************************

    int grauSaidaVertice (FILE *ptr, int vertice) {

        // Declaração de variáveis
        char c;
        int vertAtual;
        int vertLido;
        int grauSaida = 0;
        int verticeEncontrado = 0;

        // Instruções

        // Lendo o arquivo. Aqui procura-se se o vértice descrito em cada linha é o vertice cujo grau deseja-se saber.
        rewind (ptr);
        while (!feof (ptr)) {
            fscanf (ptr, "%d", &vertAtual);
            c = fgetc (ptr);
            if (vertAtual == vertice) {
                verticeEncontrado = 1;
                while ((c != '\n') && (c != EOF)) {
                    fscanf (ptr, "%d", &vertLido);
                    grauSaida++;
                    c = fgetc (ptr);
                }
            }
            else {
                while ((c != '\n') && (c != EOF)) {
                    fscanf (ptr, "%d", &vertLido);
                    c = fgetc (ptr);
                }
            }
        }
        if (verticeEncontrado == 0) {
            return (-1);
        }
        else {
            return (grauSaida);
        }
    }


    /// ****************************************************************************************************

    int arestasParalelas (FILE *ptr) {

        // Declaração de variáveis
        int **matrizAdj;
        int vertices;
        int i, j;
        int arestasParalelas = 0;

        // Instruções

        // Gerando a matriz de adjacência e contando quantas arestas paralelas existem no grafo por meio da matriz
        gerarMatrizAdj (ptr, &matrizAdj);
        vertices = qtdeVertices (ptr);
        for (i=0; i<=vertices-1; i++) {
            for (j=0; j<=vertices-1; j++) {
                if (matrizAdj[i][j] > 1) {
                    arestasParalelas = 1;
                    break;
                }
            }
            if (arestasParalelas != 0) {
                break;
            }
        }
        return (arestasParalelas);
    }

    /// ****************************************************************************************************

    int qtdeVertices (FILE *ptr) {

        // Declaração de variáveis
        char c;
        int vertices = 0;

        // Instruções

        // Lendo o arquivo à procura de separadores de linha '\n'
        rewind (ptr);
        c = fgetc (ptr);
        if (c != EOF) {
            vertices = 1;
        }
        while (c != EOF) {
            if (c == '\n') {
                vertices++;
            }
            c = fgetc (ptr);
        }
        return (vertices);
    }

    /// ****************************************************************************************************

    int qtdeArestas (FILE *ptr, int tipoGrafo) {

        // Declaração de variáveis
        char c;
        int vertAtual;
        int vertLido;
        int arestas = 0;

        // Instruções

        // Verificando se o parâmetro 'tipoGrafo' possui um valor válido
        if ((tipoGrafo != DIRECIONADO) && (tipoGrafo != NAODIRECIONADO)) {
            return (-1);
        }

        // Realizando a contagem das arestas
        rewind (ptr);
        while (!feof (ptr)) {
            fscanf (ptr, "%d", &vertAtual);
            c = fgetc (ptr);
            if (tipoGrafo == DIRECIONADO) {
                while ((c != '\n') && (c != EOF)) {
                    fscanf (ptr, "%d", &vertLido);
                    /* if (vertAtual <= vertLido) {
                        arestas++;
                    } */
                    arestas++;
                    c = fgetc (ptr);
                }
            }
            else { // if (tipoGrafo == NAODIRECIONADO)
                while ((c != '\n') && (c != EOF)) {
                    fscanf (ptr, "%d", &vertLido);
                    if (vertAtual <= vertLido) {
                        arestas++;
                    }
                    c = fgetc (ptr);
                }
            }
        }
        return (arestas);
    }

    /// ****************************************************************************************************

    int gerarMatrizAdj (FILE *ptr, int ***matriz) {

        // Declaração de variáveis
        char c;
        int vertices;
        int i;
        int **matrizAdj;
        int vertAtual, posVertAtual = -1;
        int vertLido, posVertLido = -1;
        int *vetorRotulos;

        // Instruções

        rewind (ptr);

        // Contando o número de vértices do grafo
        vertices = qtdeVertices (ptr);

        // Alocando memória para a matriz
        matrizAdj = (int**) calloc (vertices, sizeof (int*));
        if (!matrizAdj) {
            return (FRACASSO);
        }
        for (i=0; i<=vertices-1; i++) {
            matrizAdj[i] = (int*) calloc (vertices, sizeof (int));
            if (!matrizAdj[i]) {
                return (FRACASSO);
            }
        }

        // Gerando a matriz de adjacência

        rotulosVertices (ptr, &vetorRotulos);
        rewind (ptr);

        while (!feof (ptr)) {
            fscanf (ptr, "%d", &vertAtual); // Lendo um vértice do arquivo e verificando sua linha no arquivo (0ª, 1ª, 2ª, ...)
            for (i=0; i<=vertices-1; i++) {
                if (vetorRotulos[i] == vertAtual) {
                    posVertAtual = i;
                    break;
                }
            }
            c = fgetc (ptr);
            while ((c != '\n') && (c != EOF)) { // Lendo os vértices vizinhos ao vértice atual e conferindo as suas posições
                fscanf (ptr, "%d", &vertLido);
                for (i=0; i<=vertices-1; i++) {
                    if (vetorRotulos[i] == vertLido) {
                        posVertLido = i;
                        break;
                    }
                }
                matrizAdj[posVertAtual][posVertLido]++; // Preenchendo a matriz de adjacência
                c = fgetc (ptr); // Lendo o próximo caractere
            }
        }

        *matriz = matrizAdj;
        return (SUCESSO);
    }

    /// ****************************************************************************************************

    void imprimirMatrizAdj (FILE *ptr, int **matriz) {

        // Declaração de variáveis
        int i, j, k=0, l=0; // contadores para loops
        int dimensao; // dimensao da matriz (quadrada)
        int *vetorRotulos;

        // Instruções

        dimensao = qtdeVertices (ptr);
        rotulosVertices (ptr, &vetorRotulos);

        for (i=-1; i<=dimensao-1; i++) {
            for (j=-1; j<=dimensao-1; j++) {
                if ((i==-1) && (j==-1)) {
                    printf ("      ");
                }
                if ((i == -1) && (j != -1)) {
                    printf ("V%-4d", vetorRotulos[k]);
                    if (k == (dimensao-1)) {
                        printf ("\n");
                    }
                    k++;
                }
                if (i != -1) {
                    if (j == -1) {
                        printf ("V%-5d", vetorRotulos[l]);
                        l++;
                    }
                    else {
                        if (j<dimensao-1) {
                            printf ("%-5d", matriz[i][j]);
                        }
                        else {
                            printf ("%-5d\n", matriz[i][j]);
                        }
                    }
                }
            }
        }
    }

    /// ****************************************************************************************************

    int gerarMatrizIncid (FILE *ptr, int ***matriz, int tipoGrafo) {

        // Declaração de variáveis
        LDDE *listaArestas;
        int **matrizIncid;
        aresta arestaAtual;
        int ret;
        int vertices;
        int arestas;
        int *vetorRotulos;
        int i, j;
        int vertice1, vertice2;
        int posVertice1, posVertice2;

        // Instruções

        // Verificando se o parâmetro 'tipoGrafo' possui um valor válido
        if ((tipoGrafo != DIRECIONADO) && (tipoGrafo != NAODIRECIONADO)) {
            return (FRACASSO);
        }

        // Gerando lista de arestas
        ret = gerarListaArestas (ptr, &listaArestas, tipoGrafo);
        if (ret == FRACASSO) {
            return (FRACASSO);
        }

        // Contando o número de vértices e arestas
        vertices = qtdeVertices (ptr);
        arestas = tamanhoLDDE (listaArestas);

        // Alocando memória para a matriz de incidência
        matrizIncid = (int**) calloc (arestas, sizeof (int*));
        for (i=0; i<=arestas-1; i++) {
            matrizIncid[i] = (int*) calloc (vertices, sizeof (int));
        }

        // Obtendo o vetor de rótulos
        rotulosVertices (ptr, &vetorRotulos);

        // Gerando a matriz de incidência
        for (i=0; i<=arestas-1; i++) {
            ret = buscarPosLogLDDE (listaArestas, &arestaAtual, i);
            if (ret == FRACASSO) {
                return (FRACASSO);
            }
            vertice1 = arestaAtual.extr1;
            for (j=0; j<=vertices-1; j++) {
                if (vetorRotulos[j] == vertice1) {
                    posVertice1 = j;
                }
            }
            vertice2 = arestaAtual.extr2;
            for (j=0; j<=vertices-1; j++) {
                if (vetorRotulos[j] == vertice2) {
                    posVertice2 = j;
                }
            }
            switch (tipoGrafo) {
                case NAODIRECIONADO:
                    matrizIncid[i][posVertice1]++;
                    matrizIncid[i][posVertice2]++;
                    break;
                case DIRECIONADO:
                    matrizIncid[i][posVertice1]++;
                    matrizIncid[i][posVertice2]--;
                    break;
            }
        }

        *matriz = matrizIncid;
        return (SUCESSO);
    }

    /// ****************************************************************************************************

    void imprimirMatrizIncid (FILE *ptr, int **matriz, int tipoGrafo) {

        // Declaração de variáveis
        int linhas, colunas; // dimensões da matriz
        int *vetorRotulos;
        LDDE *listaArestas;
        aresta arestaAtual;
        int i, j;
        int ret;

        // Instruções

        ret = gerarListaArestas (ptr, &listaArestas, tipoGrafo);
        if (ret == FRACASSO) {
            return;
        }

        // Obtendo as dimensões da matriz
        linhas = tamanhoLDDE (listaArestas);
        colunas = qtdeVertices (ptr);

        // Obtendo os rótulos dos vértices
        rotulosVertices (ptr, &vetorRotulos);

        // Imprimindo a matriz de incidência
        for (i=-1; i<=linhas-1; i++) {
            for (j=-1; j<=colunas-1; j++) {
                if (i == -1) {
                    if (j == -1) {
                        printf ("       ");
                    }
                    else if (j != colunas-1) {
                        printf ("V%-4d", vetorRotulos[j]);
                    }
                    else {
                        printf ("V%-4d\n", vetorRotulos[j]);
                    }
                }
                else {
                    if (j == -1) {
                        ret = buscarPosLogLDDE (listaArestas, &arestaAtual, i);
                        if (ret == FRACASSO) {
                            return;
                        }
                        printf ("Ar%-5d", arestaAtual.rotulo);
                    }
                    else if (j != colunas-1) {
                        printf ("%-5d", matriz[i][j]);
                    }
                    else {
                        printf ("%-5d\n", matriz[i][j]);
                    }
                }
            }
        }
    }
