#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>
#include <iomanip>
#include <limits>
#include <locale>
#include <cstdlib>
#include <set>
#include <thread>

using namespace std;
using namespace chrono;

// ===================== ESTRUTURA DO PRODUTO =====================
struct Produto {
    int codigo;
    string nome;
    string categoria;
    string fornecedor;
    int quantidade;
    double preco;
    int dataValidade;  // Formato: AAAAMMDD
    int dataEntrada;   // Formato: AAAAMMDD
    
    Produto() : codigo(0), quantidade(0), preco(0.0), dataValidade(0), dataEntrada(0) {}
    
    Produto(int c, string n, string cat, string forn, int qtd, double p, int val, int ent)
        : codigo(c), nome(n), categoria(cat), fornecedor(forn), 
          quantidade(qtd), preco(p), dataValidade(val), dataEntrada(ent) {}
};

// ===================== FUNÇÕES AUXILIARES DE DATA =====================
int converterData(const string& entrada) {
    int dia, mes, ano;
    string temp = entrada;
    
    temp.erase(remove(temp.begin(), temp.end(), ' '), temp.end());
    
    if (temp.find('/') != string::npos) {
        sscanf(temp.c_str(), "%d/%d/%d", &dia, &mes, &ano);
    } 
    else if (temp.length() == 8 && all_of(temp.begin(), temp.end(), ::isdigit)) {
        dia = stoi(temp.substr(0, 2));
        mes = stoi(temp.substr(2, 2));
        ano = stoi(temp.substr(4, 4));
    }
    else {
        stringstream ss(temp);
        ss >> dia >> mes >> ano;
        if (ss.fail()) {
            return -1;
        }
    }
    
    if (ano < 2000 || ano > 2100 || mes < 1 || mes > 12 || dia < 1 || dia > 31) {
        return -1;
    }
    
    return ano * 10000 + mes * 100 + dia;
}

string formatarData(int data) {
    if (data == 0) return "N/A";
    int ano = data / 10000;
    int mes = (data % 10000) / 100;
    int dia = data % 100;
    
    stringstream ss;
    ss << setfill('0') << setw(2) << dia << "/"
       << setfill('0') << setw(2) << mes << "/"
       << ano;
    return ss.str();
}

void carregamentoBonito() {
    cout << "\n";
    cout << "╔══════════════════════════════════════════════════════════╗\n";
    cout << "║                                                          ║\n";
    cout << "║     🌟 SISTEMA DE ESTOQUE - SUPERMERCADO 🌟              ║\n";
    cout << "║                                                          ║\n";
    cout << "║     Grupo 3 - Camile B. e Arthur R.                      ║\n";
    cout << "║     Data: 14/05/2026                                     ║\n";
    cout << "║                                                          ║\n";
    cout << "╚══════════════════════════════════════════════════════════╝\n";
    cout << "\n";

    cout << "🔧 Inicializando";
    for (int i = 0; i < 3; i++) {
        cout << ".";
        cout.flush();
        this_thread::sleep_for(chrono::milliseconds(1000)); // Delay com chrono
    }
    cout << "\n";

    cout << "📂 Carregando dados";
    for (int i = 0; i < 3; i++) {
        cout << ".";
        cout.flush();
        this_thread::sleep_for(chrono::milliseconds(1000)); // Delay com chrono
    }
    cout << "\n";

    cout << "✅ Sistema pronto!\n";
    this_thread::sleep_for(chrono::milliseconds(500));
    system("cls");
}

// ===================== TABELA HASH =====================
class TabelaHash {
private:
    static const int TAMANHO = 101;
    vector<Produto> tabela[TAMANHO];
    
    int funcaoHash(int codigo) {
        return codigo % TAMANHO;
    }
    
public:
    void inserir(const Produto& p) {
        int pos = funcaoHash(p.codigo);
        tabela[pos].push_back(p);
    }
    
    Produto* buscar(int codigo) {
        int pos = funcaoHash(codigo);
        for (auto& produto : tabela[pos]) {
            if (produto.codigo == codigo) {
                return &produto;
            }
        }
        return nullptr;
    }
    
    bool remover(int codigo) {
        int pos = funcaoHash(codigo);
        for (auto it = tabela[pos].begin(); it != tabela[pos].end(); ++it) {
            if (it->codigo == codigo) {
                tabela[pos].erase(it);
                return true;
            }
        }
        return false;
    }
    
    vector<Produto> obterTodos() {
        vector<Produto> todos;
        for (int i = 0; i < TAMANHO; i++) {
            for (const auto& p : tabela[i]) {
                todos.push_back(p);
            }
        }
        return todos;
    }
    
    bool existeCodigo(int codigo) {
        return buscar(codigo) != nullptr;
    }
};

// ===================== GERENCIADOR DE ESTOQUE =====================
class GerenciadorEstoque {
private:
    TabelaHash produtos;
    vector<Produto> produtosPorNome;
    
    void quickSort(vector<Produto>& arr, int inicio, int fim) {
        if (inicio >= fim) return;
        
        string pivo = arr[fim].nome;
        int i = inicio - 1;
        
        for (int j = inicio; j < fim; j++) {
            if (arr[j].nome <= pivo) {
                i++;
                swap(arr[i], arr[j]);
            }
        }
        swap(arr[i + 1], arr[fim]);
        
        int posPivo = i + 1;
        quickSort(arr, inicio, posPivo - 1);
        quickSort(arr, posPivo + 1, fim);
    }
    
    void atualizarVetorNomes() {
        produtosPorNome = produtos.obterTodos();
        if (!produtosPorNome.empty()) {
            quickSort(produtosPorNome, 0, produtosPorNome.size() - 1);
        }
    }
    
    int buscaBinariaPorNome(const string& nome) {
        int esquerda = 0;
        int direita = produtosPorNome.size() - 1;
        
        while (esquerda <= direita) {
            int meio = (esquerda + direita) / 2;
            
            if (produtosPorNome[meio].nome == nome) {
                return meio;
            }
            else if (produtosPorNome[meio].nome < nome) {
                esquerda = meio + 1;
            }
            else {
                direita = meio - 1;
            }
        }
        return -1;
    }
    
    void limparBuffer() {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    
    int lerInteiro(const string& mensagem) {
        int valor;
        while (true) {
            cout << mensagem;
            if (cin >> valor) {
                limparBuffer();
                return valor;
            } else {
                cout << "❌ Entrada inválida! Digite um número inteiro.\n";
                limparBuffer();
            }
        }
    }
    
    double lerDouble(const string& mensagem) {
        double valor;
        while (true) {
            cout << mensagem;
            if (cin >> valor) {
                limparBuffer();
                return valor;
            } else {
                cout << "❌ Entrada inválida! Digite um número.\n";
                limparBuffer();
            }
        }
    }
    
    string lerString(const string& mensagem) {
        string valor;
        cout << mensagem;
        getline(cin, valor);
        return valor;
    }
    
    int lerData(const string& mensagem) {
        string entrada;
        int data;
        
        while (true) {
            cout << mensagem << " (ex: 12/12/2020 ou 12 12 2020 ou 12122020): ";
            getline(cin, entrada);
            
            if (entrada == "sair" || entrada == "SAIR") {
                return -1;
            }
            
            data = converterData(entrada);
            
            if (data == -1) {
                cout << "❌ Formato de data inválido! Tente novamente.\n";
            } else {
                return data;
            }
        }
    }
    
public:
    void cadastrarProduto() {
        cout << "\n📦 CADASTRO DE PRODUTO\n";
        cout << "=====================\n";
        
        int codigo = lerInteiro("Código: ");
        
        if (produtos.existeCodigo(codigo)) {
            cout << "❌ Erro: Já existe um produto com este código!\n";
            return;
        }
        
        string nome = lerString("Nome: ");
        string categoria = lerString("Categoria: ");
        string fornecedor = lerString("Fornecedor: ");
        int quantidade = lerInteiro("Quantidade: ");
        double preco = lerDouble("Preço: R$ ");
        
        cout << "\n📅 INFORME AS DATAS:\n";
        
        int entrada = lerData("Data de entrada");
        if (entrada == -1) {
            cout << "❌ Cadastro cancelado.\n";
            return;
        }
        
        int validade;
        while (true) {
            validade = lerData("Data de validade");
            if (validade == -1) {
                cout << "❌ Cadastro cancelado.\n";
                return;
            }
            
            if (entrada >= validade) {
                cout << "\n❌ ERRO: Data de entrada (" << formatarData(entrada) 
                     << ") não pode ser posterior ou igual à validade (" 
                     << formatarData(validade) << ")!\n";
                continue;
            }
            break;
        }
        
        time_t t = time(nullptr);
        tm* now = localtime(&t);
        int dataAtual = (now->tm_year + 1900) * 10000 + (now->tm_mon + 1) * 100 + now->tm_mday;
        
        if (validade <= dataAtual) {
            cout << "\n⚠️ ATENÇÃO: Produto VENCIDO (validade: " << formatarData(validade) << ")!\n";
            cout << "Deseja cadastrar mesmo assim? (s/n): ";
            string resposta;
            getline(cin, resposta);
            
            if (resposta != "s" && resposta != "S") {
                cout << "✅ Cadastro cancelado.\n";
                return;
            }
        }
        
        Produto novo(codigo, nome, categoria, fornecedor, quantidade, preco, validade, entrada);
        produtos.inserir(novo);
        atualizarVetorNomes();
        
        cout << "\n✅ Produto cadastrado com sucesso!\n";
        cout << "   Entrada: " << formatarData(entrada) << "\n";
        cout << "   Validade: " << formatarData(validade) << "\n";
    }
    
    void registrarEntrada() {
        cout << "\n📥 REGISTRAR ENTRADA\n";
        cout << "===================\n";
        
        int codigo = lerInteiro("Código do produto: ");
        Produto* p = produtos.buscar(codigo);
        
        if (p == nullptr) {
            cout << "❌ Produto não encontrado!\n";
            return;
        }
        
        cout << "Produto: " << p->nome << "\n";
        cout << "Quantidade atual: " << p->quantidade << "\n";
        
        int quantidade = lerInteiro("Quantidade a adicionar: ");
        
        if (quantidade <= 0) {
            cout << "❌ Quantidade deve ser positiva!\n";
            return;
        }
        
        p->quantidade += quantidade;
        atualizarVetorNomes();
        
        cout << "✅ Entrada registrada! Nova quantidade: " << p->quantidade << "\n";
    }
    
    void registrarSaida() {
        cout << "\n📤 REGISTRAR SAÍDA\n";
        cout << "=================\n";
        
        int codigo = lerInteiro("Código do produto: ");
        Produto* p = produtos.buscar(codigo);
        
        if (p == nullptr) {
            cout << "❌ Produto não encontrado!\n";
            return;
        }
        
        cout << "Produto: " << p->nome << "\n";
        cout << "Quantidade disponível: " << p->quantidade << "\n";
        
        int quantidade = lerInteiro("Quantidade a remover: ");
        
        if (quantidade <= 0) {
            cout << "❌ Quantidade deve ser positiva!\n";
            return;
        }
        
        if (quantidade > p->quantidade) {
            cout << "❌ Estoque insuficiente! Disponível: " << p->quantidade << "\n";
            return;
        }
        
        p->quantidade -= quantidade;
        atualizarVetorNomes();
        
        cout << "✅ Saída registrada! Nova quantidade: " << p->quantidade << "\n";
    }
    
    void buscarPorCodigo() {
        cout << "\n🔍 BUSCA POR CÓDIGO\n";
        cout << "==================\n";
        
        int codigo = lerInteiro("Código do produto: ");
        
        auto inicio = high_resolution_clock::now();
        Produto* p = produtos.buscar(codigo);
        auto fim = high_resolution_clock::now();
        
        auto duracao = duration_cast<microseconds>(fim - inicio);
        
        if (p == nullptr) {
            cout << "❌ Produto não encontrado!\n";
        } else {
            cout << "\n✅ PRODUTO ENCONTRADO:\n";
            cout << "Código: " << p->codigo << "\n";
            cout << "Nome: " << p->nome << "\n";
            cout << "Categoria: " << p->categoria << "\n";
            cout << "Fornecedor: " << p->fornecedor << "\n";
            cout << "Quantidade: " << p->quantidade << "\n";
            cout << "Preço: R$ " << fixed << setprecision(2) << p->preco << "\n";
            cout << "Data entrada: " << formatarData(p->dataEntrada) << "\n";
            cout << "Data validade: " << formatarData(p->dataValidade) << "\n";
        }
        
        cout << "⏱️ Tempo de busca: " << duracao.count() << " microssegundos\n";
    }
    
    void buscarPorNome() {
        cout << "\n🔍 BUSCA POR NOME\n";
        cout << "================\n";
        
        string nome = lerString("Nome do produto: ");
        
        auto inicio = high_resolution_clock::now();
        int indice = buscaBinariaPorNome(nome);
        auto fim = high_resolution_clock::now();
        
        auto duracao = duration_cast<microseconds>(fim - inicio);
        
        if (indice == -1) {
            cout << "❌ Produto não encontrado!\n";
        } else {
            Produto& p = produtosPorNome[indice];
            cout << "\n✅ PRODUTO ENCONTRADO:\n";
            cout << "Código: " << p.codigo << "\n";
            cout << "Nome: " << p.nome << "\n";
            cout << "Categoria: " << p.categoria << "\n";
            cout << "Fornecedor: " << p.fornecedor << "\n";
            cout << "Quantidade: " << p.quantidade << "\n";
            cout << "Preço: R$ " << fixed << setprecision(2) << p.preco << "\n";
            cout << "Data entrada: " << formatarData(p.dataEntrada) << "\n";
            cout << "Data validade: " << formatarData(p.dataValidade) << "\n";
        }
        
        cout << "⏱️ Tempo de busca: " << duracao.count() << " microssegundos\n";
    }
    
    void listarPorCategoria() {
        cout << "\n📋 LISTAR POR CATEGORIA\n";
        cout << "======================\n";
        
        string categoria = lerString("Categoria: ");
        
        auto inicio = high_resolution_clock::now();
        vector<Produto> todos = produtos.obterTodos();
        vector<Produto> filtrados;
        
        for (const auto& p : todos) {
            if (p.categoria == categoria) {
                filtrados.push_back(p);
            }
        }
        
        auto fim = high_resolution_clock::now();
        auto duracao = duration_cast<microseconds>(fim - inicio);
        
        if (filtrados.empty()) {
            cout << "❌ Nenhum produto encontrado na categoria \"" << categoria << "\"\n";
        } else {
            cout << "\n📦 PRODUTOS DA CATEGORIA \"" << categoria << "\":\n";
            cout << string(80, '-') << "\n";
            for (const auto& p : filtrados) {
                cout << "Cód: " << p.codigo << " | Nome: " << setw(60) << left << p.nome 
                     << " | Qtd: " << p.quantidade << " | R$ " << fixed << setprecision(2) << p.preco
                     << " | Validade: " << formatarData(p.dataValidade) << "\n";
            }
        }
        
        cout << "⏱️ Tempo de listagem: " << duracao.count() << " microssegundos\n";
    }
    
    void relatorioEstoqueBaixo() {
        cout << "\n⚠️ RELATÓRIO DE ESTOQUE BAIXO (QTD < 5)\n";
        cout << "======================================\n";
        
        auto inicio = high_resolution_clock::now();
        vector<Produto> todos = produtos.obterTodos();
        vector<Produto> baixoEstoque;
        
        for (const auto& p : todos) {
            if (p.quantidade < 5) {
                baixoEstoque.push_back(p);
            }
        }
        
        auto fim = high_resolution_clock::now();
        auto duracao = duration_cast<microseconds>(fim - inicio);
        
        if (baixoEstoque.empty()) {
            cout << "✅ Nenhum produto com estoque baixo!\n";
        } else {
            cout << "\n⚠️ PRODUTOS COM ESTOQUE BAIXO:\n";
            cout << string(80, '-') << "\n";
            for (const auto& p : baixoEstoque) {
                cout << "Cód: " << p.codigo << " | Nome: " << setw(60) << left << p.nome 
                     << " | Qtd: " << p.quantidade << " | Fornecedor: " << p.fornecedor << "\n";
            }
        }
        
        cout << "⏱️ Tempo de geração: " << duracao.count() << " microssegundos\n";
    }
    
    void relatorioProximoVencimento() {
        cout << "\n📅 RELATÓRIO DE PRODUTOS PRÓXIMOS DO VENCIMENTO\n";
        cout << "==============================================\n";
        
        time_t t = time(nullptr);
        tm* now = localtime(&t);
        int hoje = (now->tm_year + 1900) * 10000 + (now->tm_mon + 1) * 100 + now->tm_mday;
        
        cout << "Data de hoje: " << formatarData(hoje) << "\n\n";
        
        auto inicio = high_resolution_clock::now();
        vector<Produto> todos = produtos.obterTodos();
        vector<Produto> proximosVencer;
        vector<Produto> jaVencidos;
        
        for (const auto& p : todos) {
            if (p.dataValidade < hoje) {
                jaVencidos.push_back(p);
            } else if (p.dataValidade - hoje <= 7) {
                proximosVencer.push_back(p);
            }
        }
        
        auto fim = high_resolution_clock::now();
        auto duracao = duration_cast<microseconds>(fim - inicio);
        
        if (!jaVencidos.empty()) {
            cout << "🔴 PRODUTOS VENCIDOS:\n";
            cout << string(80, '-') << "\n";
            for (const auto& p : jaVencidos) {
                cout << "Cód: " << p.codigo << " | Nome: " << setw(60) << left << p.nome 
                     << " | Validade: " << formatarData(p.dataValidade) << " (VENCIDO!)\n";
            }
            cout << "\n";
        }
        
        if (!proximosVencer.empty()) {
            cout << "🟡 PRODUTOS PRÓXIMOS DO VENCIMENTO (até 7 dias):\n";
            cout << string(80, '-') << "\n";
            for (const auto& p : proximosVencer) {
                int diasRestantes = p.dataValidade - hoje;
                cout << "Cód: " << p.codigo << " | Nome: " << setw(60) << left << p.nome 
                     << " | Validade: " << formatarData(p.dataValidade) << " | Dias: " << diasRestantes << "\n";
            }
        }
        
        if (jaVencidos.empty() && proximosVencer.empty()) {
            cout << "✅ Nenhum produto vencido ou próximo do vencimento!\n";
        }
        
        cout << "⏱️ Tempo de geração: " << duracao.count() << " microssegundos\n";
    }

    void mostrarProdutos() {
    cout << "\n📋 MOSTRAR PRODUTOS\n";
    cout << "==================\n";
    cout << "1. Ordenar por NOME\n";
    cout << "2. Ordenar por CATEGORIA\n";
    cout << "3. Ordenar por DATA DE VALIDADE\n";
    cout << "4. Ordenar por QUANTIDADE (menor para maior)\n";
    cout << "5. Ordenar por PREÇO (menor para maior)\n";
    cout << "6. Filtrar por CATEGORIA\n";
    cout << "7. Filtrar por FORNECEDOR\n";
    cout << "8. Voltar\n";
    cout << "\nEscolha: ";
    
    int opcao;
    cin >> opcao;
    limparBuffer();
    
    vector<Produto> todos = produtos.obterTodos();
    
    if (todos.empty()) {
        cout << "\n❌ Nenhum produto cadastrado!\n";
        return;
    }
    
    auto inicio = high_resolution_clock::now();
    
    switch (opcao) {
        case 1:
            quickSort(todos, 0, todos.size() - 1);
            cout << "\n📦 PRODUTOS ORDENADOS POR NOME:\n";
            cout << string(80, '-') << "\n";
            for (const auto& p : todos) {
                cout << "Cód: " << setw(4) << p.codigo 
                     << " | Nome: " << setw(25) << left << p.nome 
                     << " | Qtd: " << setw(3) << p.quantidade
                     << " | R$ " << fixed << setprecision(2) << setw(6) << p.preco
                     << " | Validade: " << formatarData(p.dataValidade) << "\n";
            }
            break;
            
        case 2:
            sort(todos.begin(), todos.end(), [](const Produto& a, const Produto& b) {
                if (a.categoria != b.categoria) return a.categoria < b.categoria;
                return a.nome < b.nome;
            });
            cout << "\n📦 PRODUTOS ORDENADOS POR CATEGORIA:\n";
            cout << string(80, '-') << "\n";
            for (const auto& p : todos) {
                cout << "Cód: " << setw(4) << p.codigo 
                     << " | Nome: " << setw(25) << left << p.nome 
                     << " | Cat: " << setw(12) << p.categoria
                     << " | Qtd: " << p.quantidade << "\n";
            }
            break;
            
        case 3:
            sort(todos.begin(), todos.end(), [](const Produto& a, const Produto& b) {
                return a.dataValidade < b.dataValidade;
            });
            cout << "\n📦 PRODUTOS ORDENADOS POR DATA DE VALIDADE:\n";
            cout << string(80, '-') << "\n";
            for (const auto& p : todos) {
                cout << "Cód: " << setw(4) << p.codigo 
                     << " | Nome: " << setw(25) << left << p.nome 
                     << " | Validade: " << formatarData(p.dataValidade)
                     << " | Qtd: " << p.quantidade << "\n";
            }
            break;
            
        case 4:
            sort(todos.begin(), todos.end(), [](const Produto& a, const Produto& b) {
                return a.quantidade < b.quantidade;
            });
            cout << "\n📦 PRODUTOS ORDENADOS POR QUANTIDADE:\n";
            cout << string(80, '-') << "\n";
            for (const auto& p : todos) {
                string alerta = (p.quantidade < 5) ? " ⚠️" : "";
                cout << "Cód: " << setw(4) << p.codigo 
                     << " | Nome: " << setw(25) << left << p.nome 
                     << " | Qtd: " << setw(3) << p.quantidade << alerta
                     << " | Cat: " << p.categoria << "\n";
            }
            break;
            
        case 5:
            sort(todos.begin(), todos.end(), [](const Produto& a, const Produto& b) {
                return a.preco < b.preco;
            });
            cout << "\n📦 PRODUTOS ORDENADOS POR PREÇO:\n";
            cout << string(80, '-') << "\n";
            for (const auto& p : todos) {
                cout << "Cód: " << setw(4) << p.codigo 
                     << " | Nome: " << setw(25) << left << p.nome 
                     << " | R$ " << fixed << setprecision(2) << setw(6) << p.preco
                     << " | Qtd: " << p.quantidade << "\n";
            }
            break;
            
        case 6: {
            cout << "\n📂 CATEGORIAS DISPONÍVEIS:\n";
            set<string> categorias;
            for (const auto& p : todos) {
                categorias.insert(p.categoria);
            }
            for (const auto& cat : categorias) {
                cout << "   - " << cat << "\n";
            }
            
            string categoriaFiltro = lerString("\nDigite a categoria desejada: ");
            
            vector<Produto> filtrados;
            for (const auto& p : todos) {
                if (p.categoria == categoriaFiltro) {
                    filtrados.push_back(p);
                }
            }
            
            if (filtrados.empty()) {
                cout << "\n❌ Nenhum produto encontrado na categoria \"" << categoriaFiltro << "\"\n";
            } else {
                cout << "\n📦 PRODUTOS DA CATEGORIA \"" << categoriaFiltro << "\":\n";
                cout << string(80, '-') << "\n";
                for (const auto& p : filtrados) {
                    cout << "Cód: " << setw(4) << p.codigo 
                         << " | Nome: " << setw(25) << left << p.nome 
                         << " | Qtd: " << setw(3) << p.quantidade
                         << " | R$ " << fixed << setprecision(2) << p.preco
                         << " | Validade: " << formatarData(p.dataValidade) << "\n";
                }
                cout << "\n📊 Total: " << filtrados.size() << " produtos\n";
            }
            break;
        }
        
        case 7: {
            cout << "\n🏭 FORNECEDORES DISPONÍVEIS:\n";
            set<string> fornecedores;
            for (const auto& p : todos) {
                fornecedores.insert(p.fornecedor);
            }
            for (const auto& forn : fornecedores) {
                cout << "   - " << forn << "\n";
            }
            
            string fornecedorFiltro = lerString("\nDigite o nome do fornecedor: ");
            
            vector<Produto> filtrados;
            for (const auto& p : todos) {
                if (p.fornecedor == fornecedorFiltro) {
                    filtrados.push_back(p);
                }
            }
            
            if (filtrados.empty()) {
                cout << "\n❌ Nenhum produto encontrado do fornecedor \"" << fornecedorFiltro << "\"\n";
            } else {
                cout << "\n📦 PRODUTOS DO FORNECEDOR \"" << fornecedorFiltro << "\":\n";
                cout << string(80, '-') << "\n";
                for (const auto& p : filtrados) {
                    cout << "Cód: " << setw(4) << p.codigo 
                         << " | Nome: " << setw(25) << left << p.nome 
                         << " | Qtd: " << setw(3) << p.quantidade
                         << " | R$ " << fixed << setprecision(2) << p.preco
                         << " | Validade: " << formatarData(p.dataValidade) << "\n";
                }
                cout << "\n📊 Total: " << filtrados.size() << " produtos\n";
            }
            break;
        }
        
        case 8:
            return;
            
        default:
            cout << "\n❌ Opção inválida!\n";
            return;
    }
    
    auto fim = high_resolution_clock::now();
    auto duracao = duration_cast<microseconds>(fim - inicio);
    
    cout << "\n📊 Total de produtos exibidos: " << todos.size() << "\n";
    cout << "⏱️ Tempo de exibição: " << duracao.count() << " microssegundos\n";
}

    
    void adicionarProdutosExemplo() {
        cout << "\n📦 ADICIONANDO 50 PRODUTOS DE EXEMPLO...\n";
        
        vector<tuple<int, string, string, string, int, double, int, int>> produtosExemplo = {
            {1001, "Arroz 5kg", "Mercearia", "Unilever", 50, 22.90, 20261231, 20260115},
            {1002, "Feijão 1kg", "Mercearia", "Camil", 45, 8.50, 20261130, 20260115},
            {1003, "Açúcar 1kg", "Mercearia", "União", 60, 4.75, 20261015, 20260120},
            {1004, "Óleo 900ml", "Mercearia", "Liza", 40, 6.90, 20260930, 20260120},
            {1005, "Macarrão 500g", "Mercearia", "Adria", 55, 3.99, 20260815, 20260125},
            {1006, "Farinha 1kg", "Mercearia", "Rosa Branca", 35, 4.50, 20260720, 20260125},
            {1007, "Sal 1kg", "Mercearia", "Cisne", 48, 2.30, 20261231, 20260201},
            {1008, "Café 500g", "Mercearia", "3 Corações", 32, 14.90, 20261010, 20260201},
            {1009, "Leite Condensado", "Mercearia", "Moça", 28, 6.50, 20260920, 20260205},
            {1010, "Molho Tomate", "Mercearia", "Pomarola", 42, 3.20, 20260830, 20260205},
            {2001, "Refrigerante 2L", "Bebidas", "Coca-Cola", 80, 8.99, 20260515, 20260110},
            {2002, "Suco 1L", "Bebidas", "Sucos do Vale", 35, 6.50, 20260420, 20260110},
            {2003, "Água 500ml", "Bebidas", "Crystal", 120, 2.00, 20261231, 20260112},
            {2004, "Cerveja 350ml", "Bebidas", "Ambev", 90, 3.50, 20260530, 20260112},
            {2005, "Energético 250ml", "Bebidas", "Monster", 25, 9.90, 20260715, 20260115},
            {2006, "Leite UHT 1L", "Bebidas", "Parmalat", 45, 4.99, 20260410, 20260115},
            {2007, "Iogurte 160g", "Bebidas", "Danone", 30, 3.50, 20260325, 20260118},
            {2008, "Chá Gelado", "Bebidas", "Lipton", 28, 6.50, 20260820, 20260118},
            {2009, "Vinho Tinto", "Bebidas", "Santa Helena", 15, 29.90, 20281231, 20260120},
            {2010, "Cachaça 1L", "Bebidas", "51", 20, 18.90, 20301231, 20260120},
            {3001, "Detergente", "Limpeza", "Ypê", 70, 2.30, 20261231, 20260105},
            {3002, "Sabão em Pó", "Limpeza", "Omo", 40, 12.90, 20261015, 20260105},
            {3003, "Água Sanitária", "Limpeza", "Q-Boa", 25, 3.80, 20260920, 20260108},
            {3004, "Desinfetante", "Limpeza", "Pinho Sol", 32, 5.50, 20260815, 20260108},
            {3005, "Esponja Aço", "Limpeza", "Bombril", 100, 1.50, 20261231, 20260110},
            {3006, "Papel Toalha", "Limpeza", "Personal", 45, 7.90, 20261130, 20260110},
            {3007, "Lustra Móveis", "Limpeza", "Peroba", 22, 8.50, 20261010, 20260112},
            {3008, "Sabão Líquido", "Limpeza", "Minuano", 35, 6.90, 20260905, 20260112},
            {3009, "Alvejante", "Limpeza", "Vanish", 18, 11.90, 20260820, 20260115},
            {3010, "Cera Auto", "Limpeza", "Vonixx", 12, 25.90, 20261231, 20260115},
            {4001, "Sabonete", "Higiene", "Dove", 150, 1.99, 20260515, 20260102},
            {4002, "Shampoo", "Higiene", "Seda", 55, 9.90, 20260720, 20260102},
            {4003, "Condicionador", "Higiene", "Pantene", 50, 10.90, 20260720, 20260103},
            {4004, "Creme Dental", "Higiene", "Colgate", 80, 3.50, 20260810, 20260103},
            {4005, "Desodorante", "Higiene", "Rexona", 65, 12.90, 20260705, 20260105},
            {4006, "Papel Higiênico", "Higiene", "Neve", 90, 6.99, 20261231, 20260105},
            {4007, "Fio Dental", "Higiene", "Oral-B", 40, 4.50, 20260915, 20260107},
            {4008, "Enxaguante", "Higiene", "Listerine", 25, 15.90, 20260820, 20260107},
            {4009, "Absorvente", "Higiene", "Always", 60, 8.90, 20261030, 20260109},
            {4010, "Aparelho Barbear", "Higiene", "Gillette", 35, 14.90, 20261231, 20260109},
            {5001, "Queijo Mussarela", "Frios", "Tirolez", 25, 19.90, 20260315, 20260114},
            {5002, "Presunto", "Frios", "Sadia", 28, 12.90, 20260310, 20260114},
            {5003, "Manteiga", "Frios", "Aviação", 30, 7.50, 20260325, 20260116},
            {5004, "Margarina", "Frios", "Qualy", 35, 6.90, 20260405, 20260116},
            {5005, "Requeijão", "Frios", "Catupiry", 22, 11.90, 20260320, 20260118},
            {5006, "Iogurte Bebível", "Frios", "Batavo", 40, 2.50, 20260328, 20260118},
            {5007, "Salmão", "Frios", "Seabob", 8, 45.90, 20260305, 20260120},
            {5008, "Peito Peru", "Frios", "Perdigão", 20, 13.90, 20260318, 20260120},
            {5009, "Cream Cheese", "Frios", "Philadelphia", 15, 8.90, 20260322, 20260122},
            {5010, "Leite Fermentado", "Frios", "Chamyto", 25, 3.50, 20260330, 20260122}
        };
        
        int adicionados = 0;
        for (const auto& prod : produtosExemplo) {
            Produto p(get<0>(prod), get<1>(prod), get<2>(prod), get<3>(prod),
                      get<4>(prod), get<5>(prod), get<6>(prod), get<7>(prod));
            if (!produtos.existeCodigo(p.codigo)) {
                produtos.inserir(p);
                adicionados++;
            }
        }
        
        atualizarVetorNomes();
        cout << "✅ " << adicionados << " produtos adicionados!\n";
        cout << "📊 Total no estoque: " << produtos.obterTodos().size() << "\n";
    }
    
    void salvarArquivo() {
        cout << "\n💾 SALVANDO...\n";
        
        ofstream arquivo("estoque.dat", ios::binary);
        if (!arquivo) {
            cout << "❌ Erro ao salvar!\n";
            return;
        }
        
        vector<Produto> todos = produtos.obterTodos();
        int tamanho = todos.size();
        arquivo.write((char*)&tamanho, sizeof(tamanho));
        
        for (const auto& p : todos) {
            arquivo.write((char*)&p.codigo, sizeof(p.codigo));
            arquivo.write((char*)&p.quantidade, sizeof(p.quantidade));
            arquivo.write((char*)&p.preco, sizeof(p.preco));
            arquivo.write((char*)&p.dataValidade, sizeof(p.dataValidade));
            arquivo.write((char*)&p.dataEntrada, sizeof(p.dataEntrada));
            
            int tam;
            tam = p.nome.size();
            arquivo.write((char*)&tam, sizeof(tam));
            arquivo.write(p.nome.c_str(), tam);
            
            tam = p.categoria.size();
            arquivo.write((char*)&tam, sizeof(tam));
            arquivo.write(p.categoria.c_str(), tam);
            
            tam = p.fornecedor.size();
            arquivo.write((char*)&tam, sizeof(tam));
            arquivo.write(p.fornecedor.c_str(), tam);
        }
        
        arquivo.close();
        cout << "✅ " << tamanho << " produtos salvos!\n";
    }

    void excluirProduto() {
        cout << "\n🗑️ EXCLUIR PRODUTO\n";
        cout << "=================\n";
        
        int codigo = lerInteiro("Código do produto a excluir: ");
        
        auto inicio = high_resolution_clock::now();
        Produto* p = produtos.buscar(codigo);
        
        if (p == nullptr) {
            cout << "❌ Produto não encontrado!\n";
            return;
        }
        
        // Mostra dados do produto antes de excluir
        cout << "\n📦 PRODUTO ENCONTRADO:\n";
        cout << "Código: " << p->codigo << "\n";
        cout << "Nome: " << p->nome << "\n";
        cout << "Categoria: " << p->categoria << "\n";
        cout << "Fornecedor: " << p->fornecedor << "\n";
        cout << "Quantidade: " << p->quantidade << "\n";
        cout << "Preço: R$ " << fixed << setprecision(2) << p->preco << "\n";
        cout << "Data entrada: " << formatarData(p->dataEntrada) << "\n";
        cout << "Data validade: " << formatarData(p->dataValidade) << "\n";
        
        cout << "\n⚠️ TEM CERTEZA QUE DESEJA EXCLUIR ESTE PRODUTO?\n";
        cout << "Digite 'SIM' para confirmar ou qualquer outra tecla para cancelar: ";
        string confirmacao;
        getline(cin, confirmacao);
        
        if (confirmacao != "SIM" && confirmacao != "sim" && confirmacao != "Sim") {
            cout << "✅ Exclusão cancelada.\n";
            return;
        }
        
        // Remove da tabela hash
        bool removido = produtos.remover(codigo);
        
        if (removido) {
            atualizarVetorNomes();  // Reconstroi o vetor ordenado por nome
            auto fim = high_resolution_clock::now();
            auto duracao = duration_cast<microseconds>(fim - inicio);
            
            cout << "\n✅ Produto excluído com sucesso!\n";
            cout << "⏱️ Tempo de exclusão: " << duracao.count() << " microssegundos\n";
        } else {
            cout << "\n❌ Erro ao excluir produto!\n";
        }
    }
    
    void carregarArquivo() {
        ifstream arquivo("estoque.dat", ios::binary);
        if (!arquivo) {
            cout << "⚠️  Nenhum arquivo encontrado. Iniciando vazio.\n";
            return;
        }
        
        int tamanho;
        arquivo.read((char*)&tamanho, sizeof(tamanho));
        
        for (int i = 0; i < tamanho; i++) {
            Produto p;
            arquivo.read((char*)&p.codigo, sizeof(p.codigo));
            arquivo.read((char*)&p.quantidade, sizeof(p.quantidade));
            arquivo.read((char*)&p.preco, sizeof(p.preco));
            arquivo.read((char*)&p.dataValidade, sizeof(p.dataValidade));
            arquivo.read((char*)&p.dataEntrada, sizeof(p.dataEntrada));
            
            int tam;
            arquivo.read((char*)&tam, sizeof(tam));
            p.nome.resize(tam);
            arquivo.read(&p.nome[0], tam);
            
            arquivo.read((char*)&tam, sizeof(tam));
            p.categoria.resize(tam);
            arquivo.read(&p.categoria[0], tam);
            
            arquivo.read((char*)&tam, sizeof(tam));
            p.fornecedor.resize(tam);
            arquivo.read(&p.fornecedor[0], tam);
            
            produtos.inserir(p);
        }
        
        arquivo.close();
        atualizarVetorNomes();
        cout << "✅ " << tamanho << " produtos carregados!\n";
    }

    void editarProduto() {
    cout << "\n✏️ EDITAR PRODUTO\n";
    cout << "================\n";
    
    int codigo = lerInteiro("Código do produto a editar: ");
    
    auto inicio = high_resolution_clock::now();
    Produto* p = produtos.buscar(codigo);
    
    if (p == nullptr) {
        cout << "❌ Produto não encontrado!\n";
        return;
    }
    
    // Mostra dados atuais
    cout << "\n📦 PRODUTO ENCONTRADO:\n";
    cout << "═══════════════════════════════════════════════════════════\n";
    cout << "Código.......: " << p->codigo << "\n";
    cout << "Nome.........: " << p->nome << "\n";
    cout << "Categoria....: " << p->categoria << "\n";
    cout << "Fornecedor...: " << p->fornecedor << "\n";
    cout << "Quantidade...: " << p->quantidade << "\n";
    cout << "Preço........: R$ " << fixed << setprecision(2) << p->preco << "\n";
    cout << "Data entrada.: " << formatarData(p->dataEntrada) << "\n";
    cout << "Data validade: " << formatarData(p->dataValidade) << "\n";
    cout << "═══════════════════════════════════════════════════════════\n";
    
    cout << "\n📝 O QUE DESEJA EDITAR?\n";
    cout << "1. Nome\n";
    cout << "2. Categoria\n";
    cout << "3. Fornecedor\n";
    cout << "4. Quantidade\n";
    cout << "5. Preço\n";
    cout << "6. Data de entrada\n";
    cout << "7. Data de validade\n";
    cout << "8. Editar MÚLTIPLOS campos\n";
    cout << "9. Cancelar\n";
    cout << "\nEscolha: ";
    
    int opcao;
    cin >> opcao;
    limparBuffer();
    
    bool precisaAtualizar = false;
    
    switch (opcao) {
        case 1: {
            string novoNome = lerString("Novo nome: ");
            p->nome = novoNome;
            precisaAtualizar = true;
            cout << "✅ Nome alterado com sucesso!\n";
            break;
        }
        case 2: {
            string novaCategoria = lerString("Nova categoria: ");
            p->categoria = novaCategoria;
            cout << "✅ Categoria alterada com sucesso!\n";
            break;
        }
        case 3: {
            string novoFornecedor = lerString("Novo fornecedor: ");
            p->fornecedor = novoFornecedor;
            cout << "✅ Fornecedor alterado com sucesso!\n";
            break;
        }
        case 4: {
            int novaQuantidade = lerInteiro("Nova quantidade: ");
            if (novaQuantidade < 0) {
                cout << "❌ Quantidade não pode ser negativa!\n";
            } else {
                p->quantidade = novaQuantidade;
                cout << "✅ Quantidade alterada com sucesso!\n";
            }
            break;
        }
        case 5: {
            double novoPreco = lerDouble("Novo preço: R$ ");
            if (novoPreco < 0) {
                cout << "❌ Preço não pode ser negativo!\n";
            } else {
                p->preco = novoPreco;
                cout << "✅ Preço alterado com sucesso!\n";
            }
            break;
        }
        case 6: {
            cout << "\n📅 Data atual: " << formatarData(p->dataEntrada) << "\n";
            int novaEntrada = lerData("Nova data de entrada");
            if (novaEntrada == -1) {
                cout << "❌ Edição cancelada.\n";
            } else if (p->dataValidade != 0 && novaEntrada >= p->dataValidade) {
                cout << "❌ ERRO: Data de entrada não pode ser posterior ou igual à validade!\n";
            } else {
                p->dataEntrada = novaEntrada;
                cout << "✅ Data de entrada alterada com sucesso!\n";
            }
            break;
        }
        case 7: {
            cout << "\n📅 Data atual: " << formatarData(p->dataValidade) << "\n";
            int novaValidade = lerData("Nova data de validade");
            if (novaValidade == -1) {
                cout << "❌ Edição cancelada.\n";
            } else if (novaValidade <= p->dataEntrada) {
                cout << "❌ ERRO: Data de validade deve ser posterior à data de entrada!\n";
            } else {
                p->dataValidade = novaValidade;
                
                // Verifica se o produto está vencido
                time_t t = time(nullptr);
                tm* now = localtime(&t);
                int dataAtual = (now->tm_year + 1900) * 10000 + (now->tm_mon + 1) * 100 + now->tm_mday;
                
                if (p->dataValidade <= dataAtual) {
                    cout << "⚠️ ATENÇÃO: Produto está VENCIDO com esta nova data!\n";
                }
                cout << "✅ Data de validade alterada com sucesso!\n";
            }
            break;
        }
        case 8: {
            // Edição múltipla
            cout << "\n🔧 EDIÇÃO MÚLTIPLA (deixe em branco para manter o valor atual)\n";
            cout << "═══════════════════════════════════════════════════════════════\n";
            
            string input;
            
            // Nome
            cout << "Nome atual: " << p->nome << "\n";
            cout << "Novo nome (Enter para manter): ";
            getline(cin, input);
            if (!input.empty()) {
                p->nome = input;
                precisaAtualizar = true;
            }
            
            // Categoria
            cout << "\nCategoria atual: " << p->categoria << "\n";
            cout << "Nova categoria (Enter para manter): ";
            getline(cin, input);
            if (!input.empty()) {
                p->categoria = input;
            }
            
            // Fornecedor
            cout << "\nFornecedor atual: " << p->fornecedor << "\n";
            cout << "Novo fornecedor (Enter para manter): ";
            getline(cin, input);
            if (!input.empty()) {
                p->fornecedor = input;
            }
            
            // Quantidade
            cout << "\nQuantidade atual: " << p->quantidade << "\n";
            cout << "Nova quantidade (Enter para manter): ";
            getline(cin, input);
            if (!input.empty()) {
                int novaQtd = stoi(input);
                if (novaQtd >= 0) {
                    p->quantidade = novaQtd;
                } else {
                    cout << "⚠️ Quantidade negativa ignorada!\n";
                }
            }
            
            // Preço
            cout << "\nPreço atual: R$ " << fixed << setprecision(2) << p->preco << "\n";
            cout << "Novo preço (Enter para manter): ";
            getline(cin, input);
            if (!input.empty()) {
                double novoPreco = stod(input);
                if (novoPreco >= 0) {
                    p->preco = novoPreco;
                } else {
                    cout << "⚠️ Preço negativo ignorado!\n";
                }
            }
            
            // Data de entrada
            cout << "\nData entrada atual: " << formatarData(p->dataEntrada) << "\n";
            cout << "Nova data de entrada (Enter para manter, formato: 12/12/2024): ";
            getline(cin, input);
            if (!input.empty()) {
                int novaEntrada = converterData(input);
                if (novaEntrada != -1) {
                    if (p->dataValidade != 0 && novaEntrada >= p->dataValidade) {
                        cout << "❌ ERRO: Data de entrada não pode ser posterior à validade!\n";
                    } else {
                        p->dataEntrada = novaEntrada;
                    }
                } else {
                    cout << "⚠️ Data inválida! Mantida a original.\n";
                }
            }
            
            // Data de validade
            cout << "\nData validade atual: " << formatarData(p->dataValidade) << "\n";
            cout << "Nova data de validade (Enter para manter, formato: 12/12/2024): ";
            getline(cin, input);
            if (!input.empty()) {
                int novaValidade = converterData(input);
                if (novaValidade != -1) {
                    if (novaValidade <= p->dataEntrada) {
                        cout << "❌ ERRO: Validade deve ser posterior à data de entrada!\n";
                    } else {
                        p->dataValidade = novaValidade;
                        precisaAtualizar = true;
                    }
                } else {
                    cout << "⚠️ Data inválida! Mantida a original.\n";
                }
            }
            
            cout << "\n✅ Edição múltipla concluída!\n";
            break;
        }
        case 9:
            cout << "✅ Edição cancelada.\n";
            return;
        default:
            cout << "❌ Opção inválida!\n";
            return;
    }
    
    // Se alterou nome, precisa reordenar o vetor
    if (precisaAtualizar) {
        atualizarVetorNomes();
    }
    
    auto fim = high_resolution_clock::now();
    auto duracao = duration_cast<microseconds>(fim - inicio);
    
    cout << "\n📊 DADOS ATUALIZADOS DO PRODUTO:\n";
    cout << "───────────────────────────────────────────────────────────\n";
    cout << "Nome.........: " << p->nome << "\n";
    cout << "Categoria....: " << p->categoria << "\n";
    cout << "Fornecedor...: " << p->fornecedor << "\n";
    cout << "Quantidade...: " << p->quantidade << "\n";
    cout << "Preço........: R$ " << fixed << setprecision(2) << p->preco << "\n";
    cout << "Data entrada.: " << formatarData(p->dataEntrada) << "\n";
    cout << "Data validade: " << formatarData(p->dataValidade) << "\n";
    cout << "───────────────────────────────────────────────────────────\n";
    cout << "⏱️ Tempo de edição: " << duracao.count() << " microssegundos\n";
}
    
    void mostrarMenu() {
        cout << "\n╔════════════════════════════════════════════════╗\n";
        cout << "║     GERENCIADOR DE ESTOQUE - SUPERMERCADO      ║\n";
        cout << "╠════════════════════════════════════════════════╣\n";
        cout << "║  1. Cadastrar produto                          ║\n";
        cout << "║  2. Registrar entrada                          ║\n";
        cout << "║  3. Registrar saída                            ║\n";
        cout << "║  4. Mostrar Produtos (Ordenar/Filtrar)         ║\n";
        cout << "║  5. Buscar por código (Hash)                   ║\n";
        cout << "║  6. Buscar por nome (Busca Binária)            ║\n";
        cout << "║  7. Listar por categoria                       ║\n";
        cout << "║  8. Relatório de estoque baixo                 ║\n";
        cout << "║  9. Relatório de vencimento                    ║\n";
        cout << "║ 10. Excluir Produto                            ║\n";
        cout << "║ 11. Editar Produto                             ║\n";
        cout << "║ 12. Salvar e sair                              ║\n";
        cout << "╚════════════════════════════════════════════════╝\n";
    }
};

// ===================== FUNÇÃO PRINCIPAL =====================
int main() {
    setlocale(LC_ALL, "pt_BR.UTF-8");
    system("chcp 65001 > nul");
    system("color 0A");

    carregamentoBonito();
    
    GerenciadorEstoque sistema;
    
    sistema.carregarArquivo();
    
    int opcao;
    
    while (true) {
        sistema.mostrarMenu();
        cout << "\nOpção: ";
        
        if (!(cin >> opcao)) {
            cout << "❌ Opção inválida!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        switch (opcao) {
            case 1: sistema.cadastrarProduto(); break;
            case 2: sistema.registrarEntrada(); break;
            case 3: sistema.registrarSaida(); break;
            case 4: sistema.mostrarProdutos(); break;
            case 5: sistema.buscarPorCodigo(); break;
            case 6: sistema.buscarPorNome(); break;
            case 7: sistema.listarPorCategoria(); break;
            case 8: sistema.relatorioEstoqueBaixo(); break;
            case 9: sistema.relatorioProximoVencimento(); break;
            case 10: sistema.excluirProduto(); break;
            case 11: sistema.editarProduto(); break;
            case 20: sistema.adicionarProdutosExemplo(); break;
            case 12:
                sistema.salvarArquivo();
                cout << "\n👋 Programa finalizado!\n";
                return 0;
            default:
                cout << "❌ Opção inválida! Digite 1 a 12.\n";
        }
        
        cout << "\nPressione Enter...";
        cin.get();
    }
    
    return 0;
}