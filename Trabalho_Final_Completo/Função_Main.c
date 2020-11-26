# include <stdio.h>
# include <stdlib.h>
# include "Protótipos_Funções.h"
# include "estruturasdedados.h"
# include "funcoes_menu.h"

/*
Desenvolvido pelos alunos Geremias Corrêa e Rafael de Melo
*/

int main() {

    // Declaração de variáveis
    int opcaoEscolhida;
    int tipoGrafo;

    // Instruções

    printf ("Aluno: Geremias Corrêa");
    printf ("\n------------------------------\n\n");
    tipoGrafo = menuGrafoDirecionado();

    while (1) {

        menuListarOpcoes ();
        printf ("OPCAO: ");
        scanf ("%d", &opcaoEscolhida);
        fflush (stdin);
        printf ("\n------------------------------\n\n");

        // Execução da opção escolhida

        switch (opcaoEscolhida) {
            case VER_ARQUIVO:
                menuVerArquivo ();
                break;
            case GERAR_MATRIZ_ADJ:
                menuMatrizAdj ();
                break;
            case GERAR_MATRIZ_INCID:
                menuMatrizIncid (tipoGrafo);
                break;
            case VERIFICAR_ARESTAS_PARALELAS:
                menuArestasParalelas();
                break;
            case QTDE_VERTICES:
                menuQuantidadeVertices();
                break;
            case QTDE_ARESTAS:
                menuQuantidadeArestas (tipoGrafo);
                break;
            case GRAU_ENTRADA_VERTICE:
                menuGrauEntradaVertice();
                break;
            case GRAU_SAIDA_VERTICE:
                menuGrauSaidaVertice();
                break;
            case GRAU_VERTICE:
                menuGrauVertice();
                break;
            case GRAUS_ENTRADA_TODOS:
                menuGrauEntradaTodos();
                break;
            case GRAUS_SAIDA_TODOS:
                menuGrauSaidaTodos();
                break;
            case GRAUS_TODOS:
                menuGrauTodos (tipoGrafo);
                break;
            case GRAUS_TODOS_COMPLETO:
                menuGrauTodosCompleto (tipoGrafo);
                break;
            case INSERIR_VERTICE:
                menuInserirVertice();
                break;
            case REMOVER_VERTICE:
                menuRemoverVertice();
                break;
            case INSERIR_ARESTA:
                menuInserirAresta (tipoGrafo);
                break;
            case REMOVER_ARESTA:
                menuRemoverAresta (tipoGrafo);
                break;
            case GERAR_MATRIZ_ADJ_COMPL:
                menuMatrizAdjCompl();
                break;
            case GERAR_ARQUIVO_COMPL:
                menuGrafoComplementarArq();
                break;
            case GERAR_VETOR_ADJ:
                menuVetorAdj (tipoGrafo);
                break;
            case GERAR_LISTA_ADJ:
                menuListaAdj (tipoGrafo);
                break;
            case NUMERO_COMPONENTES:
                menuComponentesGrafo();
                break;
            case VERIFICAR_GRAFO_EULERIANO:
                menuGrafoEuleriano (tipoGrafo);
                break;
            case BUSCA_PROFUNDIDADE:
                menuBuscaEmProfundidade();
                break;
            case GERAR_LISTA_ARESTAS:
                menuListaArestas (tipoGrafo);
                break;
            case GERAR_LISTA_SUCESSORES:
                menuListaSucessores();
                break;
            case FECHO_DIRETO:
                menuFechoDireto();
                break;
            case REMOVER_SENTIDOS:
                menuRemoverSentidos();
                break;
            case SAIR:
                menuDespedida();
                return (0);
            default:
                printf ("Opcao invalida. Digite novamente.\n");
                esperarUsuario();
        }
    }
}


