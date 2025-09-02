#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

#define MAXplanilha 100
struct planilha { 
  std:: string nome;
  int matricula;
  float salario;
  float imposto;
};

int leitura(planilha f[], int n){
  cout << "Digite a quantidade de funcionários" << endl;
  std::cin >> n;
  
  for(int i = 0; i <n; i++){
    cout << "Digite o nome do funcionário" << endl;
    cin >> f[i].nome;
    cout << "Digite a matrícula do funcionário" << endl;
    cin >> f[i].matricula;
    cout << "Digite o salário do funcionário" << endl;
    cin >> f[i].salario;
    cout << "Digite o imposto do funcionário" << endl;
    cin >> f[i].imposto;
    cout << "Funcionário adicionado com sucesso" << endl
         << "--------------------------------" << endl
          << "Digite o nome do próximo funcionário:" << endl;

  }
  return n;
}
int main(){
  planilha z[MAXplanilha];
  leitura (z, MAXplanilha);
}
