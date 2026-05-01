#include <iostream>
#include <vector>
#include <iomanip>
#include <locale>
using namespace std;

class Produto {
private:
    string nome;
    float preco;
    int quantidade;

public:
    Produto(string n, float p, int q) {
        nome = n;
        preco = p;
        quantidade = q;
    }

    string getNome() {
        return nome;
    }

    void mostrar() {
        cout << nome 
             << " - preço: R$" 
             << fixed << setprecision(2) << preco 
             << " - quantidade: " 
             << quantidade << endl;
    }

    void adicionar(int q) {
        quantidade += q;
    }

    bool remover(int q) {
        if(q <= quantidade) {
            quantidade -= q;
            return true;
        }
        return false;
    }
};

class Estoque {
private:
    vector<Produto> produtos;

public:
    void adicionarProduto(const Produto& p) {
        produtos.push_back(p);
    }

    void listarProdutos() {
        if(produtos.empty()) {
            cout << "Estoque vazio!\n";
            return;
        }

        for(auto &p : produtos) {
            p.mostrar();
        }
    }

    Produto* buscarProduto(string nome) {
        for(auto &p : produtos) {
            if(p.getNome() == nome) {
                return &p;
            }
        }
        return nullptr;
    }
};

int main() {
    setlocale(LC_ALL, "pt_BR.UTF-8");

    Estoque estoque;
    int opcao;

    do {
        cout << "\n=== SISTEMA DE ESTOQUE ===\n";
        cout << "1 - Adicionar produto\n";
        cout << "2 - Listar produtos\n";
        cout << "3 - Vender produto\n";
        cout << "0 - Sair\n";
        cout << "Escolha: ";
        cin >> opcao;

        if(opcao == 1) {
            string nome;
            float preco;
            int qtd;

            cout << "Nome: ";
            cin >> nome;

            cout << "Preço: ";
            cin >> preco;

            cout << "Quantidade: ";
            cin >> qtd;

            estoque.adicionarProduto(Produto(nome, preco, qtd));
        }

        else if(opcao == 2) {
            estoque.listarProdutos();
        }

        else if(opcao == 3) {
            string nome;
            int qtd;

            cout << "Nome do produto: ";
            cin >> nome;

            Produto* p = estoque.buscarProduto(nome);

            if(p != nullptr) {
                cout << "Quantidade a vender: ";
                cin >> qtd;

                if(p->remover(qtd)) {
                    cout << "Venda realizada!\n";
                } else {
                    cout << "Estoque insuficiente!\n";
                }
            } else {
                cout << "Produto não encontrado!\n";
            }
        }

    } while(opcao != 0);

    return 0;
}