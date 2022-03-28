#include <iostream>



    //Struct do container
    struct TElemento {
        int dado;
        TElemento* prox;
    };

    //Struct da Lista
    struct TLista {
        TElemento* inicio;
    };

// Quando são varios elementos, e você não tem conhecimento deles é necessário um navegador que vai chegar até o ultimo elemento.
TElemento* encontrarUltimo(TElemento* container){
    TElemento* nav = container;
    while ( nav->prox != NULL) {
        nav = nav->prox;
    };
    return nav;
}


//Alocação dinâmica em lista.
int main() {

    // 1 - Inicializa-se o TElemento.
    TElemento* T1 = new TElemento;

    // 2 - Adiciona-se o dado.
    T1->dado = 10;

    // 3 - Cria o indicador do proxímo elemento.
    T1->prox = NULL;

    // 4 - Inicializa-se o proxímo elemento.
    TElemento* T2 = new TElemento;    

    // 5 - Adiciona o valor do dado do proxímo elemento.
    T2 -> dado = 20;

    // 6 - Inicializa o apontador para o proxímo.
    T2 -> prox = NULL;

    // 7 - Define que o Elemento anterior aponta para o proxímo e mais recente elemento.
    T1 -> prox = T2;

    // Função para encontrar o ultimo Elemento da lista.
    TElemento* ultimoContainer = encontrarUltimo(T1);
    
    std::cout<<ultimoContainer->dado<<std::endl;

    return 0;


}