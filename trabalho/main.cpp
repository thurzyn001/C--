#include <iostream>
#include "estoque.h"
#include <locale>
#include <limits>
#include <cstdlib>

using namespace std;

bool lerOpcao(int &opcao) {
    cout << "Opcao: ";

    if (!(cin >> opcao)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return true;
}

int main() {
    setlocale(LC_ALL, "pt_BR.UTF-8");
    system("chcp 65001 > nul");

    Estoque estoque;
    int opcao;

    do {
        cout << "\n=====================================\n";
        cout << "        SISTEMA DE ESTOQUE          \n";
        cout << "=====================================\n";
        cout << "[1] Adicionar produto\n";
        cout << "[2] Listar produtos\n";
        cout << "[3] Buscar produto\n";
        cout << "[4] Remover produto\n";
        cout << "[0] Sair\n";
        cout << "=====================================\n";

        if (!lerOpcao(opcao)) {
            cout << "Entrada invalida!\n";
            continue;
        }

        switch (opcao) {
                case 1: {
                string nome, categoria, fornecedor;
                float preco;
                int quantidade, id, validade, dataEntrada;

                cout << "Nome: ";
                getline(cin >> ws, nome);

                cout << "Preço: ";
                cin >> preco;

                cout << "Quantidade: ";
                cin >> quantidade;

                cout << "ID: ";
                cin >> id;

                if (estoque.buscarPorId(id) != nullptr) {
                    cout << "Erro: já existe produto com esse ID!\n";
                    break;
                }

                cout << "Categoria: ";
                getline(cin >> ws, categoria);

                cout << "Fornecedor: ";
                getline(cin >> ws, fornecedor);

                cout << "Validade (YYYYMMDD): ";
                cin >> validade;

                cout << "Data de entrada (YYYYMMDD): ";
                cin >> dataEntrada;

                cout << "\n>>> Adicionando produto...\n";

                Produto p(nome, preco, quantidade, id, categoria, fornecedor, validade, dataEntrada);
                estoque.adicionarProduto(p);

                cout << "\nProduto adicionado com sucesso!\n";

                break;
            }

            case 2:
                estoque.listarProdutos();
                break;

            case 3: {
                int id;
                cout << "Digite o ID: ";
                cin >> id;

                const Produto* p = estoque.buscarPorId(id);

                if (p != nullptr) {
                    cout << "Produto encontrado:\n" << *p << endl;
                } else {
                    cout << "Produto não encontrado!\n";
                }
                break;
            }

            case 4: {
                int id;
                cout << "Digite o ID para remover: ";
                cin >> id;
                estoque.removerProduto(id);
                break;
            }

            case 0:
                cout << "Saindo...\n";
                break;

            default:
                cout << "Opção inválida!\n";
        }

    } while (opcao != 0);

    return 0;
}