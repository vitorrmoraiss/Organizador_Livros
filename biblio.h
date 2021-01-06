#ifndef BIBLIO_H_INCLUDED
#define BIBLIO_H_INCLUDED
#include <iostream>
using namespace std;

//Biblioteca .h com a entrada das fun��es

//Cria campos de cada livro
struct TLivro{
    string nome;
    string autor;
    int ano;
    int avaliacao;
};

//Struct para indicar pr�xima c�lula de dados na pilha
struct Tcelula{
   TLivro item;
   Tcelula *proximo;
};

//Declarando ponteiros que ser�o os extremos da pilha
struct TpilhaLivros{
   Tcelula *fundo;
   Tcelula *topo;
   int contador;
};

//Criando n� e filhos
struct Tnoh{
   TLivro nitem;
   Tnoh *esq, *dir;
};

//Declarando a raiz da �rvore
struct Tarvore{
   Tnoh *raiz;
};

//Declarando as Fun��es
void criarPilhaVazia(TpilhaLivros &p);
bool eVazia(TpilhaLivros &p);
void inserirLivros(TLivro l, TpilhaLivros &p);
void cadastrarLivros(TpilhaLivros &p);
void mostrarPilha(TpilhaLivros &p);
TLivro desempilha(TpilhaLivros &p);
void inicializarArvore(Tarvore &arv);
bool estaVazia(Tarvore arv);
void inserirArvore(TLivro l, Tnoh *&noh, Tarvore &arv);
void percorrerInOrdem(Tnoh *&n);
void cadastrarArvore(TpilhaLivros p, Tarvore &a);
void menu(string op, TpilhaLivros &p, Tarvore &a);
int lendoArq(string nomeArq, int quantTokens);
int escrevendoArq(string nomeArq, string vetDados, int quantTokens);



#endif // BIBLIO_H_INCLUDED
