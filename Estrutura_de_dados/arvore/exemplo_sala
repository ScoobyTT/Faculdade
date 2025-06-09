#include <iostream>
using namespace std;

struct nodo {
    int info;
    struct nodo *esq, *dir;
};

class Basic {
    public:
    nodo *raiz;

    Basic() { raiz = nullptr; }

    nodo* inserir(nodo *raiz, int n) { //método com recursão

        if(raiz == nullptr){
            raiz = new nodo();
            if(raiz == nullptr) exit(1);
            raiz->info = n;
            raiz->esq = nullptr;
            raiz->dir = nullptr;
            return raiz;
        }

        if(n > raiz->info) raiz->dir = inserir(raiz->dir, n);
        else {
            if(n < raiz->info) raiz->esq = inserir(raiz->esq, n);
            else cout << "Número repetido";
        }

        return raiz;

    }

    void emOrdem(nodo *raiz) {
        if(raiz == nullptr) return;
        emOrdem(raiz->esq);
        cout << raiz->info << " ";
        emOrdem(raiz->dir);
    }

    int buscar(nodo *raiz, int n) {
        if(raiz == nullptr) {
            return -1;
        }
        if(raiz->info == n) {
            return raiz->info;
        }

        if(raiz->info > n) {
            return buscar(raiz->esq, n);
        }
        else {
            return buscar(raiz->dir, n);
        }
    }

    int contarF(nodo *raiz) {
            if(raiz == nullptr) return 0;
            if(raiz->esq == nullptr && !raiz->dir)  return 1;

            return(contarF(raiz->esq) + contarF(raiz->dir));
        }

    void compararLados(nodo *raiz) {
        int e, d;
        if(raiz == nullptr) return;

        e = contarF(raiz->esq);
        d = contarF(raiz->dir);

        if(e > d) cout << "esquerda tem mais folhas";
        else if(e < d) cout << "esquerda tem menos folhas";
        else cout << "iguais";
    }

    int maiorFolha(nodo *raiz) {

        if(raiz->dir != nullptr) return maiorFolha(raiz->dir);
        else return raiz->info;
        
    }

    int contar(nodo *raiz) { 

        if(raiz == nullptr) {
            return 0;
        }
        
        return (1 + contar(raiz->esq) + contar(raiz->dir));

    }

    bool eEstritaBinario(nodo *raiz) {

        if(raiz == nullptr) {
            return true;
        }

        if(raiz->esq == nullptr && raiz->dir == nullptr) {
                return true;
            } 
        if(raiz->esq != nullptr && raiz->dir != nullptr) {
            return eEstritaBinario(raiz->esq) && eEstritaBinario(raiz->dir);
            //antes eu só estava chamando a função e esquecendo de retornar
        }
    
        return false;
    
    }

    nodo* retirar(nodo *raiz, int n) {
        nodo *aux;

        if(raiz == nullptr) return raiz;
        if(n > raiz->info) {
            raiz->dir = retirar(raiz->dir, n);
        }
        else {
            if(n < raiz->info) {
                raiz->esq = retirar(raiz->esq, n);
            }
            else { //igual

            }
        }
    }

    int altura(nodo *raiz){
        if(raiz==nullptr) return -1;

        int e = altura(raiz->esq);
        int d = altura(raiz->dir);

        if(e>d) return e+1;
        else return d+1;
    }

    void imprimeNiveis(nodo *raiz) { //largura
        nodo *esq, *dir;

        if(raiz != nullptr) cout << raiz->info;

        if(raiz->esq != nullptr) {
            esq = raiz->esq;
        }
        else if(raiz->dir != nullptr) {
            dir = raiz->dir;
        }

        if(esq) imprimeNiveis(raiz->esq);
        else if(dir) imprimeNiveis(raiz->dir);

    }

};

int main() {

    Basic arvore;
   
    arvore.raiz = arvore.inserir(arvore.raiz, 10);
    arvore.raiz = arvore.inserir(arvore.raiz, 5);
    arvore.raiz = arvore.inserir(arvore.raiz, 15);
    arvore.raiz = arvore.inserir(arvore.raiz, 3);
    arvore.raiz = arvore.inserir(arvore.raiz, 1);
    arvore.raiz = arvore.inserir(arvore.raiz, 4);
    arvore.raiz = arvore.inserir(arvore.raiz, 7);
    arvore.raiz = arvore.inserir(arvore.raiz, 20);
    arvore.raiz = arvore.inserir(arvore.raiz, 12);

    /*cout << arvore.contar(arvore.raiz);
    cout << endl;
    cout << arvore.maiorFolha(arvore.raiz);
    cout << endl;
    arvore.compararLados(arvore.raiz);
    cout << endl;
    arvore.emOrdem(arvore.raiz);
    cout << endl;
    cout << arvore.contarF(arvore.raiz);
    cout << endl;
    cout << arvore.buscar(arvore.raiz, 12);
    cout << endl;
    cout << arvore.eEstritaBinario(arvore.raiz);*/
    cout << arvore.altura(arvore.raiz);

}
