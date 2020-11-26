#ifndef EDA_IMPLEMENTACAO_H_INCLUDED
#define EDA_IMPLEMENTACAO_H_INCLUDED

    /// ****************************************************************************************************

    // DEFINES

    # define FRACASSO 0
    # define SUCESSO 1

    /// ****************************************************************************************************

    /// ESTRUTURAS BÁSICAS PARA PILHA DINÂMICA SIMPLESMENTE ENCADEADA

    // Nó da pilha
    struct NoPDSE {
        void *dados;
        struct NoPDSE *abaixo;
    };
    typedef struct NoPDSE noPDSE;

    // Descritor da pilha
    struct descritorPDSE {
        struct NoPDSE *topo;
        unsigned int tamInfo;
    };
    typedef struct descritorPDSE PDSE;

    /// ****************************************************************************************************

    /// ESTRUTURAS BÁSICAS PARA FILA DINÂMICA DUPLAMENTE ENCADEADA

    // Nó da fila
    struct NoFDDE {
        void *dados;
        struct NoFDDE *frente;
        struct NoFDDE *tras;
    };
    typedef struct NoFDDE noFDDE;

    // Descritor da fila
    struct descritorFDDE {
        struct NoFDDE *primeiro;
        struct NoFDDE *ultimo;
        unsigned int tamInfo;
    };
    typedef struct descritorFDDE FDDE;

    /// ****************************************************************************************************

    /// ESTRUTURAS BÁSICAS PARA LISTA DINÂMICA DUPLAMENTE ENCADEADA

    // Nó da fila
    struct NoLDDE {
        void *dados;
        struct NoLDDE *frente;
        struct NoLDDE *tras;
    };
    typedef struct NoLDDE noLDDE;

    // Descritor da fila
    struct descritorLDDE {
        struct NoLDDE *primeiro;
        struct NoLDDE *ultimo;
        unsigned int tamInfo;
    };
    typedef struct descritorLDDE LDDE;

#endif // EDA_IMPLEMENTACAO_H_INCLUDED
