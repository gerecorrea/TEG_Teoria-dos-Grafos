# include <stdio.h>
# include <stdlib.h>
# include "Protótipos_Funções.h"
# include "estruturasdedados.h"
# include "funcoes_menu.h"


    /// ****************************************************************************************************

    void menuVerArquivo (void) {

        // Declaração de variáveis
        FILE *arq;

        // Instruções
        arq = abrirArquivo();
        if (arq != NULL) {
            printf ("VISUALIZAR ARQUIVO\n\n");
            verArquivo (arq);
            fclose (arq);
        }
        esperarUsuario();
    }

    /// ****************************************************************************************************

    void menuMatrizAdj (void) {

        // Declaração de variáveis
        FILE *arq;
        int **matrizAdj;

        // Instruções

        arq = abrirArquivo();
        if (arq != NULL) {
            printf ("MATRIZ DE ADJACENCIA\n\n");
            gerarMatrizAdj (arq, &matrizAdj);
            imprimirMatrizAdj (arq, matrizAdj);
            fclose (arq);
        }
        esperarUsuario();
    }

    /// ****************************************************************************************************

    void menuMatrizIncid (int tipoGrafo) {

        // Declaração de variáveis
        FILE *arq;
        int **matrizIncid;

        // Instruções

        arq = abrirArquivo();
        if (arq != NULL) {
            printf ("MATRIZ DE INCIDENCIA\n\n");
            gerarMatrizIncid (arq, &matrizIncid, tipoGrafo);
            imprimirMatrizIncid (arq, matrizIncid, tipoGrafo);
            fclose (arq);
        }
        esperarUsuario ();
    }

    /// ****************************************************************************************************

    void menuArestasParalelas (void) {

        // Declaração de variáveis
        FILE *arq;

        // Instruções

        arq = abrirArquivo();
        if (arq != NULL) {
            printf ("VERIFICAR SE O GRAFO POSSUI ARESTAS PARALELAS\n\n");
            if ((arestasParalelas (arq)) == 0) {
                printf ("RESPOSTA: o grafo NAO POSSUI arestas paralelas.\n");
            }
            else {
                printf ("RESPOSTA: o grafo POSSUI arestas paralelas.\n");
            }
            fclose (arq);
        }
        esperarUsuario();
    }

    /// ****************************************************************************************************

    void menuQuantidadeVertices (void) {

            // Declaração de variáveis
            FILE *arq;

            // Instruções
            arq = abrirArquivo();
            if (arq != NULL) {
                printf ("QUANTIDADE DE VERTICES\n\n");
                printf ("RESPOSTA: %d vertice(s).\n", qtdeVertices (arq));
                fclose (arq);
            }
            esperarUsuario();
        }

    /// ****************************************************************************************************

    void menuQuantidadeArestas (int tipoGrafo) {

        // Declaração de variáveis
        FILE *arq;

        // Instruções
        arq = abrirArquivo();
        if (arq != NULL) {
            printf ("QUANTIDADE DE ARESTAS\n\n");
            printf ("RESPOSTA: %d aresta(s).\n", qtdeArestas (arq, tipoGrafo));
            fclose (arq);
        }
        esperarUsuario();
    }

    /// ****************************************************************************************************

    void menuGrauEntradaVertice () {

        // Declaração de variáveis
        FILE *arq;
        int vertDesejado;
        int GEVertDesejado;

        // Instruções

        arq = abrirArquivo();
        if (arq != NULL) {
            printf ("GRAU DE ENTRADA DE UM DETERMINADO VERTICE\n\n");
            printf ("Vertice desejado: ");
            scanf ("%d", &vertDesejado);
            GEVertDesejado = grauEntradaVertice (arq, vertDesejado);
            if (GEVertDesejado != -1) {
                printf ("\nRESPOSTA: Grau (V%d) = %d.\n", vertDesejado, GEVertDesejado);
            }
            else {
                printf ("\nRESPOSTA: o vertice procurado nao consta no grafo.\n");
            }
            fclose (arq);
        }
        esperarUsuario();
    }

    /// ****************************************************************************************************

    void menuGrauSaidaVertice () {

        // Declaração de variáveis
        FILE *arq;
        int vertDesejado;
        int GSVertDesejado;

        // Instruções

        arq = abrirArquivo();
        if (arq != NULL) {
            printf ("GRAU DE SAIDA DE UM DETERMINADO VERTICE\n\n");
            printf ("Vertice desejado: ");
            scanf ("%d", &vertDesejado);
            GSVertDesejado = grauSaidaVertice (arq, vertDesejado);
            if (GSVertDesejado != -1) {
                printf ("\nRESPOSTA: Grau (V%d) = %d.\n", vertDesejado, GSVertDesejado);
            }
            else {
                printf ("\nRESPOSTA: o vertice procurado nao consta no grafo.\n");
            }
            fclose (arq);
        }
        esperarUsuario();
    }

    /// ****************************************************************************************************

    void menuGrauVertice () {

        // Declaração de variáveis
        FILE *arq;
        int vertDesejado;
        int grauVertDesejado;

        // Instruções

        arq = abrirArquivo();
        if (arq != NULL) {
            printf ("GRAU DE UM DETERMINADO VERTICE\n\n");
            printf ("Vertice desejado: ");
            scanf ("%d", &vertDesejado);
            grauVertDesejado = grauVertice (arq, vertDesejado);
            if (grauVertDesejado != -1) {
                printf ("\nRESPOSTA: Grau (V%d) = %d.\n", vertDesejado, grauVertDesejado);
            }
            else {
                printf ("\nRESPOSTA: o vertice procurado nao consta no grafo.\n");
            }
            fclose (arq);
        }
        esperarUsuario();
    }

    /// ****************************************************************************************************

    void menuGrauEntradaTodos () {

        // Declaração de variáveis
        FILE *arq;
        int *vetorGE;
        int *vetorRotulos;
        int i;

        // Instruções

        arq = abrirArquivo();
        if (arq != NULL) {
            printf ("GRAUS DE ENTRADA DE TODOS OS VERTICES\n\n");
            grauEntradaTodos (arq, &vetorGE);
            rotulosVertices (arq, &vetorRotulos);
            printf ("RESPOSTA:\n\n");
            for (i=0; i<=qtdeVertices(arq)-1; i++) {
                printf ("V%d:\t%d\n", vetorRotulos[i], vetorGE[i]);
            }
            fclose (arq);
        }
        esperarUsuario();
    }

    /// ****************************************************************************************************

    void menuGrauSaidaTodos () {

        // Declaração de variáveis
        FILE *arq;
        int *vetorGS;
        int *vetorRotulos;
        int i;

        // Instruções

        arq = abrirArquivo();
        if (arq != NULL) {
            printf ("GRAUS DE SAIDA DE TODOS OS VERTICES\n\n");
            grauSaidaTodos (arq, &vetorGS);
            rotulosVertices (arq, &vetorRotulos);
            printf ("RESPOSTA:\n\n");
            for (i=0; i<=qtdeVertices(arq)-1; i++) {
                printf ("V%d:\t%d\n", vetorRotulos[i], vetorGS[i]);
            }
            fclose (arq);
        }
        esperarUsuario();
    }

    /// ****************************************************************************************************

    void menuGrauTodos (int tipoGrafo) {

        // Declaração de variáveis
        FILE *arq;
        int *vetorGrau;
        int *vetorRotulos;
        int i;

        // Instruções

        arq = abrirArquivo();
        if (arq != NULL) {
            printf ("GRAUS DE TODOS OS VERTICES\n\n");
            grauTodos (arq, &vetorGrau, tipoGrafo);
            rotulosVertices (arq, &vetorRotulos);
            printf ("RESPOSTA:\n\n");
            for (i=0; i<=qtdeVertices(arq)-1; i++) {
                printf ("V%d:\t%d\n", vetorRotulos[i], vetorGrau[i]);
            }
            fclose (arq);
        }
        esperarUsuario();
    }

    /// ****************************************************************************************************

    void menuGrauTodosCompleto (int tipoGrafo) {

        // Declaração de variáveis
        FILE *arq;
        int *vetorGrau, *vetorGE, *vetorGS;
        int *vetorRotulos;
        int i;

        // Instruções

        arq = abrirArquivo();
        if (arq != NULL) {
            printf ("GRAUS DE ENTRADA, SAIDA E GERAL DE TODOS OS VERTICES\n\n");

            if (tipoGrafo == NAODIRECIONADO) {
                printf ("RESPOSTA: nao faz sentido falar em grau de entrada ou saida em grafos nao direcionados, apenas de"
                        "grau 'simples' de vertice. Exibindo os graus dos vertices do grafo.");
                grauTodos (arq, &vetorGrau, tipoGrafo);
                rotulosVertices (arq, &vetorRotulos);
                printf ("RESPOSTA:\n\n");
                for (i=0; i<=qtdeVertices(arq)-1; i++) {
                    printf ("V%d:\t%d\n", vetorRotulos[i], vetorGrau[i]);
                }
            }
            else {
                grauTodosCompleto (arq, &vetorGE, &vetorGS, &vetorGrau);
                rotulosVertices (arq, &vetorRotulos);
                printf ("RESPOSTA:\n\n");
                printf ("Vert.\tGE\tGS\tGrau\n");
                for (i=0; i<=qtdeVertices(arq)-1; i++) {
                    printf ("V%d:\t%d\t%d\t%d\n", vetorRotulos[i], vetorGE[i], vetorGS[i], vetorGrau[i]);
                }
            }
            fclose (arq);
        }
        esperarUsuario();
    }

    /// ****************************************************************************************************

    void menuInserirVertice () {

        // Declaração de variáveis
        FILE *arq;

        // Instruções

        arq = abrirArquivo();
        if (arq != NULL) {
            printf ("INSERIR VERTICE\n\n");
            if (inserirVertice (arq) == 1) {
                printf ("RESPOSTA: insercao bem sucedida.");
            }
            else {
                printf ("RESPOSTA: a insercao fracassou.");
            }
            printf ("\n");
            fclose (arq);
        }
        esperarUsuario();
    }

    /// ****************************************************************************************************

    void menuRemoverVertice () {

        // Declaração de variáveis
        FILE *arq;
        int vertDesejado;

        // Instruções

        arq = abrirArquivo();
        if (arq != NULL) {
            printf ("REMOVER VERTICE\n\n");
            printf ("Vertice a remover: ");
            scanf ("%d", &vertDesejado);
            if (removerVertice (arq, vertDesejado) == 1) {
                printf ("RESPOSTA: remocao bem sucedida.");
                fclose (arq);
                remove ("Grafo.txt");
                rename ("Grafo_Vertice_Removido.txt", "Grafo.txt");
            }
            else {
                printf ("RESPOSTA: a remocao fracassou.");
                fclose (arq);
            }
            printf ("\n");
        }
        esperarUsuario();
    }

    /// ****************************************************************************************************

    void menuInserirAresta (int tipoGrafo) {

        // Declaração de variáveis
        FILE *arq;
        int vert1;
        int vert2;

        // Instruções

        arq = abrirArquivo();
        if (arq != NULL) {
            printf ("INSERIR ARESTA\n\n");
            if (tipoGrafo == NAODIRECIONADO) {
                printf ("Primeira extremidade da aresta: ");
                scanf ("%d", &vert1);
                printf ("Segunda extremidade da aresta: ");
                scanf ("%d", &vert2);
                printf ("\n");
            }
            else {
                printf ("Vertice de origem: ");
                scanf ("%d", &vert1);
                printf ("Vertice de destino: ");
                scanf ("%d", &vert2);
                printf ("\n");
            }
            if (inserirAresta (arq, vert1, vert2, tipoGrafo) == 1) {
                printf ("RESPOSTA: insercao bem sucedida.");
                fclose (arq);
                remove ("Grafo.txt");
                rename ("Grafo_Aresta_Inserida.txt", "Grafo.txt");

            }
            else {
                printf ("RESPOSTA: a insercao fracassou.");
                fclose (arq);
            }
            printf ("\n");
        }
        esperarUsuario();
    }

    /// ****************************************************************************************************

    void menuRemoverAresta (int tipoGrafo) {

        // Declaração de variáveis
        FILE *arq;
        int vert1;
        int vert2;

        // Instruções

        arq = abrirArquivo();
        if (arq != NULL) {
            printf ("REMOVER ARESTA\n\n");
            if (tipoGrafo == NAODIRECIONADO) {
                printf ("Primeira extremidade da aresta: ");
                scanf ("%d", &vert1);
                printf ("Segunda extremidade da aresta: ");
                scanf ("%d", &vert2);
                printf ("\n");
            }
            else {
                printf ("Vertice de origem: ");
                scanf ("%d", &vert1);
                printf ("Vertice de destino: ");
                scanf ("%d", &vert2);
                printf ("\n");
            }
            if (removerAresta (arq, vert1, vert2, tipoGrafo) == SUCESSO) {
                printf ("RESPOSTA: remocao bem sucedida.");
                fclose (arq);
                remove ("Grafo.txt");
                rename ("Grafo_Aresta_Removida.txt", "Grafo.txt");
            }
            else {
                printf ("RESPOSTA: a remocao fracassou.");
                fclose (arq);
            }
            printf ("\n");
        }
        esperarUsuario();
    }

    /// ****************************************************************************************************

    void menuMatrizAdjCompl () {

        // Declaração de variáveis
        FILE *arq;
        int **matriz;

        // Instruções

        arq = abrirArquivo();
        if (arq != NULL) {
            printf ("MATRIZ DE ADJACENCIA DO GRAFO COMPLEMENTAR\n\n");
            if ((grafoComplementarAdj (arq, &matriz)) == 0) {
                printf ("RESPOSTA: falha na geracao da matriz de adjacencia do grafo complementar.");
            }
            else {
                imprimirMatrizAdj (arq, matriz);
                /* Aqui foi fornecido o ponteiro de arquivo do grafo fonte (e não do grafo complementar) para que não seja
                necessário gerar um arquivo para o grafo complementar. O "lógico" seria fornecer o ponteiro de um
                arquivo do grafo complementar. No entanto, as informações que seriam retiradas desse arquivo seriam iguais
                às obtidas a partir do arquivo do grafo fonte. */
            }
            fclose (arq);
        }
        esperarUsuario();
    }

    /// ****************************************************************************************************

    void menuGrafoComplementarArq () {

        // Declaração de variáveis
        FILE *arq;

        // Instruções

        arq = abrirArquivo();
        if (arq != NULL) {
            printf ("GERACAO DE ARQUIVO DO GRAFO COMPLEMENTAR\n\n");
            if ((grafoComplementarArq (arq)) == 0) {
                printf ("RESPOSTA: falha na geracao do arquivo do grafo complementar.\n");
            }
            else {
                printf ("RESPOSTA: arquivo gerado com sucesso.");
            }
            fclose (arq);
        }
        esperarUsuario();
    }

    /// ****************************************************************************************************

    void menuVetorAdj (int tipoGrafo) {

        // Declaração de variáveis
        FILE *arq;
        int *ptrGrau;
        int *vetorAdjacencia;

        // Instruções

        arq = abrirArquivo();
        if (arq != NULL) {
            printf ("VETOR DE ADJACENCIA\n\n");
            if (gerarVetorAdj (arq, &ptrGrau, &vetorAdjacencia, tipoGrafo) == 0) {
                printf ("RESPOSTA: falha na geracao do vetor de adjacencia.\n");
            }
            else {
                gerarVetorAdj (arq, &ptrGrau, &vetorAdjacencia, tipoGrafo);
                imprimirVetorAdj (arq, ptrGrau, vetorAdjacencia);
            }
        }
        esperarUsuario();
    }

    /// ****************************************************************************************************

    void menuListaAdj (int tipoGrafo) {

        // Declaração de variáveis
        FILE *arq;
        LDDE *listaAdjacencia;

        // Instruções

        arq = abrirArquivo();
        if (arq != NULL) {
            printf ("LISTA DE ADJACENCIA\n\n");
            if ((gerarListaAdj (arq, &listaAdjacencia, tipoGrafo)) == 0) {
                printf ("RESPOSTA: falha na geracao da lista de adjacencia.\n");
                fclose (arq);
            }
            else  {
                printf ("Vert.\tVertices adjacentes\n\n");
                imprimirMultilista (arq, listaAdjacencia);
                fclose (arq);
            }
        }
        esperarUsuario();
    }

    /// ****************************************************************************************************

    void menuComponentesGrafo () {

        // Declaração de variáveis
        FILE *arq;
        // int **matriz;
        // int vertices;
        int componentes;

        // Instruções

        arq = abrirArquivo();
        if (arq != NULL) {
            printf ("NUMERO DE COMPONENTES DO GRAFO\n\n");
            // componentes = qtdeComponentesArq (arq);
            componentes = qtdeComponentes (arq);
            // gerarMatrizAdj (arq, &matriz);
            // vertices = qtdeVertices (arq);
            // componentes = qtdeComponentesAdj (&matriz, vertices);
            if (componentes == -1) {
                printf ("RESPOSTA: falha na contagem do numero de componentes do grafo.\n");
            }
            else if (componentes == 1) {
                printf ("RESPOSTA: o grafo possui apenas 1 componente, portanto e conexo.\n");
            }
            else {
                printf ("RESPOSTA: o grafo possui %d componentes, portanto NAO e conexo.\n", componentes);
            }
            fclose (arq);
        }
        esperarUsuario();
    }

    /// ****************************************************************************************************

    void menuGrafoEuleriano (int tipoGrafo) {

        // Declarações
        FILE *arq;
        int ret;

        // Instruções

        arq = abrirArquivo();
        if (arq != NULL) {
            printf ("VERIFICAR SE O GRAFO E EULERIANO\n\n");
            ret = grafoEuleriano (arq, tipoGrafo);
            printf ("\n");
            if (ret == VERDADEIRO) {
                printf ("RESPOSTA: o grafo e euleriano.\n");
            }
            else {
                printf ("RESPOSTA: o grafo nao e euleriano.\n");
            }
            fclose (arq);
        }
        esperarUsuario();
    }

    /// ****************************************************************************************************

    void menuBuscaEmProfundidade () {

        // Declaração de variáveis
        FILE *arq;
        int ret;
        int *tempoEntrada;
        int *tempoSaida;
        int *pais;
        LDDE *listaArestas;

        // Instruções

        arq = abrirArquivo();
        if (arq != NULL) {
            printf ("APLICAR ALGORITMO DE BUSCA EM PROFUNDIDADE\n\n");
            ret = buscaEmProfundidade (arq, &tempoEntrada, &tempoSaida, &pais, &listaArestas);
            if (ret == FRACASSO) {
                printf ("RESPOSTA: erro na execucao do algoritmo.\n\n");
            }
            imprimirResultadosBFS (arq, &tempoEntrada, &tempoSaida, &pais, &listaArestas);
        }
        fclose (arq);
        esperarUsuario();
    }

    /// ****************************************************************************************************

    void menuListaArestas (int tipoGrafo) {

        // Declaração de variáveis
        FILE *arq;
        LDDE *listaArestas;

        // Instruções

        arq = abrirArquivo();
        if (arq != NULL) {
            printf ("LISTA DE ARESTAS\n\n");
            if ((gerarListaArestas (arq, &listaArestas, tipoGrafo)) == FRACASSO) {
                printf ("RESPOSTA: falha na geracao da lista de arestas.\n");
                fclose (arq);
            }
            else  {
                switch (tipoGrafo) {
                    case NAODIRECIONADO:
                        printf ("Rotulo\tExtr1\tExtr2\tPeso\n");
                        break;
                    case DIRECIONADO:
                        printf ("Rotulo\tOrigem\tDestino\tPeso\n");
                        break;
                }
                imprimirListaArestas (listaArestas);
                fclose (arq);
            }
        }
        esperarUsuario();
    }

    /// ****************************************************************************************************

    void menuListaSucessores () {

        // Declaração de variáveis
        FILE *arq;
        LDDE *listaSucessores;

        // Instruções

        arq = abrirArquivo();
        if (arq != NULL) {
            printf ("LISTA DE SUCESSORES DOS VERTICES\n\n");
            if ((gerarListaSucessores (arq, &listaSucessores)) == 0) {
                printf ("RESPOSTA: falha na geracao da lista de adjacencia.\n");
                fclose (arq);
            }
            else  {
                printf ("Vert.\tVertices sucessores\n\n");
                imprimirMultilista (arq, listaSucessores);
                fclose (arq);
            }
        }
        esperarUsuario();
    }

    /// ****************************************************************************************************

    void menuFechoDireto (void) {

        // Declaração de variáveis
        FILE *arq;
        LDDE *listaFecho;

        // Instruções

        arq = abrirArquivo();
        if (arq != NULL) {
            printf ("FECHO TRANSITIVO DIRETO DOS VERTICES\n\n");
            if (fechoDireto (arq, &listaFecho) == FRACASSO) {
                printf ("RESPOSTA: falha na geracao dos fechos.\n");
                fclose (arq);
            }
            else  {
                printf ("Vert.\tVertices alcancaveis\n\n");
                imprimirMultilista (arq, listaFecho);
                fclose (arq);
            }
        }
        esperarUsuario();
    }

    /// ****************************************************************************************************

    void menuRemoverSentidos (void) {

        // Declaração de variáveis
        FILE *arq;
        int ret;

        // Instruções

        arq = abrirArquivo();
        if (arq != NULL) {
            printf ("REMOVENDO DIRECAO DAS ARESTAS\n\n");
            ret = removerSentidos (arq);
            if (ret == -1) {
                printf ("RESPOSTA: nao foi necessario fazer alteracoes no grafo.\n");
            }
            else if (ret == FRACASSO) {
                printf ("RESPOSTA: falha na geracao do arquivo do grafo modificado.\n");
            }
            else {
                printf ("RESPOSTA: arquivo gerado com sucesso.\n");
            }
            fclose (arq);
        }
        esperarUsuario();
    }

    /// ****************************************************************************************************





    /// ****************************************************************************************************

    /// ****************************************************************************************************

    void menuListarOpcoes (void) {
        printf ("\n------------------------------");
        printf ("\n\nDigite a opcao desejada: \n\n");
        printf ("(%d) Visualizar arquivo de entrada; \n", VER_ARQUIVO);
        printf ("(%d) Gerar matriz de adjacencia; \n", GERAR_MATRIZ_ADJ);
        printf ("(%d) Gerar matriz de incidencia; \n", GERAR_MATRIZ_INCID);
        printf ("(%d) Verificar existencia de arestas paralelas; \n", VERIFICAR_ARESTAS_PARALELAS);
        printf ("(%d) Quantidade de vertices; \n", QTDE_VERTICES);
        printf ("(%d) Quantidade de arestas; \n", QTDE_ARESTAS);
        printf ("(%d) Grau de entrada de um vertice; \n", GRAU_ENTRADA_VERTICE);
        printf ("(%d) Grau de saida de um vertice; \n", GRAU_SAIDA_VERTICE);
        printf ("(%d) Grau de um vertice; \n", GRAU_VERTICE);
        printf ("(%d) Graus de entrada dos vertices; \n", GRAUS_ENTRADA_TODOS);
        printf ("(%d) Graus de saida dos vertices; \n", GRAUS_SAIDA_TODOS);
        printf ("(%d) Graus dos vertices; \n", GRAUS_TODOS);
        printf ("(%d) Graus de entrada, saida e geral dos vertices; \n", GRAUS_TODOS_COMPLETO);
        printf ("(%d) Inserir vertice; \n", INSERIR_VERTICE);
        printf ("(%d) Remover vertice; \n", REMOVER_VERTICE);
        printf ("(%d) Inserir aresta; \n", INSERIR_ARESTA);
        printf ("(%d) Remover aresta; \n", REMOVER_ARESTA);
        printf ("(%d) Gerar matriz de adjacencia do grafo complementar; \n", GERAR_MATRIZ_ADJ_COMPL);
        printf ("(%d) Gerar arquivo do grafo complementar; \n", GERAR_ARQUIVO_COMPL);
        printf ("(%d) Gerar vetor de adjacencia; \n", GERAR_VETOR_ADJ);
        printf ("(%d) Gerar lista de adjacencia; \n", GERAR_LISTA_ADJ);
        printf ("(%d) Numero de componentes do grafo; \n", NUMERO_COMPONENTES);
        printf ("(%d) Verificar se o grafo e euleriano; \n", VERIFICAR_GRAFO_EULERIANO);
        printf ("(%d) Realizar busca em profundidade; \n", BUSCA_PROFUNDIDADE);
        printf ("(%d) Gerar lista de arestas; \n", GERAR_LISTA_ARESTAS);
        printf ("(%d) Gerar lista de sucessores; \n", GERAR_LISTA_SUCESSORES);
        printf ("(%d) Fecho transitivo direto; \n", FECHO_DIRETO );
        printf ("(%d) Remover sentidos das arestas de um grafo direcionado; \n", REMOVER_SENTIDOS);
        printf ("(%d) Sair\n\n", SAIR);
    }

    /// ****************************************************************************************************

    void esperarUsuario (void) {

        // Declaração de variáveis
        char c;

        // Instruções
        do {
            fflush (stdin);
            printf ("\nPressione ENTER para continuar. ");
            c = getc (stdin);
        } while (c != '\n');
    }

    /// ****************************************************************************************************

    void menuDespedida () {
        printf ("Tchau.\n");
        printf ("\n------------------------------\n");
    }

    /// ****************************************************************************************************

    FILE* abrirArquivo (void) {

        // Declaração de variáveis
        FILE *ptr = NULL;

        // Instruções
        ptr = fopen ("Grafo.txt", "r+");
        if (!ptr) {
            printf ("RESPOSTA: erro na abertura do arquivo.\n");
        }
        return (ptr);
    }

    /// ****************************************************************************************************

    int menuGrafoDirecionado (void) {

        // Declaração de variáveis
        FILE *arq;
        int tipo;

        // Instruções
        arq = abrirArquivo();
        if (arq != NULL) {
            printf ("VERIFICANDO SE O GRAFO E DIRECIONADO OU NAO-DIRECIONADO...\n\n");
            tipo = grafoDirecionado(arq);
            fclose (arq);
        }
        return (tipo);
    }
