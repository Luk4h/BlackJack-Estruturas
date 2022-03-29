#include <iostream>
#include "lista_encadeada.h"

using namespace std;

//Alocação dinâmica em lista.
int main() {
    TJogador j1;
    j1.nome = "Luk4h";

    TJogador j2;
    j2.nome = "Pablo";

    TJogador j3;
    j3.nome = "Fabio";

    TLista* l1 = inicializa_lista_encadeada(j1);

    // cout << l1->inicio->jogador.nome << "\n";


    
    inserir_fim_lista(l1, j2);
    TElemento* ultimo = encontrar_ultimo_elemento(l1->inicio);

    cout << ultimo->jogador.nome << "\n";

    
    inserir_fim_lista(l1, j3);
    TElemento* ultimo2 = encontrar_ultimo_elemento(l1->inicio);

    cout << ultimo2->jogador.nome << "\n";




    return 0;


}