#include <iostream>

template <typename T>
struct TElemento{
    T dado;
    TElemento* prox;
};

template <typename T>
struct TLista{
    TElemento<T> *inicio;
};

template <typename T>
void inicializa_lista_encadeada(TLista<T> &l, T dado){
    TElemento<T> *novo = new TElemento<T>;
    novo->dado = dado;
    novo->prox = NULL;

    l.inicio = novo;
}

template <typename T>
TElemento<T>* encontrar_ultimo_elemento(TLista<T> &l){
    TElemento<T>* nav = l.inicio;
    while( nav->prox != NULL){
        nav = nav->prox;
    }
    return nav;
}

template <typename T>
void inserir_fim_lista(TLista<T> &lista, T dado){
    if ( lista.inicio == NULL ){
        inicializa_lista_encadeada(lista, dado);
    } else {
        TElemento<T>* ultimo = encontrar_ultimo_elemento(lista);

        TElemento<T>* container = new TElemento<T>;
        container->dado = dado;
        container->prox = NULL;

        if ( ultimo == NULL ){
            ultimo = container;
        } else{
            ultimo->prox = container;
        }
    }
}

template<typename T>
void inserir_no_inicio(TLista<T> &l, T dado){
    if ( lista.inicio == NULL ){
        inicializa_lista_encadeada(lista, dado);
    } else {
        TElemento<T> *novo = new TElemento<T>;
        novo->dado = dado;
        novo->prox = NULL;

        if(l.inicio == NULL){
            l.inicio = novo;
        }
        else{
            novo->prox = l.inicio;
            l.inicio = novo;
        }
    }
}

template<typename T>
void inserir_na_posicao(TLista<T> &l, T dado, int posicao){
    if ( posicao == 0 ) {
        inserir_no_inicio(l, dado);
    } else {
    TElemento<T> *novo = new TElemento<T>;
    novo->dado = dado;
    novo->prox = NULL;

    if(l.inicio == NULL){
        l.inicio = novo;
    }
    else
    {
        int contador = 0;
        for(TElemento<T> *nav = l.inicio; nav != NULL; nav = nav->prox){
            contador++;
        }

        if (posicao - 1 > contador || posicao < 0){
            cout << "Nao pode inserir nessa posicao!";
            return;
        }
        else{
            TElemento<T> *nav = new TElemento<T>;
            nav->prox = l.inicio;
            for(int i = 0; i < posicao; i++){
                cout << nav->dado.nome;
                nav = nav->prox;
            }

            novo->prox = nav->prox;
            nav->prox = novo;
        }
    }}
}

template<typename T>
void imprimir_lista_encadeada(TLista<T> &l){
    TElemento<T> *nav = new TElemento<T>;
    nav = l.inicio;
    if(nav != NULL){
        while(nav->prox != NULL && nav->prox != l.inicio){
            cout << nav->dado << endl;
            nav = nav->prox;
        }
        cout << nav->dado << endl;
    }
}


template<typename T>
void remover_no_inicio(TLista<T> &l){
    TElemento<T> *nav = new TElemento<T>;
    nav = l.inicio;
    l.inicio = nav->prox;
}
    
    

template<typename T>    
void remover_fim_lista(TLista<T> &l){
    TElemento<T> *nav = new TElemento<T>;
    nav = l.inicio;

    while(nav->prox->prox != NULL){
        nav = nav->prox;
    }

    nav->prox = NULL;
}

template<typename T>
void remover_na_posicao(TLista<T> &l, int posicao){
    if ( posicao == 0 ) {
        remover_no_inicio(l);
    } else {
        int contador = 0;
        for(TElemento<T> *nav = l.inicio; nav != NULL; nav = nav->prox){
            contador++;
        }

        if (posicao - 1 > contador || posicao < 0){
            cout << "Nao pode remover nessa posicao!";
            return;
        }
        else{
            TElemento<T> *nav = new TElemento<T>;
            nav->prox = l.inicio;
            for(int i = 0; i < posicao; i++){
                cout << nav->dado.nome;
                nav = nav->prox;
            }

            nav->prox = nav->prox->prox;
        }
    }
}

template<typename T>
T obter_item_lista(TLista<T> &l, int pos){
     TElemento<T> *nav = l.inicio;
    for ( int n = 0; n < pos; n++ ){
        nav = nav->prox;
    }
    return nav->dado;
}


template <typename T>
bool contem_item_lista(TLista<T> &l, T dado){
    TElemento<T> *nav = l.inicio;
    while(nav->prox != NULL){
        nav = nav->prox;
        if (nav->dado == dado)
            return true;
    }
    
    return false;
}
template <typename T>
int obter_indice(TLista<T> &l, T dado){
    TElemento<T> *nav = l.inicio;
    int index = 0;
    while(nav->prox != NULL){
        if (nav->dado == dado)
            return index;
        index++;
        nav = nav->prox;
    }
    if (nav->dado == dado)
        return index;
    return -1;
}


