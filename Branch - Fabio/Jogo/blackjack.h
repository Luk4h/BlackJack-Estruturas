#include <iostream>
#include <string>
#include <time.h>
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
    bool jogando;
    int soma_cartas;
    int soma_cartas_history;
};

bool operator == (TJogador j1, TJogador j2) {
    if ( j1.nome == j2.nome ) {
        return true;
    } else {
        return false;
    }
}

ostream& operator <<(ostream &saida, TJogador &j){
    cout << "==================\n"
         << "Nome: " << j.nome
         << "\n==================\n";
    cout << "Soma: " << (j.soma_cartas == 0 || j.soma_cartas == NULL ? j.soma_cartas_history : j.soma_cartas)
         << "\n==================\n";
    // cout << "Cartas na mao: " << endl;
    // imprimir_lista(j.mao);
    // cout << "==================\n\n";

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

template<int MAX>
void criar_baralho_embaralhado(TListaEstatica<TCarta, MAX> &baralho) {
    inicializar_lista_estatica(baralho);

    for(int i = 0; i < MAX; i++) {
        TCarta carta;
        carta.naipe = i / 13;
        carta.valor = (i % 13) + 1;
        inserir_fim_lista_estatica(baralho, carta);
    }

    embaralhar(baralho);
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

int get_qtde_jogadores_ativos(TLista<TJogador> &jogadores){
    TElemento<TJogador> *nav = jogadores.inicio;
    if(nav != NULL){
        int quantidade = 0;
        while(nav->prox != NULL && nav->prox != jogadores.inicio){
            if(nav->dado.jogando){
                quantidade++;
            }
            nav = nav->prox;
        }
        if ( nav->dado.jogando ) 
            quantidade++;
        // JOGANDO QUANTIDADE + 1 PORQUE ELE NÃO CONTA O ULTIMO JOGADOR
        return quantidade;
    }
    
    return 0;
}

bool verifica_jogadores_ativos(TLista<TJogador> &jogadores){
    int quantidade_jogando = get_qtde_jogadores_ativos(jogadores);
    if(quantidade_jogando == 0){
        return false;
    }        

    return true;
}

int get_qtde_jogadores(TLista<TJogador> &jogadores){
    TElemento<TJogador> *nav = jogadores.inicio;
    if(nav != NULL){
        int quantidade = 1;
        while(nav->prox != NULL && nav->prox != jogadores.inicio){
            quantidade++;
            nav = nav->prox;
        }

        // JOGANDO QUANTIDADE + 1 PORQUE ELE NÃO CONTA O ULTIMO JOGADOR
        return quantidade;
    }
    return 0;
}

int get_maior_soma_jogadores(TLista<TJogador> &jogadores){
    TElemento<TJogador> *nav = jogadores.inicio;
    int maior_valor = 0;
    while(nav->prox != NULL && nav->prox != jogadores.inicio){
        if(nav->dado.soma_cartas > maior_valor && nav->dado.soma_cartas <= 21){
            maior_valor = nav->dado.soma_cartas;
        }
        nav = nav->prox;
    }
    if(nav->dado.soma_cartas > maior_valor && nav->dado.soma_cartas <= 21){
        maior_valor = nav->dado.soma_cartas;
    }

    // JOGANDO QUANTIDADE + 1 PORQUE ELE NÃO CONTA O ULTIMO JOGADOR
    return maior_valor;
}

void preenche_jogadores_vencedores(TLista<TJogador> &jogadores_vencedores, TLista<TJogador> &jogadores, int maior_soma){
    TElemento<TJogador> *nav = jogadores.inicio;

    if(nav->dado.soma_cartas == maior_soma){
        TJogador jogador;
        jogador.jogando = true;
        jogador.nome = nav->dado.nome;
        jogador.soma_cartas = 0;
        jogador.soma_cartas_history = nav->dado.soma_cartas;
        inicializar_lista_estatica(jogador.mao);    
        inserir_fim_lista(jogadores_vencedores, jogador);
    }
    while(nav->prox != NULL && nav->prox != jogadores.inicio){
        nav = nav->prox;
        if(nav->dado.soma_cartas == maior_soma){
            TJogador jogador;
            jogador.jogando = true;
            jogador.nome = nav->dado.nome;
            jogador.soma_cartas = 0;
            jogador.soma_cartas_history = nav->dado.soma_cartas;
            inicializar_lista_estatica(jogador.mao);    
            inserir_fim_lista(jogadores_vencedores, jogador);
        }
    }
}

void reseta_jogadores(TLista<TJogador> &jogadores){
    TElemento<TJogador> *nav = jogadores.inicio;
    nav->dado.soma_cartas = 0;
    nav->dado.jogando = true;
    inicializar_lista_estatica(nav->dado.mao);

    while(nav->prox != NULL){
        nav = nav->prox;
        TElemento<TJogador> *nav = jogadores.inicio;
        nav->dado.soma_cartas = 0;
        nav->dado.jogando = true;
        inicializar_lista_estatica(nav->dado.mao);
    }

}

template <int MAX>
void verifica_vencedor(TLista<TJogador> &jogadores, TListaEstatica<TCarta, MAX> &baralho, int partida){
    TLista<TJogador> jogadores_vencedores;
    jogadores_vencedores.inicio = NULL;

    int maior_soma = get_maior_soma_jogadores(jogadores);
    preenche_jogadores_vencedores(jogadores_vencedores, jogadores, maior_soma);

    cout << "\n\n====================\n";
    cout << "-----VENCEDORES-----";
    cout << "\n====================\n";

    

    int quantidade_vencedores = get_qtde_jogadores(jogadores_vencedores);
    // cout << "\n\nQUANTIDADE DE VENCEDORES: " << quantidade_vencedores << "\n\n";
    if(quantidade_vencedores > 1){
        imprimir_lista_encadeada(jogadores_vencedores);
        criar_baralho_embaralhado(baralho);
        iniciar_jogo(jogadores_vencedores, baralho, partida + 1);
    }
    else if (quantidade_vencedores == 0){
        cout << "NAO HOUVERAM VENCEDORES";
        cout << "\n====================\n\n";
    }
    else{
        imprimir_lista_encadeada(jogadores_vencedores);
    }
}

template<int MAX>
void iniciar_jogo(TLista<TJogador> &jogadores, TListaEstatica<TCarta, MAX> &baralho, int partida){
    habilitar_lista_encadeada_circular(jogadores);
    TElemento<TJogador> *nav = jogadores.inicio;

    cout << "\n\n==============\nPARTIDA " << partida << "\n==============\n\n";

    int rodada = 1;
    while ( nav->prox != NULL && baralho.quantidade > 0) {
        if(!verifica_jogadores_ativos(jogadores)){
            break;
        }

        processar_rodada(nav->dado, baralho);

        if(nav->dado.jogando)
            jogador_pensando(nav->dado);
        // remover_fim_lista_estatica(baralho);
        // inserir_fim_lista_jogadores(nav->dado, carta_distribuicao);
        // cout << nav->dado.nome << " recebeu a carta: " << carta_distribuicao << endl;
        nav = nav->prox;
        rodada++;
    }
    // if(nav->dado.jogando)
    //     jogador_pensando(nav->dado);
    // processar_rodada(nav->dado, baralho);
    imprimir_lista_encadeada(jogadores);
    system("pause");
    verifica_vencedor(jogadores, baralho, partida);
}

void jogador_pensando(TJogador &j){
    if(j.soma_cartas > 21){
        j.jogando = false;
        cout << "O " << j.nome << " passou de 21." << endl << endl;
    }
    else if(j.soma_cartas == 21){
        j.jogando = false;
        cout << "O " << j.nome << " atingiu 21." << endl << endl;
    }
    else{
        srand(time(NULL));
        int chance_de_parar = rand() % 10 + 1;
        if(j.soma_cartas > 18 && chance_de_parar > 3){
            j.jogando = false;
            cout << "O " << j.nome << " deu stop." << endl << endl;
        }
        else if(j.soma_cartas > 15 && chance_de_parar > 5){
            j.jogando = false;
            cout << "O " << j.nome << " deu stop." << endl << endl;
        }
        else if(j.soma_cartas > 12 && chance_de_parar > 8){
            j.jogando = false;
            cout << "O " << j.nome << " deu stop." << endl << endl;
        }
    }
}

template <int MAX>
void processar_rodada(TJogador &j, TListaEstatica<TCarta, MAX> &baralho){
    if(j.jogando){
        TCarta carta_distribuicao = baralho.vetor[baralho.quantidade-1].dado;
        remover_fim_lista_estatica(baralho);
        j.soma_cartas += carta_distribuicao.valor;
        inserir_fim_lista_estatica(j.mao, carta_distribuicao);
        //TODO: COUT JOGADOR X RECEBEU CARTA Y.
        cout << "O " << j.nome << " recebeu a carta: " << carta_distribuicao.valor << endl;
        system("pause");
    }
}


template <typename T>
void habilitar_lista_encadeada_circular(TLista<T> &l){
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
        jogador.soma_cartas = 0;
        jogador.jogando = true;

        inicializar_lista_estatica(jogador.mao);
        inserir_fim_lista(l, jogador);
    }
}

void comecar_jogo(){
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