#include "produto.h"
#include <string>
#include <iomanip>  

using namespace std;

//Construtor:
Produto::Produto(const string& nomw, float prec, int quan, int id,
                 const string& cate, const string& forn, int vali, int data) :
    nome(nomw), preco(prec), quantidade(quan), id(id),
    categoria(cate), fornecedor(forn), validade(vali), dataEntrada(data) {}

//Getters:
const string& Produto::getNome() const noexcept { return nome; }
float Produto::getPreco() const noexcept { return preco; }
int Produto::getQuantidade() const noexcept { return quantidade; }
int Produto::getId() const noexcept { return id; }
const string& Produto::getCategoria() const noexcept { return categoria; }
const string& Produto::getFornecedor() const noexcept { return fornecedor; }
int Produto::getValidade() const noexcept { return validade; }
int Produto::getDataDeEntrada() const noexcept { return dataEntrada; }

//Setters:
void Produto::setNome(const string& name) { nome = name; }
void Produto::setPreco(float prec) {
    if (prec >= 0) {
        preco = prec;
    }
}
void Produto::setQuantidade(int quan) {
    if (quan >= 0) {
        quantidade = quan;
    }
}
void Produto::setId(int id) {
    if(id > 0) {
         this->id = id; }
}
void Produto::setCategoria(const string& cate) { categoria = cate; }
void Produto::setFornecedor(const string& forn) { fornecedor = forn; }
void Produto::setValidade(int vali) { validade = vali; }
void Produto::setDataDeEntrada(int data) { dataEntrada = data; }

ostream& operator<<(ostream& os, const Produto& p) {
    os << "ID: " << p.getId()
       << " | Nome: " << p.getNome()
       << fixed << setprecision(2)
       << " | Preço: " << p.getPreco()
       << " | Quantidade: " << p.getQuantidade();

    return os;
}