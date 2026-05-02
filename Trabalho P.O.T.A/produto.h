#ifndef PRODUTO_H
#define PRODUTO_H

#include <iostream>
#include <string>

using namespace std;

class Produto {
private:
    string nome;
    float preco;
    int quantidade;
    int id;
    string categoria;
    string fornecedor;
    int validade;
    int dataEntrada;

public:
    Produto(const string& nomw, float prec, int quan, int id,
            const string& cate, const string& forn, int vali, int data);

    const string& getNome() const noexcept;
    float getPreco() const noexcept;
    int getQuantidade() const noexcept;
    int getId() const noexcept;
    const string& getCategoria() const noexcept;
    const string& getFornecedor() const noexcept;
    int getValidade() const noexcept;
    int getDataEntrada() const noexcept;

    void setNome(const string& nomw);
    void setPreco(float prec);
    void setQuantidade(int quan);
    void setId(int id);
    void setCategoria(const string& cate);
    void setFornecedor(const string& forn);
    void setValidade(int vali);
    void setDataEntrada(int data);

    friend ostream& operator<<(ostream& os, const Produto& p);
};

#endif