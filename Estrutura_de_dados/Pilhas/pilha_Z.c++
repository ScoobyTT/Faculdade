#include <iostream>
 
using namespace std;
 
// Definindo a estrutura nodo
struct nodo {
    int info;    // Armazena o valor do elemento
    nodo* prox;  // Aponta para o próximo elemento da pilha
};
 
class PilhaD {
private:
    nodo* topo; // Aponta para o topo da pilha
 
public:
    // Construtor
    PilhaD();
 
    // Método para empilhar um elemento
    void empilhar(int n);
 
    // Método para desempilhar um elemento
    int desempilhar();
 
    // Método para listar os elementos da pilha
    void listar();
};
 
// Implementação do construtor
PilhaD::PilhaD() {
    topo = nullptr;
}
 
// Implementação do método empilhar
void PilhaD::empilhar(int n) {
    nodo* novo = new nodo();
    novo->info = n;
    if (topo == nullptr) {
        novo->prox = nullptr;
    } else {
        novo->prox = topo;
    }
    topo = novo;
}
 
// Implementação do método desempilhar
int PilhaD::desempilhar() {
    if (topo == nullptr) {
        cout << "Pilha vazia!" << endl;
        return -1; // Indicando erro
    }
 
    nodo* aux = topo;
    int valor = aux->info;
    topo = topo->prox; // O topo da pilha passa a ser o próximo elemento
    delete aux; // Libera a memória do antigo topo
 
    return valor;
}
 
// Implementação do método listar
void PilhaD::listar() {
    nodo* atual = topo;
    if (atual == nullptr) {
        cout << "Pilha vazia!" << endl;
        return;
    }
 
    while (atual != nullptr) {
        cout << atual->info << " ";
        atual = atual->prox;
    }
    cout << endl;
}
 
int main() {
    PilhaD pilha;
 
    pilha.empilhar(4);
    pilha.empilhar(7);
    pilha.empilhar(10);
 
    cout << "Elementos da pilha: ";
    pilha.listar();
 
    cout << "Desempilhando: " << pilha.desempilhar() << endl;
 
    cout << "Elementos da pilha após desempilhar: ";
    pilha.listar();
 
    return 0;
}
