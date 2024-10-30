#include <iostream>
#include <cstdio>
#include <limits>
#include <cstring>

using namespace std;

struct livros{
    int codigo, paginas, edicao;
    char area[30], titulo[255], autores[255], editora[255];
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

        switch (opc_princ){
        case 1:
            cout << "Deseja cadastrar um livro (S ou N)?" << endl;
            cin >> opc;
            while (opc == 'S'){
                cout << "Código do livro: " << endl;
                cin >> livro.codigo;
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                cout << "Área: " << endl;
                cin.get(livro.area, 30);
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                cout << "Título: " << endl;
                cin.get(livro.titulo);
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                cout << "Autor(res): " << endl;
                cin.get(livro.autores);
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                cout << "Editora: " << endl;
                cin.get(livro.editora);
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                cout << "N° de páginas: " << endl;
                cin >> livro.paginas;
                cout << "Edição: " << endl;
                cin >> livro.edicao;

                arquivo = fopen("dados.dat","ab");
                if (arquivo == NULL){
                    arquivo = fopen("dados.dat", "wb");
                }

                if (fwrite($livro, sizeof(struct livros), 1, arquivo) == 1){
                    cout << "Livro registrado com sucesso!" << endl;
                } else {
                    cout << "Erro ao registrar o livro" << endl;
                }
                fclose(arquivo);

                cin.ignore();
                cin.get();

                cout << "Deseja cadastrar um livro (S ou N)?" << endl;
                cin >> opc;
            }
            break;
        case 2:
            arquivo = fopen("dados.dat", "rb+");
            if (arquivo != NULL){

                cout << "Digite o código do livro que deseja alterar: " << endl;
                cin >> cod;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    
                pos = -1;
                while(!feof(arquivo)){
                    fread(&livro, sizeof(struct livros), 1, arquivo);
                    pos++;
                    if (cod == livro.codigo){
                        cout << "Área: " << endl;
                        cin.get(livro.area, 30);
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Título: " << endl;
                        cin.get(livro.titulo, 255);
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Autor(es): " << endl;
                        cin.get(livro.autores, 255);
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Editora: " << endl;
                        cin.get(livro.editora, 50);
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Nº páginas: " << endl;
                        cin >> livro.paginas;
                        cout << "Edição: " << endl;
                        cin >> livro.edicao;

                        fseek(arquivo, sizeof(struct livros) * pos, SEEK_SET);
                        if (fwrite(&livro, sizeof(struct livros), 1, arquivo) == 1){
                            cout << "Livro alterado com sucesso!" << endl;
                        } else {
                            cout << "Erro ao alterar o livro!" << endl;
                        } 
                        cin.ignore();
                        cin.get();
                        break;
                    }
                }
                fclose(arquivo);

            } else {
                cout << "Erro ao abrir o banco de dados!" << endl;
                cin.ignore();
                cin.get();
            }
            break;
        case 3:
            cout << "Digite o código do livro que deseja excluir: " << endl;
            cin >> cod;
            arquivo = fopen("dados.dat", "rb");
            arquivoAux = fopen("dados.aux", "wb");

            fread(&livro, sizeof(struct livros), 1, arquivo);
            while(!feof(arquivo)){
                if (cod != livro.codigo){
                    fwrite(&livro, sizeof(struct livros), 1, arquivoAux);
                }
                fread(&livro, sizeof(struct livros), 1, arquivo);
            }

            fclose(arquivo);
            fclose(arquivoAux);
            remove("dados.dat");
            rename("dados.aux", "dados.dat");
            break;
        case 4:
            arquivo = fopen("dados.dat", "rb+");
            if (arquivo != NULL){
                cout << "Digite o código do livro que deseja emprestar: " << endl;
                cin >> cod;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    
                pos = -1;
                while(!feof(arquivo)){
                    fread(&livro, sizeof(struct livros), 1, arquivo);
                    pos++;
                    if (cod == livro.codigo){
                        fseek(arquivo, sizeof(struct livros) * pos, SEEK_SET);
                        cout << "Data de empréstimo: " << endl;
                        cin.get(livro.emp.dt_emp, 10);
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Data de devolução: " << endl;
                        cin.get(livro.emp.dt_dev, 10);
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Usuário: " << endl;
                        cin.get(livro.emp.usuario, 255);
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        fwrite(&livro, sizeof(struct livros), 1, arquivo);
                        break;
                    }
                }
                fclose(arquivo);

            } else {
                cout << "Erro ao abrir o banco de dados!" << endl;
                cin.ignore();
                cin.get();
            }
            break;
        case 5:
            arquivo = fopen("dados.dat", "rb+");
            if (arquivo != NULL){
                cout << "Digite o código do livro que deseja devolver: " << endl;
                cin >> cod;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    
                pos = -1;
                while(!feof(arquivo)){
                    fread(&livro, sizeof(struct livros), 1, arquivo);
                    pos++;
                    if (cod == livro.codigo){
                        fseek(arquivo, sizeof(struct livros) * pos, SEEK_SET);
                        strcpy(livro.emp.dt_emp, "");
                        strcpy(livro.emp.dt_dev, "");
                        strcpy(livro.emp.usuario, "");
                        fwrite(&livro, sizeof(struct livros), 1, arquivo);
                        break;
                    }
                }
                fclose(arquivo);

            } else {
                cout << "Erro ao abrir o banco de dados!" << endl;
                cin.ignore();
                cin.get();
            }
            break;
        case 6:
            arquivo = fopen("dados.dat", "rb");
            if (arquivo != NULL){
                cout << "Digite o código do livro que deseja pesquisar: " << endl;
                cin >> cod;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    
                while(!feof(arquivo)){
                    fread(&livro, sizeof(struct livros), 1, arquivo);
                    if (cod == livro.codigo){
                        cout << "Código: " << livro.codigo << endl;
                        cout << "Área: " << livro.area << endl;
                        cout << "Título: " << livro.titulo << endl;
                        cout << "Autor(es): " << livro.autores << endl;
                        cout << "Editora: " << livro.editora << endl;
                        cout << "Nº páginas: " << livro.paginas << endl;
                        cin.get();
                        break;
                    }
                }
                fclose(arquivo);

            } else {
                cout << "Erro ao abrir o banco de dados!" << endl;
                cin.ignore();
                cin.get();
            }
            break;
        case 7:
            arquivo = fopen("dados.dat", "rb");
            if (arquivo != NULL){
                fread(&livro, sizeof(struct livros), 1, arquivo);
                while(!feof(arquivo)){
                    if (strcmp(livro.emp.dt_emp, "") == 0){
                        cout << "Código: " << livro.codigo << endl;
                        cout << "Área: " << livro.area << endl;
                        cout << "Título: " << livro.titulo << endl;
                        cout << "Autor(es): " << livro.autores << endl;
                        cout << "Editora: " << livro.editora << endl;
                        cout << "Nº páginas: " << livro.paginas << endl;
                        cout << "---------------------------------------" << endl;
                    }
                    fread(&livro, sizeof(struct livros), 1, arquivo);
                }
                fclose(arquivo);
                cin.ignore();
                cin.get();
            } else {
                cout << "Erro ao abrir o banco de dados!" << endl;
                cin.ignore();
                cin.get();
            }
            break;
        case 8:
            arquivo = fopen("dados.dat", "rb");
            if (arquivo != NULL){
                fread(&livro, sizeof(struct livros), 1, arquivo);
                while(!feof(arquivo)){
                    cout << "Código: " << livro.codigo << endl;
                    cout << "Área: " << livro.area << endl;
                    cout << "Título: " << livro.titulo << endl;
                    cout << "Autor(es): " << livro.autores << endl;
                    cout << "Editora: " << livro.editora << endl;
                    cout << "Nº páginas: " << livro.paginas << endl;
                    cout << "---------------------------------------" << endl;
                    fread(&livro, sizeof(struct livros), 1, arquivo);
                }
                fclose(arquivo);
                cin.ignore();
                cin.get();
            } else {
                cout << "Erro ao abrir o banco de dados!" << endl;
                cin.ignore();
                cin.get();
            }
            break;
        case 9:
            cout << "Obrigado por usar nosso sistema!" << endl;
            break;
        default:
         cout << "Informe uma opção válida!" << endl;
            break;
        }
        System("cls");
    } while (opc_princ != 9);
    
}