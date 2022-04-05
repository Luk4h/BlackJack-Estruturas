/// Jogo de Blackjack utilizando as estruturas de dados:
/// listas estaticas, listas encadeadas simples e duplas.

#include <iostream>
#include "blackjack.h"

using namespace std;


int main(){

   TLista<TJogador> jogadores;
    jogadores.inicio = NULL;
    int num_jogadores;

    cout << "Numero de jogadores: ";
    cin >> num_jogadores;

    criar_jogadores(jogadores, num_jogadores);

    TListaEstatica<TCarta, 416> baralho;
    criar_baralho_embaralhado(baralho);

    int partida = 1;
    iniciar_jogo(jogadores, baralho, partida);

}

/// Trabalho de Estruturas de dados.
/// Ciêcias da Computação 2022 UNIVALI
/// Por Fabio Renato dos Santos Neto, Júlia Cansian Rocha, Luiz Gustavo de Vergennes Marcondes.