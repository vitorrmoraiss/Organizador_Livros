//Biblioteca que une os dois arquivos .cpp
#include "biblio.h"
#include <clocale>
#include <iostream>


int main(){
    setlocale(LC_ALL, "Portuguese");
    TLivro livr;
    TpilhaLivros livros;
    Tarvore arv;
    string opcao;
    menu(opcao, livros, arv);




    return 0;
}
