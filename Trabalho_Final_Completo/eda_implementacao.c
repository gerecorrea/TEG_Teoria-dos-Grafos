# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "eda_implementacao.h"
# include "estruturasdedados.h"

    /*
    int main() {
        return (0);
    }
    */

    /// ****************************************************************************************************

    /// FUNÇÕES DE PILHA DINÂMICA SIMPLESMENTE ENCADEADA

    int criarPDSE (PDSE **pp, unsigned int sizeInfo) {

        // Declaração de variáveis
        PDSE *ptr;

        // Instruções
        ptr = (PDSE*) malloc (1 * sizeof (PDSE));
        if (!ptr) {
            return (FRACASSO);
        }
        ptr->topo = NULL;
        ptr->tamInfo = sizeInfo;
        *pp = ptr;
        return (SUCESSO);
    }

    int inserirElemPDSE (PDSE *p, void *novo) {

        // Declaração de variáveis
        noPDSE *temp;

        // Instruções
        temp = (noPDSE*) malloc (1 * sizeof (noPDSE));
        if (!temp) {
            free (temp);
            return (FRACASSO);
        }
        temp->dados = malloc (1 * p->tamInfo);
        if (!temp->dados) {
            free (temp->dados);
            free (temp);
            return (FRACASSO);
        }
        memcpy (temp->dados, novo, p->tamInfo);
        if (p->topo == NULL) {
            p->topo = temp;
            temp->abaixo = NULL;
        }
        else {
            temp->abaixo = p->topo;
            p->topo = temp;
        }
        return (SUCESSO);
    }

    int removerElemPDSE (PDSE *p) {

        // Declaração de variáveis
        noPDSE *aux;

        // Instruções

        if (p->topo == NULL) {
            return (FRACASSO);
        }
        else {
            aux = p->topo;
            p->topo = aux->abaixo;
            free (aux->dados);
            free (aux);
            return (SUCESSO);
        }
    }

    int buscarElemPDSE (PDSE *p, void *reg) {

        // Instruções
        if (p->topo == NULL) {
            return (FRACASSO);
        }
        else {
            memcpy (reg, p->topo->dados, p->tamInfo);
            return (SUCESSO);
        }
    }

    /*
    void imprimirPDSE (PDSE *p) {

        // Declaração de variáveis
        noPDSE *aux;

        // Instruções
        aux = p->topo;
        if (aux == NULL) {
            printf ("Pilha vazia.\n");
        }
        else {
            printf ("%f\n", *(aux->dados));
            while (aux->abaixo != NULL) {
                aux = aux->abaixo;
                printf ("%f\n", *(aux->dados));
            }
        }
    }
    */

    int tamanhoPDSE (PDSE *p) {

        // Declação de variáveis
        int tamanho = 0;
        noPDSE *aux;

        // Instruções
        aux = p->topo;
        if (aux == NULL) {
            return (tamanho);
        }
        else {
            tamanho++;
            while (aux->abaixo != NULL) {
                aux = aux->abaixo;
                tamanho++;
            }
            return (tamanho);
        }
    }

    int testeVaziaPDSE (PDSE *p) {

        if (tamanhoPDSE(p) == 0) {
            return (SUCESSO);
        }
        else {
            return (FRACASSO);
        }
    }

    int reiniciarPDSE (PDSE *p) {

        // Declaração de variáveis
        noPDSE *aux;

        // Instruções
        if (p->topo == NULL) {
            return (FRACASSO);
        }
        else {
            while (p->topo != NULL) {
                aux = p->topo->abaixo;
                free (p->topo->dados);
                free (p->topo);
                p->topo = aux;
            }
            return (SUCESSO);
        }
    }

    int destruirPDSE (PDSE **p) {

        // Declaração de variáveis
        noPDSE *aux;

        // Instruções
        while ((*p)->topo != NULL) {
            aux = (*p)->topo->abaixo;
            free ((*p)->topo->dados);
            free ((*p)->topo);
            (*p)->topo = aux;
        }
        free (*p);
        (*p) = NULL;
        return (SUCESSO);
    }


    /// ****************************************************************************************************

    /// FUNÇÕES DE FILA DINÂMICA DUPLAMENTE ENCADEADA

    int criarFDDE (FDDE **pp, unsigned int sizeInfo) {

        // Declaração de variáveis
        FDDE *ptr;

        // Instruções
        ptr = (FDDE*) malloc (1 * sizeof (FDDE));
        if (!ptr) {
            return (FRACASSO);
        }
        ptr->primeiro = NULL;
        ptr->ultimo = NULL;
        ptr->tamInfo = sizeInfo;
        *pp = ptr;
        return (SUCESSO);
    }

    int inserirElemFDDE (FDDE *p, void *novo) {

        // Declaração de variáveis
        noFDDE *temp;

        // Instruções
        temp = (noFDDE*) malloc (1 * sizeof (noFDDE));
        if (!temp) {
            free (temp);
            return (FRACASSO);
        }
        temp->dados = (void*) malloc (1 * p->tamInfo);
        if (!temp->dados) {
            free (temp->dados);
            free (temp);
            return (FRACASSO);
        }
        memcpy (temp->dados, novo, p->tamInfo);
        if (p->ultimo == NULL) {
            p->ultimo = temp;
            p->primeiro = temp;
            temp->tras = NULL;
            temp->frente = NULL;
        }
        else {
            temp->frente = p->ultimo;
            temp->tras = NULL;
            p->ultimo->tras = temp;
            p->ultimo = temp;
        }
        return (SUCESSO);
    }

    int removerElemFDDE (FDDE *p) {

        // Declaração de variáveis
        noFDDE *aux;

        // Instruções

        if (p->primeiro == NULL) {
            return (FRACASSO);
        }
        else if (p->primeiro == p->ultimo) {
            free (p->primeiro->dados);
            free (p->primeiro);
            p->primeiro = NULL;
            p->ultimo = NULL;
        }
        else {
            aux = p->primeiro;
            p->primeiro = aux->tras;
            aux->tras->frente = NULL;
            free (aux->dados);
            free (aux);
        }
        return (SUCESSO);
    }

    int buscarComecoFDDE (FDDE *p, void *reg) {

        // Instruções
        if (p->primeiro == NULL) {
            return (FRACASSO);
        }
        else {
            memcpy (reg, p->primeiro->dados, p->tamInfo);
            return (SUCESSO);
        }
    }

    int buscarFimFDDE (FDDE *p, void *reg) {

        // Instruções
        if (p->ultimo == NULL) {
            return (FRACASSO);
        }
        else {
            memcpy (reg, p->ultimo->dados, p->tamInfo);
            return (SUCESSO);
        }
    }

    /*
    void imprimirFDDE (FDDE *p) {

        // Declaração de variáveis
        noFDDE *aux;

        // Instruções
        aux = p->primeiro;
        if (aux == NULL) {
            printf ("Fila vazia.\n");
        }
        else {
            printf ("%f\n", *(aux->dados));
            while (aux->tras != NULL) {
                aux = aux->tras;
                printf ("%f\n", *(aux->dados));
            }
        }
    }
    */

    int tamanhoFDDE (FDDE *p) {

        // Declação de variáveis
        int tamanho = 0;
        noFDDE *aux;

        // Instruções
        aux = p->primeiro;
        if (aux == NULL) {
            return (tamanho);
        }
        else {
            tamanho++;
            while (aux->tras != NULL) {
                aux = aux->tras;
                tamanho++;
            }
            return (tamanho);
        }
    }

    int testeVaziaFDDE (FDDE *p) {

        if (tamanhoFDDE(p) == 0) {
            return (SUCESSO);
        }
        else {
            return (FRACASSO);
        }
    }

    int reiniciarFDDE (FDDE *p) {

        // Declaração de variáveis
        noFDDE *aux;

        // Instruções
        if (p->primeiro == NULL) {
            return (FRACASSO);
        }
        else {
            while (p->primeiro != p->ultimo) {
                aux = p->primeiro->tras;
                aux->frente = NULL;
                free (p->primeiro->dados);
                free (p->primeiro);
                p->primeiro = aux;
            }
            free (p->primeiro->dados);
            free (p->primeiro);
            p->primeiro = NULL;
            p->ultimo = NULL;
            return (SUCESSO);
        }
    }

    int destruirFDDE (FDDE **p) {

        // Declaração de variáveis
        noFDDE *aux;

        // Instruções
        while ((*p)->primeiro != NULL) {
            aux = (*p)->primeiro->tras;
            free ((*p)->primeiro->dados);
            free ((*p)->primeiro);
            (*p)->primeiro = aux;
        }
        free (*p);
        (*p) = NULL;
        return (SUCESSO);
    }

    /// ****************************************************************************************************

    /// FUNÇÕES DE LISTA DINÂMICA DUPLAMENTE ENCADEADA

    int criarLDDE (LDDE **pp, unsigned int sizeInfo) {

        // Declaração de variáveis
        LDDE *ptr;

        // Instruções
        ptr = (LDDE*) malloc (1 * sizeof (LDDE));
        if (!ptr) {
            return (FRACASSO);
        }
        ptr->primeiro = NULL;
        ptr->ultimo = NULL;
        ptr->tamInfo = sizeInfo;
        *pp = ptr;
        return (SUCESSO);
    }

    int inserirComecoLDDE (LDDE *p, void *novo) {

        // Declaração de variáveis
        noLDDE *temp;

        // Instruções
        temp = (noLDDE*) malloc (1 * sizeof (noLDDE));
        if (!temp) {
            free (temp);
            return (FRACASSO);
        }
        temp->dados = (void*) malloc (1 * p->tamInfo);
        if (!temp->dados) {
            free (temp->dados);
            free (temp);
            return (FRACASSO);
        }
        memcpy (temp->dados, novo, p->tamInfo);
        if (p->primeiro == NULL) {
            p->primeiro = temp;
            p->ultimo = temp;
            temp->tras = NULL;
            temp->frente = NULL;
        }
        else {
            temp->tras = p->primeiro;
            temp->frente = NULL;
            p->primeiro->frente = temp;
            p->primeiro = temp;
        }
        return (SUCESSO);
    }

    int inserirPosLogLDDE (LDDE *p, void *novo, unsigned int posLog) {

        // Declaração de variáveis
        noLDDE *temp;
        noLDDE *aux;
        int i;

        // Instruções

        // Criando o nó que será inserido
        temp = (noLDDE*) malloc (1 * sizeof (noLDDE));
        if (!temp) {
            free (temp);
            return (FRACASSO);
        }
        temp->dados = (void*) malloc (1 * p->tamInfo);
        if (!temp->dados) {
            free (temp->dados);
            free (temp);
            return (FRACASSO);
        }
        memcpy (temp->dados, novo, p->tamInfo);

        // Inserindo o nó criado na lista
        if ((posLog < 0) ||  (posLog >= tamanhoLDDE(p)+1)) {
            return (FRACASSO);
        }
        else if (posLog == 0) {
            inserirComecoLDDE (p, novo);
        }
        else if (posLog == tamanhoLDDE(p)) {
            inserirFimLDDE (p, novo);
        }
        else {
            aux = p->primeiro;
            for (i=0; i<=posLog-1; i++) {
                aux = aux->tras;
            }
            temp->tras = aux;
            temp->frente = aux->frente;
            aux->frente->tras = temp;
            aux->frente = temp;
        }
        return (SUCESSO);
    }

    int inserirFimLDDE (LDDE *p, void *novo) {

        // Declaração de variáveis
        noLDDE *temp;

        // Instruções
        temp = (noLDDE*) malloc (1 * sizeof (noLDDE));
        if (!temp) {
            free (temp);
            return (FRACASSO);
        }
        temp->dados = (void*) malloc (1 * p->tamInfo);
        if (!temp->dados) {
            free (temp->dados);
            free (temp);
            return (FRACASSO);
        }
        memcpy (temp->dados, novo, p->tamInfo);
        if (p->ultimo == NULL) {
            p->ultimo = temp;
            p->primeiro = temp;
            temp->tras = NULL;
            temp->frente = NULL;
        }
        else {
            temp->frente = p->ultimo;
            temp->tras = NULL;
            p->ultimo->tras = temp;
            p->ultimo = temp;
        }
        return (SUCESSO);
    }

    int removerComecoLDDE (LDDE *p) {

        // Declaração de variáveis
        noLDDE *aux;

        // Instruções

        if (p->primeiro == NULL) {
            return (FRACASSO);
        }
        else if (p->primeiro == p->ultimo) {
            free (p->primeiro->dados);
            free (p->primeiro);
            p->primeiro = NULL;
            p->ultimo = NULL;
        }
        else {
            aux = p->primeiro;
            p->primeiro = aux->tras;
            aux->tras->frente = NULL;
            free (aux->dados);
            free (aux);
        }
        return (SUCESSO);
    }

    int removerPosLogLDDE (LDDE *p, unsigned int posLog) {

        // Declaração de variáveis
        noLDDE *aux;
        int i;

        // Instruções
        if ((posLog < 0) || (posLog >= tamanhoLDDE(p))) {
            return (FRACASSO);
        }
        else if (posLog == 0) {
            removerComecoLDDE (p);
        }
        else if (posLog == tamanhoLDDE(p)-1) {
            removerFimLDDE (p);
        }
        else {
            aux = p->primeiro;
            for (i=0; i<=posLog-1; i++) {
                aux = aux->tras;
            }
            aux->frente->tras = aux->tras;
            aux->tras->frente = aux->frente;
            free (aux->dados);
            free (aux);
        }
        return (SUCESSO);
    }

    int removerFimLDDE (LDDE *p) {

        // Declaração de variáveis
        noLDDE *aux;

        // Instruções

        if (p->ultimo == NULL) {
            return (FRACASSO);
        }
        else if (p->primeiro == p->ultimo) {
            free (p->ultimo->dados);
            free (p->ultimo);
            p->primeiro = NULL;
            p->ultimo = NULL;
        }
        else {
            aux = p->ultimo;
            p->ultimo = aux->frente;
            aux->frente->tras = NULL;
            free (aux->dados);
            free (aux);
        }
        return (SUCESSO);
    }

    int buscarComecoLDDE (LDDE *p, void *reg) {

        // Instruções
        if (p->primeiro == NULL) {
            return (FRACASSO);
        }
        else {
            memcpy (reg, p->primeiro->dados, p->tamInfo);
            return (SUCESSO);
        }
    }

    int buscarPosLogLDDE (LDDE *p, void *reg, unsigned int posLog) {

        // Declaração de variáveis
        noLDDE *aux;
        int i;

        // Instruções

        if ((posLog < 0) || (posLog >= tamanhoLDDE(p))) {
            return (FRACASSO);
        }
        else if (posLog == 0) {
            buscarComecoLDDE (p, reg);
        }
        else if (posLog == tamanhoLDDE(p)-1) {
            buscarFimLDDE (p, reg);
        }
        else {
            aux = p->primeiro;
            for (i=0; i<=posLog-1; i++) {
                aux = aux->tras;
            }
            memcpy (reg, aux->dados, p->tamInfo);
        }
        return (SUCESSO);
    }

    int buscarFimLDDE (LDDE *p, void *reg) {

        // Instruções
        if (p->ultimo == NULL) {
            return (FRACASSO);
        }
        else {
            memcpy (reg, p->ultimo->dados, p->tamInfo);
            return (SUCESSO);
        }
    }

    /*
    void imprimirLDDE (LDDE *p) {

        // Declaração de variáveis
        noLDDE *aux;

        // Instruções
        aux = p->primeiro;
        if (aux == NULL) {
            printf ("Lista vazia.\n");
        }
        else {
            printf ("%f\n", *(aux->dados));
            while (aux->tras != NULL) {
                aux = aux->tras;
                printf ("%f\n", *(aux->dados));
            }
        }
    }
    */

    int tamanhoLDDE (LDDE *p) {

        // Declação de variáveis
        int tamanho = 0;
        noLDDE *aux;

        // Instruções
        aux = p->primeiro;
        if (aux == NULL) {
            return (tamanho);
        }
        else {
            tamanho++;
            while (aux->tras != NULL) {
                aux = aux->tras;
                tamanho++;
            }
            return (tamanho);
        }
    }

    int testeVaziaLDDE (LDDE *p) {

        if (tamanhoLDDE(p) == 0) {
            return (SUCESSO);
        }
        else {
            return (FRACASSO);
        }
    }

    int reiniciarLDDE (LDDE *p) {

        // Declaração de variáveis
        noLDDE *aux;

        // Instruções
        if (p->primeiro == NULL) {
            return (FRACASSO);
        }
        else {
            while (p->primeiro != p->ultimo) {
                aux = p->primeiro->tras;
                aux->frente = NULL;
                free (p->primeiro->dados);
                free (p->primeiro);
                p->primeiro = aux;
            }
            free (p->primeiro->dados);
            free (p->primeiro);
            p->primeiro = NULL;
            p->ultimo = NULL;
            return (SUCESSO);
        }
    }

    int destruirLDDE (LDDE **p) {

        // Declaração de variáveis
        noLDDE *aux;

        // Instruções
        while ((*p)->primeiro != NULL) {
            aux = (*p)->primeiro->tras;
            free ((*p)->primeiro->dados);
            free ((*p)->primeiro);
            (*p)->primeiro = aux;
        }
        free (*p);
        (*p) = NULL;
        return (SUCESSO);
    }

