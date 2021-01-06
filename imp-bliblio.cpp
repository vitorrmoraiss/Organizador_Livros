#include "biblio.h"
#include <fstream>

int lendoArq(string nomeArq, int quantTokens){

    fstream arq(nomeArq);// instanciando e abrindo o arquivo

    if (arq.is_open()){
        string registro, token;
        string valores[quantTokens];
        int i, j, contToken, contRegistro;

        contRegistro = 1;
        while (arq.good()){
            getline(arq,registro);
            if (registro.length() > 0){ //ignora linhas em branco
                cout << "Registro " << contRegistro << " completo: " << string(registro) << endl;
                token = ""; // LIMPA INICIAL

                for (j=0; j < quantTokens;j++){ // LIMPA TODAS AS POSIÇÕES DO VETOR
                    valores[j] = token;
                }

                i=0;
                contToken=0;
                while (i <= int(registro.length())){  // PERCORRENDO O VETOR DE CHAR (REGISTRO)
                   if (registro[i] != ';') {
                        token = token + registro[i]; //  PREENCHE A VARIÁVEL TOKEN
                    }
                    else{
                       valores[contToken] = token;  // PREENCHE E ARMAZENA NA POSIÇÃO CERTA
                                                    // para as 2 primeiras palavras
                       contToken++;     // INCREMENTA O CONTTOKEN
                       token = "";   // LIMPA

                    }
                    i++;
                }
                valores[contToken] = token; // para a última palavra/TOKEN, que não tem ; no final
                for (j=0; j<quantTokens;j++){
                    cout << "     Token " << j << ": " << valores[j] << endl;
                }
                contRegistro++;
            }
        }
    }
    else{
        cout << "Problemas com a abertura do arquivo!" << endl;
	return -1;
    }
    arq.close();
    return 0;
}

int escrevendoArq(string nomeArq, TpilhaLivros &p, int quantTokens){

    int i;
    string registro = "";
    fstream arquivo(nomeArq,ios::ate|ios::in|ios::out);

    if (arquivo.is_open()){
        for (i=0; i<quantTokens;i++){   // MONTANDO NOSSO REGISTRO!
            if (i < quantTokens-1){
                registro = registro + vetDados[i] + ";";
            }
            else{
                registro = registro + vetDados[i] + "\n";
            }
        }
        arquivo << registro; // ESCREVE O REGISTRO NO ARQUIVO!
        arquivo.close();
        cout << "Dados inseridos com sucesso!" << endl;
        return 0;
    }
    else{
        cout << "Problemas com o arquivo!" << endl;
        return -1;
    }
}
//Esse procedimento cria a pilha vazia
void criarPilhaVazia(TpilhaLivros &p){
   p.topo = new Tcelula;
   p.fundo = p.topo;
   p.topo->proximo = NULL;
   p.contador = 0;
   cout<< "\nLista inicializada com sucesso" << endl;
}

//Retorna se a Pilha estiver vazia
bool eVazia(TpilhaLivros &p){
   return (p.topo == p.fundo);
}
//Insere novos itens na pilha
void inserirLivros(TLivro l, TpilhaLivros &p){
   Tcelula *celAux = new Tcelula;
   p.topo->item = l;
   celAux->proximo = p.topo;
   p.topo = celAux;
   p.contador++;
}

//Utilizado para cadastrar novos livros
void cadastrarLivros(TpilhaLivros &p){
   TLivro liv;
   string resposta="s";

   cout << "\nCadastrando seus livros" << endl;
   while((resposta != "n") && (resposta != "N")){
       cout << "Nome do Livro: ";
       cin >> liv.nome;
       cout << "Nome do Autor(a): ";
       cin >> liv.autor;
       cout << "Ano de Lançamento: ";
       cin >> liv.ano;
       cout << "Avaliação - 0 a 5: ";
       cin >> liv.avaliacao;

       inserirLivros(liv,p);
       cout << "\nDeseja adicionar outro livro? (S/N) ";
       cin >> resposta;
   }
}

//Mostra itens da pilha
void mostrarPilha(TpilhaLivros &p){
   Tcelula *pcelaux;
   pcelaux = p.topo->proximo;

   cout << "\n=====================================================" << endl;
   cout << "Livros anexados à pilha atual: " << endl;
   while(pcelaux != NULL){
    cout << "Livro: " << pcelaux->item.nome << endl;
    cout << "Autor(a): " << pcelaux->item.autor << endl;
    cout << "Ano: " << pcelaux->item.ano << endl;
    cout << "Avaliação: " << pcelaux->item.avaliacao << endl;
    cout << "======================================================" << endl;

    pcelaux = pcelaux->proximo;
   }
}

//Retiramos o topo da pilha e passamos como retorno
TLivro desempilha(TpilhaLivros &p){
   Tcelula *celAux;
   TLivro livrAux;

   if( eVazia(p)){
       cout << " ERRO! Não há livros para retirar da pilha!" << endl;
   }else{
       celAux = p.topo;
       livrAux = celAux->proximo->item;
       p.topo = celAux->proximo;
       p.contador--;
       delete celAux;
   }
   return livrAux;
   }

//Declara a árvore igual a NULL
void inicializarArvore(Tarvore &arv){
   arv.raiz = NULL;
   cout << "\nProntos para organizar" << endl;
}

//Confere se a árvore está vazia
bool estaVazia(Tarvore arv){
   return (arv.raiz == NULL);
}

//Insere itens na árvore
void inserirArvore(TLivro l, Tnoh *&noh, Tarvore &arv){
   if( noh == NULL){
    noh = new Tnoh;
    noh->nitem = l;
    noh->esq = NULL;
    noh->dir = NULL;

    if(arv.raiz == NULL){
        arv.raiz = noh;
    }else{
       if(l.nome < noh->nitem.nome){
        inserirArvore(l, noh->esq, arv);
       }else{
          if(l.nome > noh->nitem.nome){
            inserirArvore(l,noh->dir, arv);
          }else{
             cout << "Livro já cadastrado!" << endl;
          }
        }
      }
    }
}

//Esse procedimento percorre a árvore na seguência IN ORDEM
void percorrerInOrdem(Tnoh *&n){
   if(n != NULL){
    cout << "\n-------------------------------------------" << endl;
    cout << "Livros anexados ao seu arquivo: " <<endl;
    percorrerInOrdem(n->esq);
    cout << "Livro: " << n->nitem.nome << endl;
    cout << "Autor(a): " << n->nitem.autor << endl;
    cout << "Ano: " << n->nitem.ano << endl;
    cout << "Avaliação: " << n->nitem.avaliacao << endl;
    cout << "---------------------------------------------" << endl;
    percorrerInOrdem(n->dir);
   }
}

//Esse procedimento transfere da pilha para a árvore
void cadastrarArvore(TpilhaLivros p, Tarvore &a){
   TLivro livr;
   Tcelula *aux;

   aux = p.topo->proximo;
   if(eVazia(p)){
    cout << "Não há livros para desempilhar!" << endl;
   }else{
       while(aux != NULL){
        livr=desempilha(p);
        inserirArvore(livr, a.raiz, a);
        aux = aux->proximo;
       }
   }
}

//Menu do código
void menu(string operacao, TpilhaLivros &p, Tarvore &a){
    int op;

    while (op != 7){


    cout << "\n*********************************************************" <<endl;
    cout << "       BEM VINDO AO ORGANIZADOR DE LIVROS IFTEC!" << endl;
    cout << "*********************************************************\n" <<endl;

    cout<< "MENU DE OPERAÇÕES:" << endl;
    cout << "=========================================================" <<endl;
    cout << "    1- Criar arquivo de livros." << endl;
    cout << "    2- Conferir se há livros cadastrados no seu arquivo." << endl;
    cout << "    3- Acrescentar livros em seu arquivo." << endl;
    cout << "    4- Mostrar lista de livros parcialmente." << endl;
    cout << "    5- Inicializar organizador de livros." << endl;
    cout << "    6- Mostrar lista de livros organizada e avaliada!" << endl;
    cout << "    7- Encerrar o programa." << endl;
    cout << "=========================================================\n" <<endl;


    cout << "\n Escolha uma Opção: ";
    cin >> op;

    switch(op){
      case 1:
          criarPilhaVazia(p);
          break;
      case 2:
          if(eVazia(p)){
            cout << "\nSem livros em seu arquivo!" <<endl;
          }else{
             cout << "\nHá livros em seu arquivo! Escolha a opção 4 para visualizar!" <<endl;
          }
          break;
      case 3:
          cadastrarLivros(p);

          break;
      case 4:
          mostrarPilha(p);
          break;
      case 5:
          inicializarArvore(a);
          break;
      case 6:
          cadastrarArvore(p, a);
          percorrerInOrdem(a.raiz);
        break;
      case 7:
         cout << "\nPrograma encerrado! Volte Sempre!" <<endl;
          break;
      default:
          cout << "\nOpção inválida!" << endl;
    }
  }
}
