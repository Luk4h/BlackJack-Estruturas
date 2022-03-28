#ifndef CARTA_H
#define CARTA_H

#include <iostream>
#include "lista.h"
#include "time.h"
using namespace std;

struct TCarta {
    int naipe;
    int valor;
};


const string NAIPES[]={"Espada", "Copas", "Ouros", "Paus"};

ostream& operator <<(ostream &os, TCarta c) {
    os << "Carta{ naipe: " << NAIPES[c.naipe] << ", valor: "
       << c.valor << "}";
    return os;
}

TListaEstatica<TCarta,52> criar_baralho() {
    TListaEstatica<TCarta,52> baralho;
    inicializar_lista_estatica(baralho);

    for(int i = 0; i < 52; i++) {
        TCarta carta;
        carta.naipe = i / 13;
        carta.valor = (i % 13) + 1;
        inserir_fim_lista_estatica(baralho, carta);
    }
    return baralho;
}

template<typename T, int MAX>
void imprimir_baralho(TListaEstatica<T, MAX> &l){
        for(int i = 0; i < l.quantidade; i++) {
        std::cout << l.vetor[i].dado << std::endl;
    }
}

void imprimir_carta(TCarta &carta){
    std::cout << carta << std::endl;
}

#include <algorithm>
#include <vector>
template<typename T, int MAX>
void trocar_posicoes_lista_estatica(TListaEstatica<T,MAX> &l, int pos1, int pos2) {

    TElemento<T> aux = l.vetor[pos1];
    l.vetor[pos1] = l.vetor[pos2];
    l.vetor[pos2] = aux;

}


void embaralhar(TListaEstatica<TCarta,52> &baralho) {
    srand(time(NULL));

    for(int i = 0; i < 26; i++) {
        int posicao1 = rand() % 52;
        int posicao2 = rand() % 52;
        trocar_posicoes_lista_estatica(baralho,posicao1,posicao2);
    }
}

bool operator == (TCarta c1, TCarta c2) {
    if ( c1.valor == c2.valor && c1.naipe == c2.naipe ) {
        return true;
    } else {
        return false;
    }
}

#endif // CARTA_H
