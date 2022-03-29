#include <iostream>

// struct TCarta {
//     int naipe;
//     int valor;
// };

// template<typename T>
// struct TElemento {
//     T dado;
//     TElemento* prox;
// };

// //Struct do container
// struct TJogador{
//     std::string nome;
//     TElemento<TJogador>* cartas;
// };

// //Struct da Lista
// template<typename T>
// struct TLista {
//     TElemento<T>* inicio;
// };

// // Quando são varios elementos, e você não tem conhecimento deles é necessário um navegador que vai chegar até o ultimo elemento.
// template <typename T>
// TElemento<T>* encontrarUltimo(TElemento<T>* container){
//     TElemento<T>* nav = container;
//     while ( nav->prox != NULL) {
//         nav = nav->prox;
//     };
//     return nav;
// }

// template<typename T>
// TLista<T>* inicializa_lista_encadeada(T &dado){


//     return l;
// }

struct TJogador{
    std::string nome;
};

struct TElemento{
    TJogador jogador;
    TElemento* prox;
};

struct TLista{
    TElemento* inicio;
};

TLista* inicializa_lista_encadeada(TJogador jogador){
    TElemento* t = new TElemento;
    t->jogador = jogador;
    t->prox = NULL;

    TLista* l = new TLista;
    l->inicio = t;

    return l;
}

TElemento* encontrar_ultimo_elemento(TElemento* container){
    TElemento* nav = container;
    while(nav->prox != NULL){
        nav = nav->prox;
    }
    return nav;
}

void inserir_fim_lista(TLista* &lista, TJogador jogador){
    TElemento* ultimo = encontrar_ultimo_elemento(lista->inicio);

    TElemento* container = new TElemento;
    container->jogador = jogador;
    container->prox = NULL;

    ultimo->prox = container;
}

