#ifndef ESTOQUE_H
#define ESTOQUE_H

#include <vector>
#include "produto.h"

using namespace std;

class Estoque {
private:
    vector<Produto> produtos;

public:
    void adicionarProduto(const string& nome, float preco, int quantidade,
                               int id, const string& categoria,
                               const string& fornecedor, int validade, int dataEntrada);
    void listarProdutos() const;
    const Produto* buscarPorId(int id) const; 
    void removerProduto(int id);
};

#endif