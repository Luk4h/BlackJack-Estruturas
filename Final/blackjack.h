#include <iostream>
#include <string>
#include <time.h>
#include "lista-encadeada-dupla.h"
#include "lista-encadeada-simples.h"
#include "lista-estatica.h"

using namespace std;
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

    return saida;
}

ostream& operator <<(ostream &saida, TCarta &c){
    cout << "Naipe: " << arr_naipes[c.naipe] << " | Valor: " << c.valor;
    return saida;
}

// Inicialização do baralho como uma lista estatica.
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

// Embaralha trocando a posição das cartas do baralho 5*baralho.quantidade vezes.
template <typename T, int MAX>
void embaralhar(TListaEstatica<T,MAX> &baralho) {
    srand(time(NULL));

    for(int i = 0; i < baralho.quantidade*5; i++) {
        int posicao1 = rand() % MAX;
        int posicao2 = rand() % MAX;

        trocar_posicoes_lista_estatica(baralho,posicao1,posicao2);
    }
}

// Inicialização do baralho e embaralhamento dele ao mesmo tempo.
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

// Ccontagem de jogadores com o J.jogando como true dentro da lista do parametro.
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
        return quantidade;
    }
    
    return 0;
}

// Contagem de jogadores na lista.
int get_qtde_jogadores(TLista<TJogador> &jogadores){
    TElemento<TJogador> *nav = jogadores.inicio;
    if(nav != NULL){
        int quantidade = 1;
        while(nav->prox != NULL && nav->prox != jogadores.inicio){
            quantidade++;
            nav = nav->prox;
        }

        return quantidade;
    }
    return 0;
}

// Descobrir qual jogador possui a maior soma abaixo de 21 na mão.
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

    return maior_valor;
}

// Cria uma segunda lista encadeada simples circular e adiciona os jogadores vencedores a ela.
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

// Verificação de qual jogador na lista é o vencedor/res.
template <int MAX>
void verifica_vencedor(TLista<TJogador> &jogadores, TListaEstatica<TCarta, MAX> &baralho, int partida){
    TLista<TJogador> jogadores_vencedores;
    jogadores_vencedores.inicio = NULL;

    int maior_soma = get_maior_soma_jogadores(jogadores);
    preenche_jogadores_vencedores(jogadores_vencedores, jogadores, maior_soma);
    system("cls");

    cout << "\n\n====================\n-----VENCEDORES-----\n====================\n";

    int quantidade_vencedores = get_qtde_jogadores(jogadores_vencedores);
    if(quantidade_vencedores > 1){
        system("cls");
        imprimir_lista_encadeada(jogadores_vencedores);
        criar_baralho_embaralhado(baralho);
        iniciar_jogov2(jogadores_vencedores, baralho, partida + 1);
    }
    else if (quantidade_vencedores == 0){
        cout << "NAO HOUVERAM VENCEDORES";
        cout << "\n====================\n\n";
    }
    else{
        imprimir_lista_encadeada(jogadores_vencedores);
    }
}

// Execução principal do jogo.
template<int MAX>
void iniciar_jogo(TLista<TJogador> &jogadores, TListaEstatica<TCarta, MAX> &baralho, int partida){
    habilitar_lista_encadeada_circular(jogadores);
    TElemento<TJogador> *nav = jogadores.inicio;

    int quantidade_jogadores = get_qtde_jogadores(jogadores);
    
    int rodada = 0;
    int rCounter = 1;
    system("cls");
    cout << "\n\n==============\nRodada: " << rCounter << "\n==============\n\n";
    rCounter++;
    while ( nav->prox != NULL && baralho.quantidade > 0) {

        if(get_qtde_jogadores_ativos(jogadores) == 0)
            break;

        if( rodada != 0 && rodada % quantidade_jogadores == 0){
            system("pause");
            system("cls");
            cout << "\n==============\n" <<
                    "Rodada: " << rCounter <<
                    "\n==============\n";
            rCounter++;
        }

        processar_rodada(nav->dado, baralho);

        if(nav->dado.jogando)
            jogador_pensando(nav->dado);
        nav = nav->prox;
        rodada++;
        
    }
    system("pause");
    system("cls");
    imprimir_lista_encadeada(jogadores);
    system("pause");
    verifica_vencedor(jogadores, baralho, partida);
}

// Aleatoriedade no mecanismos de HIT e STOP automatizados.
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

// Adiciona ao jogador uma carta do baralho, removendo-a do baralho.
template <int MAX>
void processar_rodada(TJogador &j, TListaEstatica<TCarta, MAX> &baralho){
    if(j.jogando){
        TCarta carta_distribuicao = baralho.vetor[baralho.quantidade-1].dado;
        remover_fim_lista_estatica(baralho);
        j.soma_cartas += carta_distribuicao.valor;
        inserir_fim_lista_estatica(j.mao, carta_distribuicao);
        cout << "O " << j.nome << " recebeu a carta: " << carta_distribuicao.valor << endl << endl;
    }
}

// Habilita-se a circularidade da lista definindo o ponteiro do atributo prox do ultimo elemento como o inicio da lista.
template <typename T>
void habilitar_lista_encadeada_circular(TLista<T> &l){
    TElemento<T> *nav = l.inicio;
    while(nav->prox != NULL){
        nav = nav->prox;
    }
    nav->prox = l.inicio;
}

// Criação e nomeação dos jogadores, criando uma lista estatica chamada mão que vai armezar as cartas do jogador.
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