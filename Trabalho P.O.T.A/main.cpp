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

    void mostrar() {
        cout << nome << " - preço: R$" << fixed << setprecision(2) << preco <<  " - quantidade no estoque: " << quantidade << endl;
    }
};

class Estoque {
private:
    vector<Produto> produtos;

public:
    void adicionarProduto(Produto p) {
        produtos.push_back(p);
    }

    void listarProdutos() {
        for(auto &p : produtos) {
            p.mostrar();
        }
    }
};

int main() {

    setlocale(LC_ALL, "pt_BR.UTF-8");

    Estoque estoque;

    estoque.adicionarProduto(Produto("Arroz", 25.0, 10));
    estoque.adicionarProduto(Produto("Feijao", 8.5, 20));

    estoque.listarProdutos();
}