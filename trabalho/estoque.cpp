#include "estoque.h"
#include <iostream>
#include <iomanip>

using namespace std;

void Estoque::adicionarProduto(const Produto& produto) {
    produtos.push_back(produto);
}

void Estoque::listarProdutos() const {
    if (produtos.empty()) {
        cout << "Estoque vazio!\n";
        return;
    }

    for (const auto& p : produtos) {
        cout << p << endl;
    }
}

const Produto* Estoque::buscarPorId(int id) const {
    for (const auto& p : produtos) {
        if (p.getId() == id) {
            return &p;
        }
    }
    return nullptr;
}

void Estoque::removerProduto(int id) {
    for (auto it = produtos.begin(); it != produtos.end(); it++) {
        if (it->getId() == id) {
            produtos.erase(it);
            cout << "Produto removido!\n";
            return;
        }
    }
    cout << "Produto não encontrado!\n";
}