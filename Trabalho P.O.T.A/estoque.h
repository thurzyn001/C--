#ifndef ESTOQUE_H
#define ESTOQUE_H

#include <vector>
#include "produto.h"

using namespace std;

class Estoque {
private:
    vector<Produto> produtos;

public:
    void adicionarProduto(const Produto& produto);
    void listarProdutos() const;
    const Produto* buscarPorId(int id) const; 
    void removerProduto(int id);
};

#endif