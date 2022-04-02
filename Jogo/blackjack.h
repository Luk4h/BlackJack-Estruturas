#include <iostream>
#include <string>
#include "lista-encadeada-dupla.h"
#include "lista-encadeada-simples.h"
#include "lista-estatica.h"

using namespace std;
// Baralho: Lista Estatica
// Jogadores: Lista encadeada (simples circular?)
// Mão: Lista Estatica
std::string arr_naipes[4] = {
    "Ouro",
    "Copas",
    "Paus",
    "Espadas"
};

struct TCarta{
    int naipe;
    int valor;
};


struct TJogador{
    std::string nome;
    TListaEstatica<TCarta, 21> mao;
};

bool operator == (TJogador j1, TJogador j2) {
    if ( j1.nome == j2.nome ) {
        return true;
    } else {
        return false;
    }
}

ostream& operator <<(ostream &saida, TJogador &j){
    cout << "Nome: " << j.nome;
    return saida;
}

ostream& operator <<(ostream &saida, TCarta &c){
    cout << "Naipe: " << arr_naipes[c.naipe] << " | Valor: " << c.valor;
    return saida;
}

template<int MAX>
void criar_baralho(TListaEstatica<TCarta, MAX> &baralho) {
    inicializar_lista_estatica(baralho);

    for(int i = 0; i < MAX; i++) {
        TCarta carta;
        carta.naipe = i / 13;
        carta.valor = (i % 13) + 1;
        inserir_fim_lista_estatica(baralho, carta);
    }
}



// template<typename T, typename T2, int MAX>
// void iniciar_jogo(TLista<T> &jogadores, TListaEstatica<T2, MAX> &baralho){
//     TElemento<T> *nav = jogadores.inicio;
//     int quantidade = baralho.quantidade;
//     while ( nav->prox != NULL && nav->prox != jogadores.inicio ) {
//         TCarta carta_distribuicao = baralho.vetor[baralho.quantidade-1].dado;
//         remover_fim_lista_estatica(baralho);
//         inserir_fim_lista_estatica(nav->dado.mao, carta_distribuicao);

//         cout << nav->dado.nome << " recebeu a carta: " << carta_distribuicao << endl;
//         nav = nav->prox;
//     }
//     TCarta carta_distribuicao = baralho.vetor[baralho.quantidade-1].dado;
//     remover_inicio_lista_estatica(baralho);
//     inserir_fim_lista_estatica(nav->dado.mao, carta_distribuicao);
//     cout << nav->dado.nome << " recebeu a carta: " << carta_distribuicao << endl;
// }

template<typename T, typename T2, int MAX>
void iniciar_jogo(TLista<T> &jogadores, TListaEstatica<T2, MAX> &baralho){
    TElemento<T> *nav = jogadores.inicio;
    while ( nav->prox != NULL && baralho.quantidade > 0) {
        TCarta carta_distribuicao = baralho.vetor[baralho.quantidade-1].dado;
        
        remover_fim_lista_estatica(baralho);
        inserir_fim_lista_estatica(nav->dado.mao, carta_distribuicao);

        // cout << nav->dado.nome << " recebeu a carta: " << carta_distribuicao << endl;
        nav = nav->prox;
    }
}



template <typename T>
void habilitarListaEncadeadaCircular(TLista<T> &l){
    TElemento<T> *nav = l.inicio;
    while(nav->prox != NULL){
        nav = nav->prox;
    }
    nav->prox = l.inicio;
}

template <typename T>
void criar_jogadores(TLista<T> &l, int numJogadores) { 

    for ( int n = 0; n < numJogadores; n++ ){
        TJogador jogador;
        jogador.nome = "Jogador " + to_string(n+1);
        inicializar_lista_estatica(jogador.mao);
        inserir_fim_lista(l, jogador);
    }

    habilitarListaEncadeadaCircular(l);
}

void comecarJogo(){
    TLista<TJogador> jogadores;
    jogadores.inicio = NULL;
    int num_jogadores;

    cout << "N° de jogadores: ";
    cin >> num_jogadores;

    criar_jogadores(jogadores, num_jogadores);

    TListaEstatica<TCarta, 52> baralho;
    criar_baralho(baralho);

    embaralhar(baralho);


    iniciar_jogo(jogadores, baralho);
    // distribuirCartas(jogadores, baralho);
    // bool continuarJogando = true;
    // while ( continuarJogando ) {
    //     distribuirCartas(jogadores, baralho);
        
    // }

    cout << jogadores.inicio->dado.nome << ":" << endl;
    imprimir_lista(jogadores.inicio->dado.mao);

    cout << "\n\n";
    cout << jogadores.inicio->prox->dado.nome << ":" << endl;
    imprimir_lista(jogadores.inicio->prox->dado.mao);
    
}