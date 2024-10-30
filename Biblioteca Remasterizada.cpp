#include <iostream>
#include <cstdio>
#include <limits>
#include <cstring>

using namespace std;

struct livros{
    int codigo, paginas, edicao;
    char area[30], titulo[255], editora[255];
    struct emprestimos emp;
};

struct livros livro;

struct empestimos{
    char data_emp[10], data_dev[10], usuario[255];
};

int opc_princ, cod, pos;
char opc;

FILE *arquivo, *arquivoAux;

int main(){
    do {
        cout << "###### Sistema de emprestimos e registros da Biblioteca Santa Cruz######" << endl;
        cout << "1 - Cadastro" << endl;
        cout << "2 - Alteração" << endl;
        cout << "3 - Exclusão" << endl;
        cout << "4 - Empréstimo" << endl;
        cout << "5 - Devolução" << endl;
        cout << "6 - Consulta de livro" << endl;
        cout << "7 - Livros disponívels" << endl;
        cout << "8 - Listagem geral de livros" << endl;
        cout << "9 - Sair" << endl;
        cout << "Digite o número representando a opção desejada: " << endl;
        cin >> opc_princ;
    }
}