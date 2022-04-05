#include <iostream>
using namespace std;

template<typename T>
struct TElementoDE {
    T dado;
    TElementoDE<T> *anterior;
    TElementoDE<T> *proximo;
};

template<typename T>
struct TListaDE {
    TElementoDE<T> * inicio;
    TElementoDE<T> * fim;
};

// Inicialização da lista.
template<typename T>
void inicializar_lista_de(TListaDE<T> &lista) {
    lista.inicio = lista.fim = NULL;
}

// Funções de inserção de elementos.

template<typename T>
void inserir_lista_inicio_de(TListaDE<T> &lista, T dado){
        TElementoDE<T>* novo = new TElementoDE<T>;
        novo->dado = dado;
        novo->proximo = lista.inicio;
        novo->anterior = NULL;

        if(lista.inicio == NULL) { // A lista estava vazia
            lista.fim = novo;
        } else {
            lista.inicio->anterior = novo;
        }
        lista.inicio = novo;
}

template<typename T>
void inserir_final_lista_de(TListaDE<T> &lista, T dado){
        TElementoDE<T>* novo = new TElementoDE<T>;
        novo->dado = dado;
        novo->anterior = lista.fim;
        novo->anterior = NULL;

        if(lista.fim == NULL) { // A lista estava vazia
            lista.inicio = novo;
        } else {
            lista.fim->proximo = novo;
        }
        lista.fim = novo;
}

template<typename T>
void inserir_lista_de_posicao(TListaDE<T> &lista,T dado, int posicao) {

    if(posicao < 0) {
        throw "Invalid index";
    }

    if(posicao == 0) { // Inserir no inicio
        inserir_lista_de_inicio(lista, dado);
    } else { // Qualquer posicao > 0
    

    int contador = 0;
    while (nav != NULL && contador < posicao-1) {
        nav = nav->proximo;
        contador++;
    }
    
    TElementoDE<T>* novo = new TElementoDE<T>;
    novo->dado = dado;
    novo->proximo = lista.inicio;
    novo->anterior = NULL;
    
    if(nav != NULL) {
        novo->proximo = nav->proximo;
        novo->anterior = nav;

        if(nav->proximo == NULL) { // O NAV é o ultimo, nada depois
            lista.fim = novo;
        } else {
            nav->proximo->anterior = novo;
        }
        nav->proximo = novo;
    } else {
        throw "Invalid index";
      }
    }
  }

// Funções de remoção de elementos.

template<typename T>
void remover_inicio_lista_de(TListaDE<T> &l){
    if ( l.inicio != NULL ){
        l.inicio->anterior = NULL;
        l.inicio = l.inicio->proximo;
    }
}    

template<typename T>
void remover_final_lista_de(TListaDE<T> &l){
    if ( l.fim->anterior == NULL ) {
        remover_inicio_lista_de(l);
    } else if ( l.fim != NULL ){
        l.fim->anterior->proximo = NULL;
        l.fim = l.fim->anterior;
    }
}    

template <typename T>
void remover_lista_de_posicao(TListaDE<T> &l, int posicao){

    if(posicao < 0){
        cout << "Invalid Index";
    }

    if(posicao == 0){
        remover_inicio_lista_de(l);
    }
    else{
        TElementoDE<T>* nav = l.inicio;
        for (int n = 0; n < posicao; n++ ) {
            nav = nav->proximo;
        }
        nav->proximo->anterior = nav->anterior;
        nav->anterior->proximo = nav->proximo;
    }


}

// Funções de impressão e obtenção de dados. 

template<typename T>
void imprimir_lista_de(TListaDE<T> l) {
    cout << "Depurando lista dupla = inicio: " << l.inicio << endl;
    TElementoDE<T>* nav = l.inicio;
    if ( nav != NULL ){
        while (nav != NULL) {
            cout << nav->dado << endl;
            nav = nav->proximo;
        };
    } else {
        cout << "A lista dupla esta vazia." << endl;
    }
}

template<typename T>
T obter_item_lista_de(TListaDE<T> &l, int pos){
     TElementoDE<T> *nav = l.inicio;
    for ( int n = 0; n < pos; n++ ){
        nav = nav->proximo;
    };
    return nav->dado;
}

// Verificação se elemento pertence a lista.
template <typename T>
bool contem_item_lista_de(TListaDE<T> l, T dado){
    TElementoDE<T> *nav = l.inicio;
    for (int i = 0; nav->proximo != NULL; i++){
        if(nav->dado == dado){
            return true;
        }
        nav = nav->proximo;
    }
    return false;
}

// Obtenção do índice do elemento na lista.
template <typename T>
int obter_indice_de(TListaDE<T> &l, T dado){
    TElementoDE<T> *nav = l.inicio;
    int index = 0;
    while(nav->proximo != NULL){
        if (nav->dado == dado)
            return index;
        index++;
        nav = nav->proximo;
    }
    if (nav->dado == dado)
        return index;
    return -1;
}