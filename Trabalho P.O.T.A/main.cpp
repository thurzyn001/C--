#include <iostream>
#include "estoque.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "pt_BR.UTF-8");

    Estoque estoque;

    
    estoque.adicionarProduto("Arroz", 5.99, 100, 1, "Alimentos", "Fornecedor A", 20251231, 20240101);
    estoque.adicionarProduto("Feijão", 8.50, 200, 2, "Alimentos", "Fornecedor B", 20251231, 20240101);

    estoque.listarProdutos();

    const Produto* p = estoque.buscarPorId(1);

    if (p != nullptr) {
        cout << "\nACHOU: " << *p << endl;
    } else {
        cout << "\nNAO ACHOU\n";
    }

    estoque.removerProduto(2);

    estoque.listarProdutos();

    return 0;
}