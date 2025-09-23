#include <iostream>
#include <string>
#include <stdlib.h>
#define TAM 10 
struct *ficha{
    int id;
    float nota;
    string nome;

};

void leitura(ficha n){
    using namespace std;
    ind[tam];
    ficha aluno;

    cout << "Digite o nome do usuário" << endl;
    cin >> aluno[i] -> nome;
    cout << "Digite o ID do aluno" << endl;
    cin >> aluno[i] -> id;
    cout << "Agora digite a nota" << endl;
    cin >> aluno[i] -> nota;
}

void troca(ficha aluno){
    int a[tam]
    int escolha;
    cout << "Informe o ID do aluno desejado" << endl;
    int id_de_procura;
    for(int i; i < a; i++){
        while(aluno[i]){
            if(id_de_procura == aluno){
                aluno -> nota = nullptr;
                cout << "Reescreva a nota" << endl;
                cin >> aluno[i] -> nota;
                
            }
        }
    }
}


int main(){
    ficha aluno;
    void menu(){
    int escolha;
    do{
        cout << "_____________________________________"
             << "CADASTRO DE ALUNOS \N"
             << "Didite as opções de escolha"
             << "Digite: 1 para inicar o cadastro dos alunos"
             << "Digite: 2 para sair do programa"
            ' << "Digite "'
            cin >> escolha;
       switch (escolha) {
        case 1:
        leitura(aluno);
        break;

        case 2:
        cout << "Saindo..." << endl;
        exit();

        case 3:
        troca(aluno);
        break;

        default:
        cout << "opcao inválida" << endl;
        break;
    }
    }while(!case 2);
    }


}
