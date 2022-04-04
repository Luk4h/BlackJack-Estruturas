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

    TLista<TJogador> lista;

    inicializa_lista_encadeada(lista, j1);
    inserir_fim_lista(lista, j3);
    inserir_na_posicao(lista, j2, 1);
    imprimir_lista_encadeada(lista);
    
    cout << obter_indice(lista, j3) << endl;

    return 0;


}