#ifndef FUNCOES_MENU_H_INCLUDED
#define FUNCOES_MENU_H_INCLUDED

    // DEFINES

    # define SUCESSO 1
    # define FRACASSO 0
    # define FRACASSO_ESPECIAL -1

    # define NAODIRECIONADO 0
    # define DIRECIONADO 1

    # define FALSO 0
    # define VERDADEIRO 1


    // Opções do menu
    # define VER_ARQUIVO                        1
    # define GERAR_MATRIZ_ADJ                   2
    # define GERAR_MATRIZ_INCID                 3
    # define VERIFICAR_ARESTAS_PARALELAS        4
    # define QTDE_VERTICES                      5
    # define QTDE_ARESTAS                       6
    # define GRAU_ENTRADA_VERTICE               7
    # define GRAU_SAIDA_VERTICE                 8
    # define GRAU_VERTICE                       9
    # define GRAUS_ENTRADA_TODOS                10
    # define GRAUS_SAIDA_TODOS                  11
    # define GRAUS_TODOS                        12
    # define GRAUS_TODOS_COMPLETO               13
    # define INSERIR_VERTICE                    14
    # define REMOVER_VERTICE                    15
    # define INSERIR_ARESTA                     16
    # define REMOVER_ARESTA                     17
    # define GERAR_MATRIZ_ADJ_COMPL             18
    # define GERAR_ARQUIVO_COMPL                19
    # define GERAR_VETOR_ADJ                    20
    # define GERAR_LISTA_ADJ                    21
    # define NUMERO_COMPONENTES                 22
    # define VERIFICAR_GRAFO_EULERIANO          23
    # define BUSCA_PROFUNDIDADE                 24
    # define GERAR_LISTA_ARESTAS                25
    # define GERAR_LISTA_SUCESSORES             26
    # define FECHO_DIRETO                       27
    # define QTDE_COMPONENTES                   28
    # define REMOVER_SENTIDOS                   29
    # define SAIR                               40

    // FUNÇÕES DE MENU

    FILE* abrirArquivo (void);
    void menuVerArquivo (void);
    void menuListarOpcoes (void);
    void menuMatrizAdj (void);
    void menuMatrizIncid (int tipoGrafo);
    void menuArestasParalelas (void);
    void menuQuantidadeVertices (void);
    void menuQuantidadeArestas (int tipoGrafo);
    void menuGrauEntradaVertice (void);
    void menuGrauSaidaVertice (void);
    void menuGrauVertice (void);
    void menuGrauEntradaTodos (void);
    void menuGrauSaidaTodos (void);
    void menuGrauTodos (int tipoGrafo);
    void menuGrauTodosCompleto (int tipoGrafo);
    void menuInserirVertice (void);
    void menuRemoverVertice (void);
    void menuInserirAresta (int tipoGrafo);
    void menuRemoverAresta (int tipoGrafo);
    void menuMatrizAdjCompl (void);
    void menuGrafoComplementarArq (void);
    void menuVetorAdj (int tipoGrafo);
    void menuListaAdj (int tipoGrafo);
    void menuComponentesGrafo (void);
    void menuGrafoEuleriano (int tipoGrafo);
    void menuBuscaEmProfundidade (void);
    int menuGrafoDirecionado (void);
    void esperarUsuario (void);
    void menuDespedida (void);
    void menuListaArestas (int tipoGrafo);
    void menuListaSucessores (void);
    void menuFechoDireto (void);
    void menuRemoverSentidos (void);

#endif // FUNCOES_MENU_H_INCLUDED
