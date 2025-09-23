#include <iostream>
#include <string>
#include <cstdlib>
#define TAM 10
struct *ficha{
    int ID;
    int nota;
    string nome;
};

int PEGA_BAHIA(ficha * n){
    using namespace std;
    ficha aluno[TAM];
    for(int i = 0; i < TAM; i++){
        cout << "Digite o nome do aluno" << endl;
        cin << aluno[i] -> nome;
        cout << "Digite a matrícula do aluno" << endl;
        cin aluno[i] -> ID;
        cout << "Agora digite a nota do aluno" << endl;
        cin << aluno -> nota;
        if(nota <= 10 && nota >= 0){
            cout << "sla tropa" << endl; 
        }else cout << "nota inválida" << endl;

    }
}

int main(){
    ficha aluno;
    do{
        std::cout << "-----------------------------------------------\n"
                  << "Inicio do cadastro \n"
                  << "Digite a opção desejada"
                  << "Digite: 1 para cadastrar o aluno"
                  << "Digite: 2 para fechar o programa" 
                  '<< "Digite: 3 para cadastrar outro aluno"' << endl;

        int n = nullptr;
        switch(n)
        case 1:
        PEGA_BAHIA(aluno);
        break;
        case 2:
        std::cout << "Saindo" << endl;
        exit();
       'case 3:'
        default:
        std::cout << "Opção inválida" << endl;
    }while(case 3)
    return 0;
}


