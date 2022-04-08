// Bibliotecas usadas para o logger.
#include <fstream>
#include <iostream>

void imprimir(std::string texto) {
    std::cout<<texto<<std::endl;
    std::ofstream log;
    log.open("log.txt", std::ios::app);
    std::string str = texto;
    log << str <<"\n";
}

int main() {
    imprimir("Teste");
}