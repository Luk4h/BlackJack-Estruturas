#include <iostream>
#include "lista.h"
#include "carta.h"
using namespace std;

struct TJogador {
    std::string nome;
//      TListaEstaticaCartas mao;
    float carteira;
};


ostream& operator <<(ostream &os, TJogador c) {
    os << "Jogador{ nome: " << c.nome << " carteira: " << c.carteira << "}";
    return os;
}

int main() {
    // TListaEstatica<TCarta,52> baralho_mesa;
    // baralho_mesa = criar_baralho();
    // embaralhar(baralho_mesa);

    // imprimir_lista(baralho_mesa);
    // return 0;

    TListaEstatica<TCarta, 52> baralho = criar_baralho();
    TCarta carta_nova;
    carta_nova.naipe = 2;
    carta_nova.valor = 12 ;

    embaralhar(baralho);

    imprimir_baralho(baralho);
    int indice = obter_o_indice(baralho, carta_nova);

    if(indice != -1)
        cout << "Index is: " << indice << "\n";
    imprimir_carta(baralho.vetor[indice].dado);
    return 0; 
}
