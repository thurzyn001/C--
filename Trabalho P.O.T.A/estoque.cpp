#include "estoque.h"
#include <iostream>
#include <iomanip>

using namespace std;

void Estoque::adicionarProduto(const string& nome, float preco, int quantidade,
                               int id, const string& categoria,
                               const string& fornecedor, int validade, int dataEntrada) {

    produtos.emplace_back(nome, preco, quantidade, id, categoria, fornecedor, validade, dataEntrada);

    cout << "Produto adicionado com sucesso!\n";
}

void Estoque::listarProdutos() const {
    if (produtos.empty()) {
        cout << "Estoque vazio!\n";
        return;
    }

    for (const auto& p : produtos) {
        cout << "ID: " << p.getId()
             << " | Nome: " << p.getNome()
             << fixed << setprecision(2) <<" | Preço: " << p.getPreco()
             << " | Quantidade: " << p.getQuantidade()
             << endl;
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