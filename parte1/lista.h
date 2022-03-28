//lista.h

#ifndef LISTA_H
#define LISTA_H
using namespace std;

template<typename T>
struct TElemento {
    T dado;
};

template<typename TIPO, int CAPACIDADE>
struct TListaEstatica {
    TElemento<TIPO> vetor[CAPACIDADE];
    int quantidade;
};

template <typename T, int MAX>
void inicializar_lista_estatica(TListaEstatica<T, MAX> &l){
    l.quantidade = 0;
}

template <typename T, int MAX>
void inserir_fim_lista_estatica(TListaEstatica<T,MAX> &l, T c) {
    if(l.quantidade >= MAX) {
        throw "List Overflow";
    }
    TElemento<T> container;
    container.dado = c;
    l.vetor[l.quantidade] = container;
    l.quantidade++;
}

template<typename T, int MAX>
void inserir_inicio_lista_estatica(TListaEstatica<T,MAX> &l, T c) {
    if(l.quantidade >= MAX) {
        throw "List Overflow";
    }

    for(int i = l.quantidade; i>0; i--) {
        l.vetor[i] = l.vetor[i-1];
    }
    TElemento<T> container;
    container.dado = c;
    l.quantidade++;
}

template<typename T, int MAX>
void inserir_posicao_lista_estatica(TListaEstatica<T,MAX> &l, T c, int posicao) {
    if(l.quantidade >= MAX) {
        throw "List Overflow";
    }
    if(posicao < 0 || posicao > l.quantidade) {
        throw "Invalid Index";
    }
    for(int i = l.quantidade; i > posicao; i--) {
        l.vetor[i] = l.vetor[i-1];
    }

    TElemento<T> container;
    container.dado = c;
    l.vetor[posicao] = container;
    l.quantidade++;
}

template<typename T, int MAX>
void remover_fim_lista_estatica(TListaEstatica<T,MAX> &l) {
    if(l.quantidade <= 0)
        cout << "A lista já está vazia!";
    else 
        l.quantidade--;    
}

template<typename T, int MAX>
void remover_inicio_lista_estatica(TListaEstatica<T,MAX> &l) { 
    if(l.quantidade <= 0)
        cout << "A lista já está vazia!";
    else {
        for(int i = l.quantidade; i > 1; i--){
            l.vetor[i - 1] = l.vetor[i];
        }
    }
}

template<typename T, int MAX>
void remover_posicao_lista_estatica(TListaEstatica<T,MAX> &l, int posicao) { 
    if(l.quantidade <= 0 || posicao >= l.quantidade)
        cout << "Index out of range";

    for(int i = l.quantidade; i > posicao; i--){
        l.vetor[i - 1] = l.vetor[i];
    }
    l.quantidade--;
}

#include <iostream>

template<typename T, int MAX>
void imprimir_lista(TListaEstatica<T,MAX> &l) {
    for(int i = 0; i < l.quantidade; i++) {
        std::cout << l.vetor[i].dado << std::endl;
    }
}

template<typename T, int MAX>
T obter_ultimo_dado(TListaEstatica<T,MAX> l) {
    return l.vetor[l.quantidade-1].dado;
}

template<typename T, int MAX>
T obter_posicao_dado(TListaEstatica<T,MAX> l, int posicao) {
    if(posicao < 0 || posicao >= l.quantidade) {
        throw "Invalid Index";
    }
    return l.vetor[l.quantidade-1].dado;
}

//TODO: CONTÊM CARTA
template<typename T, int MAX>
bool percente_a_lista( TListaEstatica<T, MAX> &l, T dado ){
    for( int i = 0; i <l.quantidade; i++ ){
        if( l.vetor[i].dado == dado ){
            return true;
        }
    }
    return false;
}

//TODO: DESCOBRIR INDICE
template<typename T, int MAX>
int obter_o_indice( TListaEstatica<T, MAX> &l, T dado ){
    for( int i = 0; i <l.quantidade; i++ ){
        if( l.vetor[i].dado == dado ){
            return i;
        }
    }
    return -1;
}

//TODO: 
#endif // LISTA_H
